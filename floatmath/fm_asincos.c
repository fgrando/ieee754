#include "fmath.h"
#include "fm_util.h"

/*
 *  This implementations in this library are based on the book:
 *  Software Manual for the Elementary Functions (William J. Cody, 1980)
 */

// we need sqrt() for acos/asin
extern float fm_sqrt(float);

// local functions
static float calc_polyR(float g);
static float asincos_f(float x, int flag);


float fm_asin(float x)
{
    return asincos_f(x, 0);
}

float fm_acos(float x)
{
    return asincos_f(x, 1);
}

static float asincos_f(float x, int flag)
{
    float result = 0.0f;
    int i = 0;

    // Y = |x|
    float Y = SETSGN(x, 0);

    if (Y > 0.5f)
    {
        i = 1 - flag;
        if (Y > 1.0f)
        {
            // error
            Y = FM_FLOAT_MAX;
        }

        const float g = (1.0f - Y) / 2.0f;
        const float Y = -2.0f * fm_sqrt(g);
        const float Rg = calc_polyR(g);
        result = Y * Rg + Y;
    }
    else
    {
        i = flag;
        const float eps = 0.00024414062f; // B^(-t/2) B=2 t=24
        if (Y < eps)
        {
            result = Y;
        }
        else
        {
            const float g = Y * Y;
            const float Rg = calc_polyR(g);
            result = Y * Rg + Y;
        }
    }

    const float a[2] = { 0.0f, FM_PI_4 };
    const float b[2] = { FM_PI_2, a[1] };

    if (0 == flag)
    {
        result = (a[i] + result) + a[i];
        if (x < 0.0f)
        {
            result = -result;
        }
    }
    else
    {
        if (x < 0)
        {
            result = (b[i] + result) + b[i];
        }
        else
        {
            result = (a[i] - result) + a[i];
        }
    }

    return result;
}

static float calc_polyR(float g)
{
    const float p1 = -0.27516555290569E+1f;
    const float p2 =  0.29058762374859E+1f;
    const float p3 = -0.59450144193246E+0f;
    const float q0 = -0.16509933202424E+2f;
    const float q1 =  0.24864728969164E+2f;
    const float q2 = -0.10333867072113E+2f;
    // q3 = 1.0 so it is not used

    const float gPg = ((p3 * g + p2) * g + p1) * g;
    const float Qg = ((g + q2) * g + q1) * g + q0;
    const float Rg = gPg / Qg;

    return Rg;
}
