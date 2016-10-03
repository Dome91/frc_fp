/**
* @Author: Dominique Metz <Dome>
* @Date:   2016-07-15T15:46:10+02:00
* @Email:  DominiqueMetz@gmx.de
* @Project: FRC_FP
* @Last modified by:   dome
* @Last modified time: 2016-09-22T12:43:43+02:00
*/



#include <stdlib.h>
#include <math.h>
#include <stdio.h>

#include "compression.h"
#include "frc_fp.h"

uint8_t* compress(float* values, int32_t dim, int32_t* sizes, int32_t bits_per_block){
  uint64_t num_blocks = get_num_blocks(dim, sizes); // Get the number of blocks the source is divided into
  uint64_t size_of_result;                          // Calculate the number of bytes the result takes up
  uint8_t* result;                                  // Allocate memory for result

  // Start compression in correct dimension
  switch(dim){
    case 1:
      bits_per_block = bits_per_block == 0 ? MAX_BITRATE_1D : bits_per_block;
      size_of_result = num_blocks * bits_per_block / 8;
      result = (uint8_t*) malloc(size_of_result);
      compress_1d(values, sizes, bits_per_block, result, num_blocks);
      break;
    /*case 2:
      bits_per_block = bits_per_block == 0 ? MAX_BITRATE_2D : bits_per_block;
      size_of_result = num_blocks * bits_per_block / 8;
      result = (uint8_t*) malloc(size_of_result);
      compress_2d(values, sizes, bits_per_block, result, num_blocks);
      break;
    case 3:
      bits_per_block = bits_per_block == 0 ? MAX_BITRATE_3D : bits_per_block;
      size_of_result = num_blocks * bits_per_block / 8;
      result = (uint8_t*) malloc(size_of_result);
      compress_3d(values, sizes, bits_per_block, result, num_blocks);
      break;*/
    default:
      printf("Only up to dimension 3 is supported!\n");
      return NULL;
  }

  return result;
}

float* decompress(uint8_t* values, int32_t dim, int32_t* sizes, int32_t bits_per_block){
  uint64_t num_blocks = get_num_blocks(dim, sizes);
  uint64_t size_of_result = num_blocks * pow(4, dim) * sizeof(float);
  float* result = (float*) malloc(size_of_result);
  switch (dim) {
    case 1:
      bits_per_block = bits_per_block == 0 ? MAX_BITRATE_1D : bits_per_block;
      decompress_1d(values, sizes, bits_per_block, result, num_blocks);
      break;
    /*case 2:
      bits_per_block = bits_per_block == 0 ? MAX_BITRATE_2D : bits_per_block;
      decompress_2d(values, sizes, bits_per_block, result, num_blocks);
      break;
    case 3:
      bits_per_block = bits_per_block == 0 ? MAX_BITRATE_3D : bits_per_block;
      decompress_3d(values, sizes, bits_per_block, result, num_blocks);
      break;*/
    default:
      printf("Only up to dimension 3 is supported!\n");
      return NULL;
  }

  return result;
}

uint64_t get_num_blocks(int32_t dim, int32_t* sizes){
  uint64_t num_values = 1;
  for(int32_t i = 0; i < dim; ++i){
    num_values *= sizes[i];
  }

  int32_t blocksize = pow(4, dim);
  int32_t num_blocks = num_values / blocksize;
  num_blocks += num_values % blocksize ? 1 : 0;
  return num_blocks;
}

const struct frc_fp FRC_FP = {
    .compress   = compress,
    .decompress = decompress,
};
