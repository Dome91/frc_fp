/**
* @Author: Dominique Metz <dome>
* @Date:   2016-07-17T12:49:27+02:00
* @Email:  DominiqueMetz@gmx.de
* @Project: FRC_FP
* @Last modified by:   dome
* @Last modified time: 2016-09-22T17:46:37+02:00
*/



#include "common.h"

uint8_t get_width_of_group(float_cast *fc, int32_t num_values, uint32_t *msb){
  for(int i = 0; i < num_values; ++i){
    (*msb) |= fc[i].parts.mantissa;
  }

  return 32 - __builtin_clz(*msb);
}

void print_float_cast(float_cast* fc, int32_t size){
  for(int32_t i = 0; i < size; ++i){
    printf("%f\n", fc[i].f);
  }
}
