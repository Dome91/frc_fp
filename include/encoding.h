/**
* @Author: Dominique Metz <Dome>
* @Date:   2016-07-16T12:23:30+02:00
* @Email:  DominiqueMetz@gmx.de
* @Project: FRC_FP
* @Last modified by:   dome
* @Last modified time: 2016-09-23T18:29:01+02:00
*/

#ifndef ENCODING_H
#define ENCODING_H

#include "common.h"

/**
 * Encodes the block
 * @param fc                  Block of values
 * @param num_values_in_group How many values are in each group
 * @param width_of_group      Width of each group
 * @param bits_per_block      Bit budget of a block
 * @param num_groups          Number of groups
 * @param bs                  Reference to BitStream struct
 */
void encode(float_cast* fc, uint8_t* num_values_in_group, uint8_t* width_of_group, int32_t bits_per_block, int32_t num_groups, BitStream *bs);

/**
 * Decodes the block
 * @param  fc                  Block of values
 * @param  num_values_in_group How many values are in each group
 * @param  bits_per_block      Bit budget of a block
 * @param  num_groups          Number of groups
 * @param  bs                  Reference to BitStream struct
 * @return                     Returns the exponent of the group
 */
uint8_t decode(float_cast* fc, uint8_t* num_values_in_group, int32_t bits_per_block, int32_t num_groups, BitStream *bs);

/**
 * Writes a bit into buffer and flushes buffer to memory if full
 * @param bit Bit to be written
 * @param bs  Reference to BitStream struct
 */
void write_bit(uint8_t bit, BitStream *bs);

/**
 * Writes a byte into the buffer and flushes buffer to memory if full
 * @param byte Byte to be written
 * @param bs   Refernce to BitStream struct
 */
void write_byte(uint8_t byte, BitStream *bs);

/**
 * Reads byte from memory
 * @param  bs Refernce to BitStream struct
 * @return    Byte
 */
uint8_t read_byte(BitStream *bs);

/**
 * Reads a bit from buffer or memory
 * @param  bs Refernce to BitStream struct
 * @return    Bit
 */
uint8_t read_bit(BitStream *bs);

#endif
