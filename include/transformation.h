#ifndef TRANSFORMATION_H
#define TRANSFORMATION_H

#include "common.h"

/**
 * Decorrelates the passed floating point values via a lifted discrete orthogonal block transform
 * @param fc     Values to be transformed
 * @param start  Position of value to be started with
 * @param stride Determines the values to work with in the current pass
 */
void fwd_transform(float_cast* fc, int start, int stride);

/**
 * Correlates the passed floating point values via a lifted discrete orthogonal block transform
 * @param fc     Values to be transformed
 * @param start  Position of value to be started with
 * @param stride Determines the values to work with in the current pass
 */
void inv_transform(float_cast* fc, int start, int stride);

#endif
