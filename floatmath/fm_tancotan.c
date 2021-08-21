#include "fmath.h"
#include "fm_util.h"

/*
 *  This implementations in this library are based on the book:
 *  Software Manual for the Elementary Functions (William J. Cody, 1980)
 */

/*
 *  The (co)tangent function is calculated based on the followin definition:
 *  Considering the given input X:
 *      X = N * (pi/2) + f, where |f| <= pi/4
 *  Then:
 *      tan(X) = tan(f), N even
 *      tan(X) = -1/tan(f), N odd
 *  and
 *      cotan(X) = 1/tan(X)
 *
 * Accuracy gets really bad when the input gets closer to +-pi/2.
*/
float fm_tancotan(float X, float Y, int IFLAG)
{
    float result = 0.0f;
    const float YMAX = 6433.0f; // B^(t/2)*pi/2 --> 2^(24/2)*pi/2

    // step 5
    if (Y > YMAX)
    {
        // step 6 - error
        return 0.0f;
    }

    // step 7
    const float TWO_OVER_PI = 0.6366197723f;
    int N = INTRND(X * TWO_OVER_PI);
    const float XN = (float)N;

    // step 8 - multistep argument reduction
    const float C1 = 1.57080078125f;
    const float C2 = -4.45445510338076867e-6f;
    const float f = (X - XN * C1) - (XN * C2); // we can do this because we have guard digit

    // step 9
    float XNUM = 0.0f;
    float XDEN = 0.0f;
    const float absF = SETSGN(f, 0);
    const float eps = 0.00024414062f;// B^(-t/2) --> 2^-12
    if (absF < eps)
    {
        // step 10
        XNUM = f;
        XDEN = 1.0f;
    }
    else
    {
        // step 11
        const float g = f * f;

        // step 12
        //const float p0 = 0.1000000000000e+1f;
        const float p1 = -0.958017723E-1f;
        const float q0 = 0.100000000E+1f;
        const float q1 = -0.429135777E+0f;
        const float q2 = 0.971685835E-2f;

        // Evaluate using nested multiplication
        const float fPg = (p1 * g * f) + f; 
        const float Qg = ((q2 * g + q1) * g) + q0;

        XNUM = fPg;
        XDEN = Qg;
    }

    if (0 == IFLAG)
    {
        // step 14
        if (N & 1)
        {
            // A
            XNUM = -XNUM;
            result = XDEN / XNUM;
        }
        else
        {
            // D
            result = XNUM / XDEN;
        }
    }
    else
    {
        // step 14
        if (N & 1)
        {
            // C
            XNUM = -XNUM;
            result = XNUM / XDEN;
        }
        else
        {
            // B
            result = XDEN / XNUM;
        }
    }

    return result;
}

float fm_tan(float x)
{
    // step 2
    float y = SETSGN(x, 0);
    return fm_tancotan(x, y, 0);
}

float fm_cotan(float x)
{
    float result = 0.0f;
    float y = SETSGN(x, 0);
    const float epsl = 1.17549393043e-38f;
    // step 3
    if (y >= epsl) {
        result = fm_tancotan(x, y, 1);
    }

    // step 4 - result already set to error

    return result;
}