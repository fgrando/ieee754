#include "fmath.h"
#include "fm_util.h"

/*
 *  This implementations in this library are based on the book:
 *  Software Manual for the Elementary Functions (William J. Cody, 1980)
 */

static float sincos_f(float x, float y, float sgn);

float fm_sin(float x)
{
    float result = 0.0f;

    if (x < 0.0f)
    {
        float y = -x;
        result = sincos_f(x, y, -1.0f);
    }
    else
    {
        float y = x;
        result = sincos_f(x, y, 1.0f);
    }

    return result;
}

float fm_cos(float x)
{
    // the use of |x| guarantees that the identity cos(-x) = cos(x)
    // we get the absolute of x by setting its signal to zero
    const float y = SETSGN(x, 0) + FM_PI_2;

    return sincos_f(x, y, 1.0f);
}

static float sincos_f(float x, float y, float sgn)
{
    float result = 0.0f;

    // There are several conditions that YMAX must satisfy:
    //     1. XN*C1 and (XN-0.5)*C1 must be exactly representable for y < YMAX
    //     2. round error in last digit of y should not lead relative error in sin greater in magnitude than B^(t/2) for y < YMAX
    //     3. N should be representable as an integer
    // Considering we have B = 2 (binary), t = 24 (bits of precision 23+1)
    //     YMAX is defined as pi*B^(t/2)
    const float YMAX = 12867.0f;

    // compute for values smaller than maximum
    if (y < YMAX)
    {
        // rounds y to the nearest ingeter and extract the exponent
        const float ONE_OVER_PI = 0.31830987f;
        int N = INTRND(y*ONE_OVER_PI);
        float XN = (float)N;

        // If N is odd invert the signal
        if (N & 1)
        {
            sgn *= -1.0f;
        }

        // "COS wanted" means |x| != y
        float absX = SETSGN(x, 0);
        if (absX != y)
        {
            // this is equivalent to adding pi/2 to x
            // but leads to reater accuracy in f when done at this point.
            // XN does not have an integer value anymore
            XN = XN - 0.5f;
        }

        // considering the number of significand bits C1 and C2 are:
        const float C1 = 3.1406250f; // 201/64;
        const float C2 = 0.00096765358f;
        float f = (absX - XN * C1) - XN * C2;

        const float EPS = 0.000244140625f; // B^(-t/2), B=2, t=24
        float absF = SETSGN(f, 0);
        if (absF < EPS) {
            result = f;
        }
        else
        {
            const float g = f * f;

            // constants for our number of significand bits (24)
            const float r1 = -0.1666665668E+0f;
            const float r2 =  0.8333025139E-2f;
            const float r3 = -0.1980741872E-3f;
            const float r4 =  0.2601903036E-5f;

            // using nested multiplication:
            float Rg = (((r4 * g + r3) * g + r2) * g + r1) * g;

            result = f + (Rg * f); // do not use f * (1 + R(g))
        }

        result *= sgn;
    }
    else // x is too big
    {
        result = 0.0f;
    }

    return result;
}

