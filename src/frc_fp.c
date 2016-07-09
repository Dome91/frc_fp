#include <stdlib.h>
#include "frc_fp.h"

char* compress(float* values, int dim, int* sizes, int bitrate){
  //TODO: Implement compression
}

float* decompress(char* values, int dim, int* sizes, int bitrate){

}

const struct frc_fp FRC_FP = {
    .compress   = compress,
    .decompress = decompress,
};
