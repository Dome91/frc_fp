/**
* @Author: Dominique Metz <Dome>
* @Date:   2016-07-15T13:17:32+02:00
* @Email:  DominiqueMetz@gmx.de
* @Project: FRC_FP
* @Last modified by:   dome
* @Last modified time: 2016-09-22T12:46:15+02:00
*/

#include "common.h"

#ifndef COMPRESSION_H
#define COMPRESSION_H

/**
 * Compresses a one dimensional array of floating point values
 * @param data           Values to be compressed
 * @param sizes          Number of values
 * @param bits_per_block Number of bits for one block
 * @param dest           Memory address for storing compressed data
 * @param num_blocks     Number of blocks the values are divided into
 */
void compress_1d(float* data, int32_t *sizes, int32_t bits_per_block, uint8_t* dest, int32_t num_blocks);
/*
void compress_2d(float* data, int32_t *sizes, int32_t bits_per_block, uint8_t* dest, int32_t num_blocks);
void compress_3d(float* data, int32_t *sizes, int32_t bits_per_block, uint8_t* dest, int32_t num_blocks);
*/
/**
 * Decompresses a one dimensional array of compressed floating point values
 * @param data           Compressed floating point values
 * @param sizes          Number of values
 * @param bits_per_block Number of bits per block that were used for compression
 * @param dest           Memory address for storing the uncompressed floating point values
 * @param num_blocks     Number of blocks the floating point values were divided into
 */
void decompress_1d(uint8_t* data, int32_t *sizes, int32_t bits_per_block, float* dest, int32_t num_blocks);
/*
void decompress_2d(uint8_t* data, int32_t *sizes, int32_t bits_per_block, float* dest, int32_t num_blocks);
void decompress_3d(uint8_t* data, int32_t *sizes, int32_t bits_per_block, float* dest, int32_t num_blocks);
*/
/**
 * Flushes to left over bits in the buffer to memory
 * @param bs BitStream controlling the writing and read of memory
 */
void flush(BitStream *bs);

#endif
