#ifndef FRC_FP_H
#define FRC_FP_H

struct frc_fp{
  char* (*compress)(float* values, int dim, int* sizes, int bitrate);
  float* (*decompress)(char* values, int dim, int* sizes, int bitrate);
};

extern const struct frc_fp FRC_FP;
#endif
