/**
* @Author: Dominique Metz <Dome>
* @Date:   2016-07-15T15:42:44+02:00
* @Email:  DominiqueMetz@gmx.de
* @Project: FRC_FP
* @Last modified by:   dome
* @Last modified time: 2016-07-25T19:27:48+02:00
*/



#ifndef COMMON_H
#define COMMON_H

#define MANTISSA_SIZE_F32 23
#define MANTISSA_SIZE_F64 52
#define EXPONENT_SIZE_F32 8
#define EXPONENT_SIZE_F64 11
#define SIGN_SIZE 1

typedef union {
  float f;
  struct {
    unsigned int mantissa : MANTISSA_SIZE_F32;
    unsigned int exponent : EXPONENT_SIZE_F32;
    unsigned int sign : SIGN_SIZE;
  } parts;
} float_cast;

typedef union{
  double f;
  struct{
    unsigned long mantissa : MANTISSA_SIZE_F64;
    unsigned int exponent : EXPONENT_SIZE_F64;
    unsigned int sign : SIGN_SIZE;
  } parts;
} double_cast;

typedef struct{
  char buffer;
  char bit_pos;
  char* dest;
} BitStream;

char get_width_of_group(float_cast *fc, int num_values, unsigned int *msb);
#endif
