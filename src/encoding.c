/**
* @Author: Dominique Metz <Dome>
* @Date:   2016-07-08T12:33:36+02:00
* @Email:  DominiqueMetz@gmx.de
* @Project: FRC_FP
* @Last modified by:   dome
* @Last modified time: 2016-09-24T13:29:52+02:00
**/

#include "encoding.h"

void encode(float_cast* fc, uint8_t* num_values_in_group, uint8_t* width_of_group, int32_t bits_per_block, int32_t num_groups, BitStream *bs){
  int bit_plane = MANTISSA_SIZE_F32 - 1;    // Number of bits in the mantissa
  int current_group = num_groups - 1;   // The current group encoded
  int num_values = 0;                   // Number of values to encode
  write_byte(fc[0].parts.exponent, bs); // Write the exponent of the block
  bits_per_block -= 8;                  // Subtract 8 Bits for exponent

  // Encode one bitplane at a time
  for(bit_plane = MANTISSA_SIZE_F32, num_values = 0;  bit_plane-- > 0;){
    // Encode bit_plane
    for(int i = 0;;){
      // Encode the group of significant values
      for(; i < num_values; i++){
        uint32_t sign = fc[i].parts.sign;
				uint8_t mantissa_bit = fc[i].parts.mantissa >> bit_plane;

        // Write bit "bit_plane" of fc[i]
        write_bit(mantissa_bit & 1, bs);
        if(!--bits_per_block){
          goto END_ENCODE;
        }
        // Write the sign, when mantissa_bit is the most significant bit with a one
        if(mantissa_bit == 1){
          write_bit(sign, bs);
          if(!--bits_per_block){
            goto END_ENCODE;
          }
        }
      }
      // Continue with next bitplane, if all groups have been added to the encoding process
      if(current_group < 0){
        break;
      }
      // Test next group
      if(width_of_group[current_group] > bit_plane){
        // Signal significance and add the next values to the encoding process
        write_bit(1, bs);
        if (!--bits_per_block){
          goto END_ENCODE;
        }
        num_values += num_values_in_group[current_group];
        current_group--;
      }
      else{
        // Signal insignificance, continue with next bitplane
        write_bit(0, bs);
        if(!--bits_per_block){
          goto END_ENCODE;
        }
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

uint8_t decode(float_cast* fc, uint8_t* num_values_in_group, int32_t bits_per_block, int32_t num_groups, BitStream *bs){
  int32_t bit_plane = MANTISSA_SIZE_F32;    // Number of bits in the mantissa
  int32_t current_group = num_groups - 1;   // The current group encoded
  int32_t num_values = 0;                   // Number of values to encode
  uint8_t exponent = read_byte(bs);         // Write the exponent of the block
  uint32_t bit = 0;
  bits_per_block -= 8;                      // Subtract 8 Bits for exponent

  // Decode one bitplane at a time
  for(bit_plane = MANTISSA_SIZE_F32, num_values = 0; bit_plane-- > 0;){
    // Decode bitplane
    for(int32_t i = 0;;){
      // Decode group
      for(; i < num_values; ++i){
        //Read bit "bit_plane" from fc[i]
        bit = read_bit(bs);
        bit <<= bit_plane;
				if(!--bits_per_block){
          goto END_DECODE;
        }

        if(fc[i].parts.mantissa){
          fc[i].parts.mantissa |= bit;
        }
        else if(bit){
          // If this is the first bit of this value, read also the sign of it
          fc[i].parts.sign = read_bit(bs);
					fc[i].parts.mantissa = bit;
					if(!--bits_per_block){
            goto END_DECODE;
          }
        }
      }
      // Continue with next bitplane, if all groups have been added to the decoding process
      if(current_group < 0){
        break;
      }
      // Test next group for significance
      if(read_bit(bs)){
        // If significant, add to decoding process
        num_values += num_values_in_group[current_group];
        current_group--;
				if(!--bits_per_block){
          goto END_DECODE;
        }
      }
      else{
				if(!--bits_per_block){
          goto END_DECODE;
        }
        // Group is insignificant, go on with next bit plane
        break;
      }
    }
  }

  // Read left over bits
  while(bits_per_block-- > 0){
    read_bit(bs);
  }

END_DECODE:
  return exponent;
}

uint8_t read_byte(BitStream *bs){
  uint8_t byte = 0;
  for(int32_t i = 7; i >= 0; --i){
    byte |= read_bit(bs) << i;
  }
  return byte;
}

uint8_t read_bit(BitStream *bs){
  if(bs->bit_pos < 0){
    bs->buffer = bs->dest[0];
    bs->dest++;
    bs->bit_pos = 7;
  }
  uint8_t bit = bs->buffer >> bs->bit_pos;
  bs->bit_pos--;
  return bit & 1;
}

void write_byte(uint8_t byte, BitStream *bs){
  for(int32_t i = 7; i >= 0; --i){
    write_bit(byte >> i, bs);
  }
}

void write_bit(uint8_t bit, BitStream *bs){
  bs->buffer |= bit << bs->bit_pos;
  bs->bit_pos--;
  if(bs->bit_pos < 0){
    bs->dest[0] = bs->buffer;
    bs->dest++;
    bs->bit_pos = 7;
    bs->buffer = 0;
  }
}
