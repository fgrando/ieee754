#include "fmath.h"
#include "fm_util.h"

/*
 *  This implementations in this library are based on the book:
 *  Software Manual for the Elementary Functions (William J. Cody, 1980)
 */

/*
 * X = N * ln(C) + g; |g| <= ln(C)/2; C = 2, since our radix B is 2.
 * then:
 *      exp(X) = exp(g)*C^N
 *
 * The accuracy of the function relies on accuracy of g.
 *      g = [(X1 - N*C1) +X2] - N*C2
 */
float fm_exp(float x)
{
    // largest machine number less than ln(XMAX)
    const float BIGX = 88.7228317261f;

    // smallest machine number greater than ln(XMIN)
    const float SMALLX = -87.3364257812f;

    float result = 0.0f;
    // compute for positive values
    if (x > BIGX)
    {
        result = FM_FLOAT_MAX; // XMAX
    }
    else if (x < SMALLX)
    {
        result = 0.0f;
    }
    else
    {
        // EPS = (B^-t)/2
        const float EPS = 2.9802e-08f;
        const float absX = SETSGN(x, 0); // |x|
        if (absX < EPS)
        {
            result = 1.0f;
        }

        // round X/ln(2) to the nearest integer
        const float ONE_OVER_LN2 = 1.4426950f;
        int N = INTRND(x * ONE_OVER_LN2);
        const float XN = (float)N;

        // determine g
        const float C1 = 0.693359375f;
        const float C2 = -2.1219444E-4f;
        const float g = (x - XN * C1) - XN * C2; // do this instead of g=x-XN*ln(2)

        // approximation of exp(9)/2 for b <= 29 (we have b=24)
        const float p0 = 0.25;
        const float p1 = 0.0041602887f;
        const float q0 = 0.5f;
        const float q1 = 0.049987178f;

        // form z = g^2 first.
        const float z = g * g;
        const float gPz = (p1 * z + p0) *g;
        const float Qz = q1 * z + q0;

        // finally
        const float Rg = 0.5f + gPz / (Qz - gPz);
        N += 1;
        result = ADX(Rg, N);
    }

    return result;
}
