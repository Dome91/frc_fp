/**
* @Author: Dominique Metz <Dome>
* @Date:   2016-07-15T13:17:32+02:00
* @Email:  DominiqueMetz@gmx.de
* @Project: FRC_FP
* @Last modified by:   dome
* @Last modified time: 2016-07-19T16:37:49+02:00
*/



#ifndef COMPRESSION_H
#define COMPRESSION_H

void compress_1d(float* data, int *sizes, int bits_per_block, char* dest, int num_blocks);
void compress_2d(float* data, int *sizes, int bits_per_block, char* dest, int num_blocks);
void compress_3d(float* data, int *sizes, int bits_per_block, char* dest, int num_blocks);

void decompress_1d(char* data, int *sizes, int bits_per_block, float* dest, int num_blocks);
void decompress_2d(char* data, int *sizes, int bits_per_block, float* dest, int num_blocks);
void decompress_3d(char* data, int *sizes, int bits_per_block, float* dest, int num_blocks);

#endif
