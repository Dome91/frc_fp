/**
* @Author: Dominique Metz <Dome>
* @Date:   2016-07-15T16:51:38+02:00
* @Email:  DominiqueMetz@gmx.de
* @Project: FRC_FP
* @Last modified by:   Dome
* @Last modified time: 2016-07-16T12:28:52+02:00
*/



#include <stdlib.h>

#include "transformation.h"
#include "test/test_transformation.h"
#include "test/unity.h"

void test_fwd_inv_transform(){
  int size_3d = 64;

  float_cast fc[size_3d];
  float_cast fc_original[size_3d];
  for(int i = 0; i < size_3d; ++i){
    fc[i].f = rand() / RAND_MAX;
    fc_original[i].f = fc[i].f;
  }

  // 1 - dimensional
  fwd_transform(fc, 0, 1);
  inv_transform(fc, 0, 1);

  // 2 - dimensional
  for(int y = 0; y < 4; ++y){
    fwd_transform(fc, y * 4, 1);
  }
  for(int x = 0; x < 4; ++x){
    fwd_transform(fc, x, 4);
  }
  for(int32_t x = 0; x < 4; ++x){
    inv_transform(fc, x, 4);
  }
  for(int32_t y = 0; y < 4; ++y){
    inv_transform(fc, y * 4, 1);
  }

  // 3 - dimensional
  for (uint32_t z = 0; z < 4; ++z)
		for (uint32_t y = 0; y < 4; ++y)
			fwd_transform(fc, z + y * 4, 16);
	for (uint32_t x = 0; x < 4; ++x)
		for (uint32_t z = 0; z < 4; z++)
			fwd_transform(fc, z + x * 16, 4);
	for (uint32_t y = 0; y < 4; ++y)
		for (uint32_t x = 0; x < 4; ++x)
			fwd_transform(fc, y * 4 + x * 16, 1);
  for (uint32_t z = 0; z < 4; ++z)
    for (uint32_t y = 0; y < 4; ++y)
      inv_transform(fc, z + y * 4, 16);
  for (uint32_t x = 0; x < 4; ++x)
    for (uint32_t z = 0; z < 4; ++z)
      inv_transform(fc, z + x * 16, 4);
  for (uint32_t y = 0; y < 4; ++y)
    for (uint32_t x = 0; x < 4; ++x)
      inv_transform(fc, y * 4 + x * 16, 1);

  float delta = 0.00001f;
  for(int i = 0; i < size_3d; ++i){
    TEST_ASSERT_FLOAT_WITHIN(delta, fc_original[i].f, fc[i].f);
  }
}
