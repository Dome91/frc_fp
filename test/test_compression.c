/**
* @Author: Dominique Metz <dome>
* @Date:   2016-07-25T16:43:05+02:00
* @Email:  DominiqueMetz@gmx.de
* @Project: FRC_FP
* @Last modified by:   dome
* @Last modified time: 2016-09-22T16:58:45+02:00
*/


#include <stdlib.h>
#include "frc_fp.h"
#include "test/unity.h"
#include "test/test_compression.h"

void test_compression_1d(){
  int dim = 1;
  int size = 256;
  int bits_per_block = 0;
  float* data = (float*) malloc(size * sizeof(float));
  float* res;
  for(int i = 0; i < size; ++i){
    data[i] = ((float)rand()) / RAND_MAX;
  }

  unsigned char* compressed = FRC_FP.compress(data, dim, &size, bits_per_block);
  res = FRC_FP.decompress(compressed, dim, &size, bits_per_block);

  float delta = 0.01f;
  for(int i = 0; i < size; ++i){
    TEST_ASSERT_FLOAT_WITHIN(delta, data[i], res[i]);
  }

  free(data);
  free(compressed);
  free(res);
}
