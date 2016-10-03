## Synopsis
This is FRC_FP, a library for fixed-rate compressing of floating point values written in C.
It implements the compression scheme presented in:

Peter Lindstrom
  "Fixed-Rate Compressed Floating-Point Arrays"
  IEEE Transactions on Visualization and Computer Graphics,
    20(12):2674-2683, December 2014
  doi:10.1109/TVCG.2014.2346458

While the algorithm presented in the paper works on a fixed-point representation of decimal values, as it was designed with hardware implementations in mind,
this library uses the built - in floating point representation of values.
I implemented this only for educational purposes.
At the moment, only 1 - dimensional arrays can be compressed and decompressed.

## Installation
git clone https://github.com/Dome91/frc_fp.git
cd frc_fp
mkdir build
cd build
cmake ..
make
sudo make install

## Code Example
# Compression
unsigned char* compressed = FRC_FP.compress(data, dims, sizes, bits_per_block);

#Decompression
float* decompressed = FRC_FP.decompress(data, dim, sizes, bits_per_block);

For more information, regarding parameters and such, take a look at include/frc_fp.h
