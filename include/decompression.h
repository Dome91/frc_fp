#ifndef DECOMPRESSION_H
#define DECOMPRESSION_H

void decompress_1d(char* data, int *sizes, int bits_per_block, float* dest);
void decompress_2d(char* data, int *sizes, int bits_per_block, float* dest);
void decompress_3d(char* data, int *sizes, int bits_per_block, float* dest);

#endif
