/**
* @Author: Dominique Metz <Dome>
* @Date:   2016-07-15T15:49:00+02:00
* @Email:  DominiqueMetz@gmx.de
* @Project: FRC_FP
* @Last modified by:   Dome
* @Last modified time: 2016-07-16T12:28:04+02:00
*/



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
