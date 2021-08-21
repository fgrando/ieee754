#include "fmath.h"
#include "fm_util.h"

/*
 *  This implementations in this library are based on the book:
 *  Software Manual for the Elementary Functions (William J. Cody, 1980)
 */

/*
 *  The square root is computable for non-negative numbers.
 *  Considering X normalized: X = f*B^m, 1/B <= f < 1 and B=2 (binary)
 *  We determine g and n in such a way that:
 *      f = g*2^(-n) where 1/sqrt(2) <= g < sqrt(2)
 *  then
 *      ln(X) = (k * m - n) * ln(2) + ln(g)
 *  and
 *      log(X) = log(e) * ln(X) = ln(x)/ln(10)
 *
 *  The term (k * m - n) * ln(2) dominates for most values of X and
 *  small round errors in ln(g) do not alter the value of ln(X) BUT
 *  once this term vanishes (X = g) the accuracy of ln(g) becomes vital.
 */
static float lnlog10(float x, int doLog10)
{
    float result = 0.0f;

    // only compute positive values
    if (x > 0.0f)
    {
        // determine N and a scaled value of f
        // such that X = f * 2^N,   0.5 <= f < 1
        // let's use the exponent in x as an initial estimative
        int N = INTXP(x);

        // the significand in x is also used as initial estimate of f
        float f = SETXP(x, 0);
        // radix B is assumed to be 2^k, the k = 1 and
        // 0.5 <= f < 1 must be satisfied below

        // C0 is sqrt(0.5)
        const float C0 = FM_SQRT_05;
        float znum, zden;
        if (f > C0)
        {
            // determine znum and zden:
            // do not combine constants
            znum = (f - 0.5f) - 0.5f;
            zden =  f * 0.5f  + 0.5f;
        }
        else
        {
            N = N - 1;
            // determine znumand zden:
            znum = f - 0.5f;
            zden = znum * 0.5f + 0.5f;
        }

        // rational approximation of r(z ^ 2)
        // constants for number of significand bits b <= 24:
        const float a0 = -0.5527074855E+0f;
        const float b0 = -0.6632718214E+0f;
        const float b1 = -0.1000000000E+0f;

        const float z = znum / zden;
        const float w = z * z;

        // polynomials Aw and Bw
        const float Aw = w + a0;
        const float Bw = (w + b1) * w + b0;

        const float rz2 = w * (Aw / Bw);
        const float Rz = z + z * rz2;

        // 12
        const float XN = (float)N;
        const float C1 = 0.693359375f;// 355/512;
        const float C2 = -2.1219444170128554E-4f;

        result = (XN * C2 + Rz) + XN * C1;

        if (doLog10) {
            const float C3 = FM_LOG_e; // log(e)
            result *= C3;
        }
    }
    else
    {
        result = SETXP(-1.0, 128); // -inf
    }

    return result;
}

float fm_log(float x)
{
    return lnlog10(x, 0);
}

float fm_log10(float x)
{
    return lnlog10(x, 1);
}

