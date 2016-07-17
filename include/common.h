/**
* @Author: Dominique Metz <Dome>
* @Date:   2016-07-15T15:42:44+02:00
* @Email:  DominiqueMetz@gmx.de
* @Project: FRC_FP
* @Last modified by:   dome
* @Last modified time: 2016-07-17T12:52:53+02:00
*/



#ifndef COMMON_H
#define COMMON_H

#define MANTISSA_SIZE_F32 23
#define EXPONENT_SIZE_F32 8
#define SIGN_SIZE 1

typedef union {
  float f;
  struct {
    unsigned int mantissa : MANTISSA_SIZE_F32;
    unsigned int exponent : EXPONENT_SIZE_F32;
    unsigned int sign : SIGN_SIZE;
  } parts;
} float_cast;

char get_width_of_group(float_cast *fc, int num_values, int msb);
#endif
