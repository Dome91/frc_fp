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
  int i;                                // Index variable
  write_byte(fc[0].parts.exponent, bs); // Write the exponent of the block
  bits_per_block -= 8;                  // Subtract 8 Bits for exponent

  // While there are still bit planes to be encoded
  while(bit_plane >= 0){
    i = 0; // Start from the first value of the block

    // Until all groups are encoded
    while(1){
      // Encode num_values - i values
      while(i < num_values){
        char mantissa_bit = (fc[i].parts.mantissa >> bit_plane) & 1;
        write_bit(mantissa_bit, bs);
        bits_per_block--;
        if(bits_per_block < 0){
          goto END_ENCODE;
        }
        if(mantissa_bit){
          char sign_bit = fc[i].parts.sign;
          write_bit(sign_bit, bs);
          bits_per_block--;
          if(bits_per_block < 0){
            goto END_ENCODE;
          }
        }
      }

      // Break if all groups are encoded
      if(current_group < 0){
        break;
      }

      // Next group is significant if there is a 1-bit higher than the bitplane
      if(width_of_group[current_group] > bit_plane){
        write_bit(1, bs);
        bits_per_block--;
        if(bits_per_block < 0){
          goto END_ENCODE;
        }

        // Add values to the group
        num_values += num_values_in_group[current_group];
        current_group--;
      }
      // Group is insignificant
      else{
        write_bit(0, bs);
        bits_per_block--;
        if(bits_per_block < 0){
          goto END_ENCODE;
        }
      }
    }

    // Next bitplane
    bit_plane--;
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
  int i;                                // Index variable
  int exponent = read_byte(bs);         // Write the exponent of the block
  bits_per_block -= 8;                  // Subtract 8 Bits for exponent

  //While there are still bit planes to be decoded
  while(bit_plane >= 0){
    i = 0;  // Start from the first value in the group

    // Decode until no more groups are present
    while(1){
      // For all remaining values
      while(i < num_values){
        char k = read_bit(bs) << bit_plane; // Read mantissa bit k
        // Check for termination
        bit_plane--;
        if(bit_plane < 0){
          goto END_DECODE;
        }
        // If k is a one, process it
        if(k){
          // If there are already bits in the matissa, add the bit
          if(fc[i].parts.mantissa){
            fc[i].parts.mantissa += k;
          }
          // If not, read the sign in and set the values
          else{
            fc[i].parts.sign      = read_bit(bs);
            fc[i].parts.mantissa  = k;
            bit_plane--;
            if(bit_plane < 0){
              goto END_DECODE;
            }
          }
        }
      }

      // Break out of the infinite loop if not more groups need to be decoded
      if(current_group < 0){
        break;
      }

      // If the next group is significant
      if(read_bit(bs)){
        num_values += num_values_in_group[current_group]; // Add the values of the group
        current_group--;  // Next group
        bit_plane--;
        if(bit_plane < 0){
          goto END_DECODE;
        }
      }
      else{
        // Decode next bitplane and break out of infinite loop
        bit_plane--;
        if(bit_plane < 0){
          goto END_DECODE;
        }
        break;
      }
    }
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
