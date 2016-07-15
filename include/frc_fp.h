#ifndef FRC_FP_H
#define FRC_FP_H

struct frc_fp{
  /**
   * Compresses the given floating point values, using bits_per_block bits for every blocks
   * A block is is (4^dim) floats
   * @param  values         Floating point values to be compressed
   * @param  dim            Dimension of the values
   * @param  sizes          Size of each dimension
   * @param  bits_per_block Number of bits each block is encoded to
   * @return                The compressed values
   */
  char* (*compress)(float* values, int dim, int* sizes, int bits_per_block);

  /**
   * Decompresses the floating point values formerly compressed by the cmpression procedure
   * @param  values         Compressed floating point values
   * @param  dim            Dimension of the values
   * @param  sizes          Size of each dimension
   * @param  bits_per_block Number of bits each block was encoded to
   * @return                The decompressed values
   */
  float* (*decompress)(char* values, int dim, int* sizes, int bits_per_block);
};

/**
 * Returns the number of blocks the values are divided into
 * @param  dim   Dimension of the values
 * @param  sizes Size of each dimension
 * @return       Number of blocks the values are divided into
 */
long get_num_blocks(int dim, int* sizes);

extern const struct frc_fp FRC_FP;
#endif
