/**
* @Author: Dominique Metz <Dome>
* @Date:   2016-07-15T16:47:20+02:00
* @Email:  DominiqueMetz@gmx.de
* @Project: FRC_FP
* @Last modified by:   dome
* @Last modified time: 2016-09-23T19:48:46+02:00
*/



#include "test/unity.h"
#include "test/test_normalization.h"
#include "test/test_transformation.h"
#include "test/test_compression.h"

int main(){
  UNITY_BEGIN();
  RUN_TEST(test_normalize_denormalize);
  RUN_TEST(test_fwd_inv_transform);
  RUN_TEST(test_compression_1d);
  return UNITY_END();
}
