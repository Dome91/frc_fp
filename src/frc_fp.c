/**
* @Author: Dominique Metz <Dome>
* @Date:   2016-07-15T15:46:10+02:00
* @Email:  DominiqueMetz@gmx.de
* @Project: FRC_FP
* @Last modified by:   dome
* @Last modified time: 2016-07-17T12:57:23+02:00
*/



#include <stdlib.h>
#include <math.h>
#include <stdio.h>

#include "compression.h"
#include "decompression.h"
#include "frc_fp.h"

char* compress(float* values, int dim, int* sizes, int bits_per_block){
  long num_blocks = get_num_blocks(dim, sizes);         // Get the number of blocks the source is divided into
  long size_of_result = num_blocks * bits_per_block / 8;// Calculate the number of bytes the result takes up
  char* result = (char*) malloc(size_of_result);        // Allocate memory for result

  // Start compression in correct dimension
  switch(dim){
    case 1:
      compress_1d(values, sizes, bits_per_block, result, num_blocks);
      break;
    case 2:
      compress_2d(values, sizes, bits_per_block, result);
      break;
    case 3:
      compress_3d(values, sizes, bits_per_block, result);
      break;
    default:
      printf("Only up to dimension 3 is supported!\n");
      return NULL;
  }

  return result;
}

float* decompress(char* values, int dim, int* sizes, int bits_per_block){
  long num_blocks = get_num_blocks(dim, sizes);
  long size_of_result = num_blocks * pow(4, dim) * sizeof(float) / 8;
  float* result = (float*) malloc(size_of_result);
  switch (dim) {
    case 1:
      decompress_1d(values, sizes, bits_per_block, result);
      break;
    case 2:
      decompress_2d(values, sizes, bits_per_block, result);
      break;
    case 3:
      decompress_3d(values, sizes, bits_per_block, result);
      break;
    default:
      printf("Only up to dimension 3 is supported!\n");
      return NULL;
  }

  return result;
}

long get_num_blocks(int dim, int* sizes){
  long num_values = 1;
  for(int i = 0; i < dim; ++i){
    num_values *= sizes[i];
  }

  int blocksize = pow(4, dim);
  int num_blocks = num_values / blocksize;
  return num_blocks;
}

const struct frc_fp FRC_FP = {
    .compress   = compress,
    .decompress = decompress,
};
