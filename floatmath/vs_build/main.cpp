#include <stdio.h>
#include <math.h> // to compare with

#include "../fmath.h"

int main()
{
    float actual, expected, val = 0.4986419380f;
#if 1
    float step = 0.00001f;
    unsigned long long counter = 0;
    unsigned long long fails = 0;
    float PI = 3.1415926535897932384f;
    for (float i = -PI; i < PI; i += step)
    {
        val = i;
        actual = fm_tan(val);
        expected = tanf(val);
        float eps = 0.00001f;
        if (fabs(expected- actual) > eps)
        {
            printf("tanf %.6f\texpected %.10f actual %.10f\tdelta: %f\n", val, expected, actual, fabs(expected - actual));
            fails++;
        }
        counter++;
    }

    printf("\ntests: %lld fails: %lld %f%%\n", counter, fails, (fails/(double)counter)*100);

    return 0;

    val = 4.7123408318f;
    actual = fm_tan(val);
    expected = tanf(val);
#endif
    expected = sqrtf(val);
    actual = fm_sqrt(val);
    printf("sqrt(%f)\texpected %.10f actual %.10f\tdelta: %f\n", val, expected, actual, expected - actual);

    expected = val;
    actual = fm_sqrt(val*val);
    printf("sqrt(%f^2)=%f\texpected %.10f actual %.10f\tdelta: %f\n", val, val, expected, actual, (expected - actual));


    printf("\n\n");
    expected = log10f(val);
    actual = fm_log10(val);
    printf("log10(%f)\texpected %.10f actual %.10f\tdelta: %f\n", val, expected, actual, expected - actual);

    expected = fm_log10(val);
    actual = fm_log10(val * 11.0f / 10.0f) - fm_log(1.1f);
    printf("log10(%f)=log10(%f*11/10) - log10(1.1)\texpected %.10f actual %.10f\tdelta: %f\n", val, val, expected, actual, expected - actual);


    printf("\n\n");
    expected = logf(val);
    actual = fm_log(val);
    printf("log(%f)\texpected %.10f actual %.10f\tdelta: %f\n", val, expected, actual, expected - actual);

    expected = fm_log(val);
    actual = -fm_log(1.0f/val);
    printf("ln(%f)=-ln(1/%f)\texpected %.10f actual %.10f\tdelta: %f\n", val, val, expected, actual, expected - actual);

    expected = fm_log(val*val);
    actual = 2.0f*fm_log(val);
    printf("ln(%f^2)=2*ln(%f)\texpected %.10f actual %.10f\tdelta: %f\n", val, val, expected, actual, expected - actual);


    printf("\n\n");
    expected = sinf(val);
    actual = fm_sin(val);
    printf("sin(%f)\texpected %.10f actual %.10f\tdelta: %f\n", val, expected, actual, expected - actual);

    expected = cosf(val);
    actual = fm_cos(val);
    printf("cos(%f)\texpected %.10f actual %.10f\tdelta: %f\n", val, expected, actual, expected - actual);



    printf("\n\n");
    expected = expf(val);
    actual = fm_exp(val);
    printf("exp(%f)\texpected %.10f actual %.10f\tdelta: %f\n", val, expected, actual, expected - actual);


    printf("\n\n");
    expected = 1.0f;
    actual = fm_exp(val) * fm_exp(-val);
    printf("exp(%f)*exp(-%f)=1\texpected %.10f actual %.10f\tdelta: %f\n", val, val, expected, actual, expected - actual);


    printf("\n\n");
    val = 31;
    expected =  powf(val,2.0f);
    actual = fm_pow(val,2.0f);
    printf("pow(%f, %f)\texpected %.10f actual %.10f\tdelta: %f\n", val, 2.0, expected, actual, expected - actual);


    printf("\n\n");
    val = 1;
    expected = asinf(val);
    actual = fm_asin(val);
    printf("asin(%f)\texpected %.10f actual %.10f\tdelta: %f\n", val, expected, actual, expected - actual);

    expected = acosf(val);
    actual = fm_acos(val);
    printf("acos(%f)\texpected %.10f actual %.10f\tdelta: %f\n", val, expected, actual, expected - actual);

    val = 0.5180211663f;
    expected = acosf(val);
    actual = fm_acos(val);
    printf("acos(%f)\texpected %.10f actual %.10f\tdelta: %f\n", val, expected, actual, expected - actual);

    return 0;
}