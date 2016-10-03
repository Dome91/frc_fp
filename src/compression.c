/**
* @Author: Dominique Metz <Dome>
* @Date:   2016-07-08T12:31:13+02:00
* @Email:  DominiqueMetz@gmx.de
* @Project: FRC_FP
* @Last modified by:   dome
* @Last modified time: 2016-09-22T17:50:47+02:00
*/

#include "common.h"
#include "compression.h"
#include "encoding.h"
#include "transformation.h"
#include "normalization.h"

void compress_1d(float* data, int32_t *sizes, int32_t bits_per_block, uint8_t* dest, int32_t num_blocks){
  int32_t x_dim = sizes[0];     // Number of values
  int32_t blocksize = 4;        // Size of 1-dimensional block
  int32_t block = 0;            // The current block processed
  float_cast fc[blocksize]; // Contains the values of the current block
  uint8_t width[blocksize]; // Contains the width of groups
  BitStream bs;             // Is used to write bits into destination array
  bs.dest    = dest;
  bs.buffer  = 0;
  bs.bit_pos = 7;
  uint8_t num_values_in_group[4] = {1, 1, 1, 1};

  // While there are still blocks to process
  while(block < num_blocks){
    int32_t start_pos = block * blocksize;
    float* start_block = data + start_pos;  // Jump to the beginning of the current block

    // Copy values into the block
    for(int32_t i = 0; i < blocksize; ++i){
      if(i + start_pos < x_dim){
        fc[i].f = start_block[i];
      }
      else{
        fc[i].f = 0.0f;
      }
    }

    // Normalize and transform values
    fwd_transform(fc, 0, 1);
    normalize(fc, blocksize);

    // Get the width of all four groups
    unsigned int msb = 0;
    width[0] = get_width_of_group(fc + 3, 1, &msb);
    width[1] = get_width_of_group(fc + 2, 1, &msb);
    width[2] = get_width_of_group(fc + 1, 1, &msb);
    width[3] = get_width_of_group(fc + 0, 1, &msb);

    encode(fc, num_values_in_group, width, bits_per_block, 4, &bs);
    block++;
  }

  flush(&bs);
}
/*
void compress_2d(float* data, int32_t *sizes, int32_t bits_per_block, uint8_t* dest, int32_t num_blocks){

}

void compress_3d(float* data, int32_t *sizes, int32_t bits_per_block, uint8_t* dest, int32_t num_blocks){

}
*/
void decompress_1d(uint8_t* data, int32_t *sizes, int32_t bits_per_block, float* dest, int32_t num_blocks){
  int32_t x_dim = sizes[0]; // Number of values
  int32_t blocksize = 4;    // Size of 1-dimensional block
  int32_t block = 0;        // The current block processed
  float_cast fc[blocksize]; // Contains the values of the current block
  BitStream bs;             // Is used to read bits from source array
  bs.dest = data;
  bs.buffer = 0;
  bs.bit_pos  = -1;
  uint8_t num_values_in_group[4] = {1, 1, 1, 1};

  while(block < num_blocks){
    int start_pos = block * blocksize;
    float* start_data = dest + start_pos;
    for(int i = 0; i < blocksize; ++i){
      fc[i].f = 0.0f;
    }

    // Decode values and set exponent
    uint8_t exponent = decode(fc, num_values_in_group, bits_per_block, 4, &bs);
    for(int i = 0; i < blocksize; ++i){
      fc[i].parts.exponent = exponent;
    }

		// Denormalize values
		denormalize(fc, 4);
		// Inverse transform to correlate values
		inv_transform(fc, 0, 1);

		for(int i = 0; i < blocksize; ++i){
			if(start_pos + i < x_dim){
				start_data[i] = fc[i].f;
			}
		}

    block++;
  }
}
/*
void decompress_2d(uint8_t* data, int32_t *sizes, int32_t bits_per_block, float* dest, int32_t num_blocks){
}

void decompress_3d(uint8_t* data, int32_t *sizes, int32_t bits_per_block, float* dest, int32_t num_blocks){

}
*/
void flush(BitStream *bs){
  bs->dest[0] = bs->buffer;
  bs->dest++;
  bs->buffer = 0;
  bs->bit_pos = 7;
}
