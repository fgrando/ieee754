#include "fm_util.h"
#include "fm_manip.h"

/*
 * This implementations in this library are based on the book:
 * Software Manual for the Elementary Functions (William J. Cody, 1980)
 */

// INTXP, SETXP and ADX implementation based on the book
// Software Manual for the Elementary Functions by William J. Cody Jr.

// returns the integer representation of the exponent
// use mask&shift to get the value, check endianness!
// it is better to use frexpf ()
int INTXP(float x)
{
    // we must account that the value stored in the
    // 8bit exponent is biased by -127 (IEEE754)
    unsigned int raw = *((unsigned int*)&x);
    unsigned int exp = (raw & FM_EXPONENT_BITS) >> FM_MANTISSA_LEN;
    return (int)exp + FM_EXPONENT_BIAS;
}


// set the exponent of x to n
// use mask&shift to set the value, check endianness!
float SETXP(float x, int n)
{
    // the exponent to be stored must be equal to N
    // so we must compensate the bias that IEEE754 requires:
    // N + offset - 127 = 0
    // when N is zero, bias = 127.
    float result = 0.0;
    unsigned int* pIntX = (unsigned int*)&x;
    unsigned int* pIntRes = (unsigned int*)&result;
    unsigned int temp;
    // set the exponent
    temp = ((n - FM_EXPONENT_BIAS) << FM_MANTISSA_LEN);
    *pIntRes |= temp;
    // copy the rest
    temp = (*pIntX) & FM_EXPONENT_BITS_N;
    *pIntRes |= temp;
    return result;
}


// augments the integer exponent in the x by n
// use mask&shift to set the value, check endianness!
float ADX(float x, int n)
{
    int exp = (INTXP(x) + n) % 0xFF; // be sure we stay in range
    return SETXP(x, exp);
}


int INTRND(float x) {
    return (int)((x < 0) ? (x - 0.5f) : (x + 0.5f));
}


// set the signal of the floating number
float SETSGN(float x, int bitValue)
{
    unsigned int* pIntX = (unsigned int*)&x;

    if (bitValue)
    {
        *pIntX |= FM_SIGNAL_BIT; // put 1
    }
    else
    {
        *pIntX &= FM_SIGNAL_BIT_N; // put 0
    }

    return x;
}