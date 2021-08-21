#include "fmath.h"
#include "fm_util.h"

/*
 *  This implementations in this library are based on the book:
 *  Software Manual for the Elementary Functions (William J. Cody, 1980)
 */

float REDUCE(float V) {
    return (float)((int)(16.0 * V)) * 0.0625f;
}

/*
    In Fortran power is defined mathematically as
        x^y = exp(y*ln(x))
    But the obvious implementation using existing software
    for logarithm and exponential results in large errors.
*/
float fm_pow(float x, float y)
{
    float result = 0.0f;

    // compute for positive values
    if (x > 0.0f)
    {
        // extract the exponent
        int m = INTXP(x);

        // extract the significand
        float g = SETXP(x, 0);

        float A1[17] = {
            1.0000000000f,
            0.9576032807f,
            0.9170040432f,
            0.8781260802f,
            0.8408964153f,
            0.8052451660f,
            0.7711054127f,
            0.7384130730f,
            0.7071067812f,
            0.6771277735f,
            0.6484197773f,
            0.6209289060f,
            0.5946035575f,
            0.5693943174f,
            0.5452538663f,
            0.5221368912f,
            0.5000000000f,
        };

        float A2[9] = {
            -0.0423967242f,
            -0.0388779640f,
            -0.0356512666f,
            -0.0326923132f,
            -0.0299789906f,
            -0.0274909139f,
            -0.0252092481f,
            -0.0231170058f,
            -0.0211983621f,
        };

        int p = 1;
        if (g <= A1[9]) p = 9;
        if (g <= A1[p+4]) p += 4;
        if (g <= A1[p + 2]) p += 2;

        float num = (g - A1[p + 1]) - A2[(p + 1) / 2];
        float den = g + A1[p + 1];
        float z = num / den;

        z = z + z;

        // at this point z <= 0.044

        // minimax polynomial approx. z*P(z^2)
        const float p1 = 0.83357541E-1f;
        const float v = z * z;
        float R = p1 * v * z;

        // evaluation of U2 = (z + R)*log2(e)
        const float K = 0.44269505f;
        R = R + K * R;
        const float U2 = (R + z * K) + z;

        // U1 = FLOAT((k*m-r)*16-p)*0.0625; k=1, r=0;
        const float  U1 = ((float)m * 16.0f - p) * 0.0625f;

        // REDUCE(y)
        float Y1 = REDUCE(y);
        const float Y2 = y - Y1;

        float W = U2 * y + U1 * Y2;
        float W1 = REDUCE(W);
        float W2 = W - W1;
        W = W1 + U1 + Y1;
        W1 = REDUCE(W);
        W2 = W2 + (W - W1);
        W = REDUCE(W2);

        int IW1 = (int)(16 * (W1 + W));
        W2 = W2 - W;

        int BIGX = (16 * 128 - 1); // BIGX = INT(16*log2(XMAX)-1);
        int SMALLX = (16 * -126 + 1); // SMALLX = INT(16*log2(XMIN)+1)

        if (W > BIGX) return 0.0;
        if (W < SMALLX) return 0.0;

        int I = (IW1 < 0) ? 0 : 1;

        IW1 += 1;
        if (W2 > 0.0f) W2 -= 1 / 16.0f;

        int m_ = IW1 / 16 + I;
        int p_ = 16 * m_ - IW1;


        const float q1 = 0.69314675E0f;
        const float q2 = 0.24018510E0f;
        const float q3 = 0.54360383E0f;
        float Z = ((q3 * W2 + q2) * W2 + q1) * W2;

        Z = A1[p_ + 1] + A1[p_ + 1] * Z;

        result = ADX(Z, m_);
    }
    else // return zero
    {
        result = x;
    }

    return result;
}
