/**
* @Author: Dominique Metz <Dome>
* @Date:   2016-07-15T15:42:44+02:00
* @Email:  DominiqueMetz@gmx.de
* @Project: FRC_FP
* @Last modified by:   Dome
* @Last modified time: 2016-07-16T12:27:32+02:00
*/



#ifndef COMMON_H
#define COMMON_H

typedef union {
  float f;
  struct {
    unsigned int mantissa : 23;
    unsigned int exponent : 8;
    unsigned int sign : 1;
  } parts;
} float_cast;

#endif
