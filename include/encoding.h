/**
* @Author: Dominique Metz <Dome>
* @Date:   2016-07-16T12:23:30+02:00
* @Email:  DominiqueMetz@gmx.de
* @Project: FRC_FP
* @Last modified by:   Dome
* @Last modified time: 2016-07-16T12:25:35+02:00
*/

#ifndef ENCODING_H
#define ENCODING_H

void encode(float_cast* fc, int count, int width, int bits_per_block);
void decode(float_cast* fc, int count, int width, int bits_per_block);

#endif
