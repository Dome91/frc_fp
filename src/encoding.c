/**
* @Author: Dominique Metz <Dome>
* @Date:   2016-07-08T12:33:36+02:00
* @Email:  DominiqueMetz@gmx.de
* @Project: FRC_FP
* @Last modified by:   dome
* @Last modified time: 2016-07-20T13:56:20+02:00
**/

#include "encoding.h"

void encode(float_cast* fc, char *num_values_in_group, char* width_of_group, int bits_per_block, int num_groups, BitStream *bs){
  int bit_plane = MANTISSA_SIZE_F32;    // Number of bits in the mantissa
  int current_group = num_groups - 1;   // The current group encoded
  int num_values = 0;                   // Number of values to encode
  int i;                                // Index variable
  char keep_encoding;                   // Signals that no insignificant group was encountered for current bitplane
  write_byte(fc[0].parts.exponent, bs); // Write the exponent of the block
  bits_per_block -= 8;                  // Subtract 8 Bits for exponent

  // As long as there are still bit planes to be encoded and groups to be encoded
  while(bit_plane >= 0 && current_group > -1){
    keep_encoding = 1;  // Signals significant groups are still present, keep encoding
    i = 0;              // Start at first value

    // As long as there are still significant groups
    while(keep_encoding && current_group > -1){
      // If group is significant
      if(width_of_group[current_group] >= bit_plane){
        write_bit(1, bs);
        if(!bits_per_block--){
          goto END;
        }
        num_values += num_values_in_group[current_group]; // Add the new values to be considered
        current_group--;                                  // Take the next group in the next iteration

        // For all currently interesting values
        for(;i < num_values; ++i){
          char bit = (fc[i].parts.mantissa >> bit_plane) & 1; // Get the bit in the bit plane
          write_bit(bit, bs);

          // If it is a 1, also write the sign
          if(bit){
            char sign = fc[i].parts.sign;
            write_bit(sign, bs);
            if(!bits_per_block--){
              goto END;
            }
          }
        }
      }
      // If insignificant
      else{
        write_bit(0, bs);
        if(!bits_per_block--){
          goto END;
        }
        keep_encoding = 0; // Stop encoding
        bit_plane--;       // And go to next bit plane
      }
    }
  }

END:
  return;
}

int decode(float_cast* fc, char* num_values_in_group, char* width_of_group, int bits_per_block, int num_groups, BitStream *bs){
  int bit_plane = MANTISSA_SIZE_F32;    // Number of bits in the mantissa
  int current_group = num_groups - 1;   // The current group encoded
  int num_values = 0;                   // Number of values to encode
  int i;                                // Index variable
  char keep_encoding;                   // Signals that no insignificant group was encountered for current bitplane
  int exponent = read_byte(bs);         // Write the exponent of the block
  bits_per_block -= 8;                  // Subtract 8 Bits for exponent

  // As long as there are still bit planes to be encoded and groups to be encoded
  while(bit_plane >= 0 && current_group > -1){
    keep_encoding = 1;  // Signals significant groups are still present, keep encoding
    i = 0;              // Start at first value

    // As long as there are still significant groups
    while(keep_encoding && current_group > -1){
      // If group is significant
      if(read_bit(bs)){
        if(!bits_per_block--){
          goto END;
        }
        num_values += num_values_in_group[current_group]; // Add the new values to be considered
        current_group--;                                  // Take the next group in the next iteration

        // For all currently interesting values
        for(;i < num_values; ++i){
          char bit = read_bit(bs) << bit_plane;
          if(!bits_per_block--){
            goto END;
          }
          if(fc[i].parts.mantissa){
            fc[i].parts.mantissa += bit;
          }
          else if(bit){
            fc[i].parts.sign = read_bit(bs);
            fc[i].parts.mantissa = bit;
            if(!bits_per_block--){
              goto END;
            }

          }
        }
      }
      // If insignificant
      else{
        keep_encoding = 0; // Stop encoding
        bit_plane--;       // And go to next bit plane
      }
    }
  }

END:
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
  }
}
