#ifndef FLOAT_MATH_H_INCLUDED_
#define FLOAT_MATH_H_INCLUDED_

#ifdef __cplusplus // CPP guard
extern "C" {
#endif

#if defined(FLOAT_MATH_EXPORTS)
#define FLOAT_MATH_API __declspec(dllexport)
#elif defined(FLOAT_MATH_IMPORTS)
#define FLOAT_MATH_API __declspec(dllimport)
#else
#define FLOAT_MATH_API
#endif


FLOAT_MATH_API float fm_sqrt(float x);
FLOAT_MATH_API float fm_log(float x);
FLOAT_MATH_API float fm_log10(float x);
FLOAT_MATH_API float fm_cos(float x);
FLOAT_MATH_API float fm_sin(float x);
FLOAT_MATH_API float fm_exp(float x);
FLOAT_MATH_API float fm_pow(float x, float y);
FLOAT_MATH_API float fm_acos(float x);
FLOAT_MATH_API float fm_asin(float x);
FLOAT_MATH_API float fm_tan(float x);
FLOAT_MATH_API float fm_cotan(float x);

#ifdef __cplusplus // CPP guard
}
#endif

#endif // FLOAT_MATH_H_INCLUDED_