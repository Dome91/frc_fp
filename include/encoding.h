/**
* @Author: Dominique Metz <Dome>
* @Date:   2016-07-16T12:23:30+02:00
* @Email:  DominiqueMetz@gmx.de
* @Project: FRC_FP
* @Last modified by:   dome
* @Last modified time: 2016-07-18T16:40:31+02:00
*/

#ifndef ENCODING_H
#define ENCODING_H

#include "common.h"

/**
 * Encodes the block
 * @param fc                  Block of values
 * @param num_values_in_group How much values are in each group
 * @param width_of_group      Width of each group
 * @param bits_per_block      Bit budget of a block
 * @param num_groups          Number of groups
 * @param bs                  Reference to BitStream struct
 */
void encode(float_cast* fc, char *num_values_in_group, char* width_of_group, int bits_per_block, int num_groups, BitStream *bs);
void decode(float_cast* fc, int count, int width, int bits_per_block);

void write_bit(char bit, BitStream *bs);
void write_byte(char byte, BitStream *bs);

#endif
