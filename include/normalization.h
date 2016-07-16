/**
* @Author: Dominique Metz <Dome>
* @Date:   2016-07-15T15:45:29+02:00
* @Email:  DominiqueMetz@gmx.de
* @Project: FRC_FP
* @Last modified by:   Dome
* @Last modified time: 2016-07-16T12:27:59+02:00
*/



#ifndef NORMALIZATION_H
#define NORMALIZATION_H

#include "common.h"

/**
 * Normalizes each floating point value to the biggest exponent in the block
 * @param fc   Block of values
 * @param size Number of values in the block
 */
void normalize(float_cast *fc, int size);

/**
 * Denormalizes each value to the form before normalization
 * @param fc   Block of values
 * @param size Number of values in the block
 */
void denormalize(float_cast *fc, int size);

#endif
