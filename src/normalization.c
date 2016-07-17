/**
* @Author: Dominique Metz <Dome>
* @Date:   2016-07-15T15:41:42+02:00
* @Email:  DominiqueMetz@gmx.de
* @Project: FRC_FP
* @Last modified by:   dome
* @Last modified time: 2016-07-17T12:54:55+02:00
*/



#include "normalization.h"

void normalize(float_cast *fc, int size){
  int max_exponent = 0;	// Stores the max exponent in the block
  // For every value in the block
  for(int i = 0; i < size; ++i){
    // Store the implicit leading 1 explicitly
    fc[i].parts.mantissa >>= 1;
    fc[i].parts.mantissa |= 0x400000;
    // Check if the current exponent is larger the the current max one
    max_exponent = fc[i].parts.exponent > max_exponent ? fc[i].parts.exponent : max_exponent;
  }

  for(int i = 0; i < size; ++i){
    // Difference of exponents
    int diff = max_exponent - fc[i].parts.exponent;
    fc[i].parts.mantissa >>= diff;	// Shift the mantissa by difference of exponents
    fc[i].parts.exponent = max_exponent;	// Set new exponent
  }
}

void denormalize(float_cast *fc, int size){
  int shift_size;		// Number of shifts needed to shift out the explicit stored leading 1
  int current_bit;	// The current bit inspected

  // For every value in the float_cast array
  for(int i = 0; i < size; ++i){
    current_bit = fc[i].parts.mantissa & 0x400000;	// Get the first bit

    // Special case: If the first bit is 1, this values exponent doesn't need to be adjusted
    // Just shift out the explicitly stored leading 1
    if(current_bit){
      fc[i].parts.mantissa <<= 1;
    }
    // If its exponent needs to be adjusted
    else{
      fc[i].parts.mantissa <<= 1;	// Shift the first 0 out
      shift_size = 0;							// Initialize to zero

      // As long as we did not find the explicity stored leading 1 and we did not try every position in the mantissa
      while(!current_bit && shift_size < 23){
        shift_size++;																		// Increase the number of shifts necessary
        current_bit = fc[i].parts.mantissa & 0x400000;	// Take the first bit of the mantissa
        fc[i].parts.mantissa <<= 1;											// Shift the bit out
      }
      // When we found the explicityl stored leading 1, we know the former exponent of the value
      fc[i].parts.exponent -= shift_size;
    }
  }
}
