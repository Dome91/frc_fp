/**
* @Author: Dominique Metz <Dome>
* @Date:   2016-07-15T15:42:44+02:00
* @Email:  DominiqueMetz@gmx.de
* @Project: FRC_FP
* @Last modified by:   dome
* @Last modified time: 2016-09-22T17:46:16+02:00
*/

#include <inttypes.h>
#include <stdio.h>

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
    uint32_t mantissa : MANTISSA_SIZE_F32;
    uint32_t exponent : EXPONENT_SIZE_F32;
    uint32_t sign : SIGN_SIZE;
  } parts;
} float_cast;

typedef union{
  double f;
  struct{
    uint64_t mantissa : MANTISSA_SIZE_F64;
    uint32_t exponent : EXPONENT_SIZE_F64;
    uint32_t sign : SIGN_SIZE;
  } parts;
} double_cast;

typedef struct{
  uint8_t buffer;
  int8_t bit_pos;
  uint8_t* dest;
} BitStream;

/**
 * Returns the maximum position of the most significant bit across all values
 * @param  fc         Values
 * @param  num_values Number of values in fc
 * @param  msb        Current most significant bit
 * @return            Position of most signicant bit across all values
 */
uint8_t get_width_of_group(float_cast *fc, int32_t num_values, uint32_t *msb);

/**
 * Prints floating point values in fc. For debugging purposes
 * @param fc   Vlues
 * @param size Number of values
 */
void print_float_cast(float_cast* fc, int32_t size);

#endif
