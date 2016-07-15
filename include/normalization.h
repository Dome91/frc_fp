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
