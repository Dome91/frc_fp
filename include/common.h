#ifndef COMMON_H
#define COMMON_H

typedef union {
  float f;
  struct {
    uint32_t mantissa : 23;
    uint32_t exponent : 8;
    uint32_t sign : 1;
  } parts;
} float_cast;

#endif
