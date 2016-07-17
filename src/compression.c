/**
* @Author: Dominique Metz <Dome>
* @Date:   2016-07-08T12:31:13+02:00
* @Email:  DominiqueMetz@gmx.de
* @Project: FRC_FP
* @Last modified by:   dome
* @Last modified time: 2016-07-17T12:55:27+02:00
*/

#include "common.h"
#include "compression.h"
#include "transformation.h"
#include "normalization.h"

void compress_1d(float* data, int *sizes, int bits_per_block, char* dest, int num_blocks){
  int blocksize = 4;        // Size of 1-dimensional block
  int block = 0;            // The current block processed
  float_cast fc[blocksize]; // Contains the values of the current block
  char width[blocksize];    // Contains the width of groups

  // While there are still blocks to process
  while(block < num_blocks){
    data += block * blocksize;  // Jump to the beginning of the current block
    // Copy values into the block
    for(int i = 0; i < blocksize; ++i){
      fc[i].f = data[i];
    }

    // Normalize and transform values
    normalize(fc, blocksize);
    fwd_transform(fc, 0, 1);

    // Get the width of all four groups
    int msb = 0;
    width[0] = get_width_of_group(fc + 3, 1, msb);
    width[1] = get_width_of_group(fc + 2, 1, msb);
    width[2] = get_width_of_group(fc + 1, 1, msb);
    width[3] = get_width_of_group(fc + 0, 1, msb);

    //TODO: Implement encoding
  }
}
void compress_2d(float* data, int *sizes, int bits_per_block, char* dest){

}
void compress_3d(float* data, int *sizes, int bits_per_block, char* dest){

}
