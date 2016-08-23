/**
* @Author: Dominique Metz <Dome>
* @Date:   2016-07-08T12:33:36+02:00
* @Email:  DominiqueMetz@gmx.de
* @Project: FRC_FP
* @Last modified by:   dome
* @Last modified time: 2016-07-25T19:44:00+02:00
**/

#include "encoding.h"

void encode(float_cast* fc, char *num_values_in_group, char* width_of_group, int bits_per_block, int num_groups, BitStream *bs){
  int bit_plane = MANTISSA_SIZE_F32;    // Number of bits in the mantissa
  int current_group = num_groups - 1;   // The current group encoded
  int num_values = 0;                   // Number of values to encode
  write_byte(fc[0].parts.exponent, bs); // Write the exponent of the block
  bits_per_block -= 8;                  // Subtract 8 Bits for exponent
  // output one bit plane at a time from MSB to LSB
  for (bit_plane = MANTISSA_SIZE_F32, num_values = 0;  bit_plane-- > 0;) {
    // encode bit plane k
    for (int i = 0;;) {
      // encode group of significant values
      for (; i < num_values; i++) {
        // encode bit k of data[i]
        char sign = fc[i].parts.sign;
				char mantissa_bit = fc[i].parts.mantissa >> bit_plane;

        // write bit k of |data[i]|
        write_bit(mantissa_bit & 1, bs);
        if (!--bits_per_block)
          goto END_ENCODE;
        if (mantissa_bit == 1) {
          // write sign bit also
          write_bit(sign, bs);
          if (!--bits_per_block)
            goto END_ENCODE;
        }
      }
      // have all groups been encoded?
      if (current_group < 0)
        break;
      // test next group
      if (width_of_group[current_group] > bit_plane) {
        // group is significant; peel off and encode first subgroup
        write_bit(1, bs);
        if (!--bits_per_block)
          goto END_ENCODE;
        num_values += num_values_in_group[current_group];
        current_group--;
      }
      else {
        // group is insignificant; continue with next bit plane
        write_bit(0, bs);
        if (!--bits_per_block)
          goto END_ENCODE;
        break;
      }
    }
  }

  // Fill up with 0-bits
  while(bits_per_block-- > 0){
    write_bit(0, bs);
  }

END_ENCODE:
  return;
}

char decode(float_cast* fc, char* num_values_in_group, int bits_per_block, int num_groups, BitStream *bs){
  int bit_plane = MANTISSA_SIZE_F32;    // Number of bits in the mantissa
  int current_group = num_groups - 1;   // The current group encoded
  int num_values = 0;                   // Number of values to encode
  int exponent = read_byte(bs);         // Write the exponent of the block
  bits_per_block -= 8;                  // Subtract 8 Bits for exponent


  // input one bit plane at a time from MSB to LSB
  for(bit_plane = MANTISSA_SIZE_F32, num_values = 0; bit_plane-- > 0;){
    // decode bit plane k
    for(int i = 0;;){
      // decode group of significant values
      for(; i < num_values; i++){
        // read bit k of |data[i]|
        int mantissa_bit = read_bit(bs) << bit_plane;
				if(!--bits_per_block){
          goto END_DECODE;
        }

        if(fc[i].parts.mantissa){
          fc[i].parts.mantissa += mantissa_bit;
        }
        else if(mantissa_bit) {
          // read sign bit also
          fc[i].parts.sign = read_bit(bs);
					fc[i].parts.mantissa = mantissa_bit;
					if(!--bits_per_block){
            goto END_DECODE;
          }
        }
      }
      // have all groups been decoded?
      if(current_group < 0){
        break;
      }
      // test next group
      if(read_bit(bs)){
        // group is significant; peel off and decode first subgroup
        num_values += num_values_in_group[current_group];
        current_group--;
				if(!--bits_per_block){
          goto END_DECODE;
        }
      }
      else{
				if (!--bits_per_block){
          goto END_DECODE;
        }
        // group is insignificant; continue with next bit plane
        break;
      }
    }
  }

  while(bits_per_block-- > 0){
    read_bit(bs);
  }

END_DECODE:
  return exponent;
}

char read_byte(BitStream *bs){
  char byte = 0;
  for(int i = 7; i >= 0; --i){
    byte |= read_bit(bs) << i;
  }
  return byte;
}

char read_bit(BitStream *bs){
  if(bs->bit_pos < 0){
    bs->buffer = bs->dest[0];
    bs->dest++;
    bs->bit_pos = 7;
  }
  char bit = bs->buffer >> bs->bit_pos;
  bs->bit_pos--;
  return bit;
}

void write_byte(char byte, BitStream *bs){
  for(int i = 7; i >= 0; --i){
    write_bit(byte >> i, bs);
  }
}

void write_bit(char bit, BitStream *bs){
  bs->buffer |= bit << bs->bit_pos;
  bs->bit_pos--;
  if(bs->bit_pos < 0){
    bs->dest[0] = bs->buffer;
    bs->dest++;
    bs->bit_pos = 7;
    bs->buffer = 0;
  }
}
