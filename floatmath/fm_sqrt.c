#include "fmath.h"
#include "fm_util.h"

/*
 *  This implementations in this library are based on the book:
 *  Software Manual for the Elementary Functions (William J. Cody, 1980)
 */

/*
 *  The square root is computable for non-negative numbers.
 *
 *  Assume X > 0 and let X = f*B^e, 1/B <= f < 1, 2 <= B <= 16.
 *  Then for even e: sqrt(X) = sqrt(f) * B^(e/2)
 *       for off  e: sqrt(X) = [sqrt(f)/srqt(B)] * B^[(e+1)/2]
 *
 *  For example sqrt(25):
 *      25 = 1.5625 * 2^4
 *      sqrt(1.5625) * 2^(4/2) = 5
 *
 *  Note: this can also be implemented directly with Heron's algorithm:
 *      float guess = 6;
 *      float value = 42;
 *      for (int i = 0; i < 3; i++) {
 *          guess = 0.5f * (guess + value / guess);
 *      }
*/
float fm_sqrt(float x)
{
    float result = 0.0f;

    // compute for positive values
    if (x > 0.0f)
    {
        // extract the exponent
        int N = INTXP(x);

        // extract the significand
        float f = SETXP(x, 0);

        // initial approximations to find y0 (guess from Heron's/Newton iteration)
        float y0 = 0.41731f + 0.59016f * f;

        // calculate yj j = 1...n
        // we have 23+1 bits for f = 24 bits, then 2 iterations is sufficient
        // yi = 0.5 *(yi-1 + f / yi-1)
        float y1 = 0.5f * (y0 + f / y0);
        float y2 = 0.5f * (y1 + f / y1);
        float y3 = 0.5f * (y2 + f / y2);
        float yj = y3;

        // Is N odd ? then divide by the base
        if (N & 1)
        {
            // multiplication is usually faster than division
            // then yj / sqrt(B) is implemented likje yj * sqrt(B/2)
            yj = yj * FM_SQRT_05;
            N = N + 1;
        }

        int M = N / 2;

        // scale to the correct result
        result = ADX(yj, M);
    }
    else if (x < 0.0f) // we dont deal with imaginaries here
    {
        result = FM_FLOAT_NAN; // NaN
    }
    else // square of zero is zero
    {
        result = x;
    }

    return result;
}
