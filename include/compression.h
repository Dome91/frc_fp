#ifndef COMPRESSION_H
#define COMPRESSION_H

void compress_1d(float* data, int *sizes, int bits_per_block, char* dest);
void compress_2d(float* data, int *sizes, int bits_per_block, char* dest);
void compress_3d(float* data, int *sizes, int bits_per_block, char* dest);

#endif
