#ifndef FLOAT_MATH_UTIL_H_INCLUDED_
#define FLOAT_MATH_UTIL_H_INCLUDED_

#define FM_SQRT_05   0.70710678f    // sqrt(0.5)
#define FM_PI_2      1.57079637f    // pi/2
#define FM_PI_4      0.78539816f    // pi/4
#define FM_LOG_e     0.43429448f    // log(e)
#define FM_FLOAT_MAX 3.402823e+38f  // XMAX
#define FM_FLOAT_MIN 1.175494e-38f  // XMIN
#define FM_FLOAT_NAN 0x7fc00000     // Not a Number

int INTXP(float x);

float SETXP(float x, int n);

float ADX(float x, int n);

int INTRND(float x);

float SETSGN(float x, int bitValue);


#endif // FLOAT_MATH_UTIL_H_INCLUDED_