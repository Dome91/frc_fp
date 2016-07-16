/**
* @Author: Dominique Metz <Dome>
* @Date:   2016-07-15T13:17:32+02:00
* @Email:  DominiqueMetz@gmx.de
* @Project: FRC_FP
* @Last modified by:   Dome
* @Last modified time: 2016-07-16T12:27:39+02:00
*/



#ifndef COMPRESSION_H
#define COMPRESSION_H

void compress_1d(float* data, int *sizes, int bits_per_block, char* dest);
void compress_2d(float* data, int *sizes, int bits_per_block, char* dest);
void compress_3d(float* data, int *sizes, int bits_per_block, char* dest);

#endif
