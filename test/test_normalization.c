#include <stdlib.h>

#include "normalization.h"
#include "test/test_normalization.h"
#include "test/unity.h"

void test_normalize_denormalize(){
  int size_3d = 64;

  float_cast fc[size_3d];
  float_cast fc_original[size_3d];
  for(int i = 0; i < size_3d; ++i){
    fc[i].f = rand() / RAND_MAX;
    fc_original[i].f = fc[i].f;
  }

  normalize(fc, size_3d);
  denormalize(fc, size_3d);

  float delta = 0.00001f;
  for(int i = 0; i < size_3d; ++i){
    TEST_ASSERT_FLOAT_WITHIN(delta, fc_original[i].f, fc[i].f);
  }
}
