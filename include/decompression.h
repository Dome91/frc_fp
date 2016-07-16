/**
* @Author: Dominique Metz <Dome>
* @Date:   2016-07-15T13:19:56+02:00
* @Email:  DominiqueMetz@gmx.de
* @Project: FRC_FP
* @Last modified by:   Dome
* @Last modified time: 2016-07-16T12:27:45+02:00
*/



#ifndef DECOMPRESSION_H
#define DECOMPRESSION_H

void decompress_1d(char* data, int *sizes, int bits_per_block, float* dest);
void decompress_2d(char* data, int *sizes, int bits_per_block, float* dest);
void decompress_3d(char* data, int *sizes, int bits_per_block, float* dest);

#endif
