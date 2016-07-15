#include "test/unity.h"
#include "test/test_normalization.h"
#include "test/test_transformation.h"

int main(int argc, char** argv){
  UNITY_BEGIN();
  RUN_TEST(test_normalize_denormalize);
  RUN_TEST(test_fwd_inv_transform);
  return UNITY_END();
}
