/**
* @Author: Dominique Metz <dome>
* @Date:   2016-07-17T12:49:27+02:00
* @Email:  DominiqueMetz@gmx.de
* @Project: FRC_FP
* @Last modified by:   dome
* @Last modified time: 2016-07-17T12:57:38+02:00
*/



#include "common.h"

char get_width_of_group(float_cast *fc, int num_values, int msb){
  for(int i = 0; i < num_values; ++i){
    msb |= fc[i].parts.mantissa;
  }
  return 23 - __builtin_clz(msb);
}
