#include "transformation.h"

void fwd_transform(float_cast* fc, int start, int stride){
  float x = fc[start].f;
	float y = fc[start + stride].f;
	float z = fc[start + 2 * stride].f;
	float w = fc[start + 3 * stride].f;

	const float c = 1.36778f;

	w -= x;
  w /= 2;
  x += w;
  y -= z;
  y /= 2;
  z += y;
	z -= x;
  z /= 2;
  x += z;
	y /= 2;
  y -= c*w;
  y /= 2;
  w += c*y;
  w *= 2;  //y /= 2; is w *= 2; in the related paper

	fc[start].f 							= x;
	fc[start + stride].f 			= y;
	fc[start + 2 * stride].f 	= z;
	fc[start + 3 * stride].f 	= w;
}

void inv_transform(float_cast* fc, int start, int stride){
  float x = fc[start].f;
	float y = fc[start + stride].f;
	float z = fc[start + 2 * stride].f;
	float w = fc[start + 3 * stride].f;

	const float c = 1.36778;

	w /= 2;
  w -= c * y;
  y *= 2;
  y += c * w;
  y *= 2;
  x -= z;
  z *= 2;
  z += x;
  z -= y;
  y *= 2;
  y += z;
  x -= w;
  w *= 2;
  w += x;

	fc[start].f 							= x;
	fc[start + stride].f 			= y;
	fc[start + 2 * stride].f 	= z;
	fc[start + 3 * stride].f 	= w;
}
