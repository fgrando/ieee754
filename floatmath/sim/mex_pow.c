#include <mex.h>

#define	INPUT_VAR	prhs[0]
#define	OUTPUT_VAR	plhs[0]

#include "fmath.h"

/* the "main" function
nlhs	Number of output (left-side) arguments, or the size of the plhs array.
plhs	Array of output arguments.
nrhs	Number of input (right-side) arguments, or the size of the prhs array.
prhs	Array of input arguments.
*/
void mexFunction( int nlhs, mxArray *plhs[],
		  int nrhs, const mxArray*prhs[] )
{
    if (nrhs != 2) {
	    mexErrMsgIdAndTxt( "MATLAB:fm_pow:invalidNumInputs",
                "Two input arguments required.");
    } else if (nlhs > 1) {
	    mexErrMsgIdAndTxt( "MATLAB:fm_pow:maxlhs",
                "Too many output arguments.");
    }
    
    size_t m = mxGetM(INPUT_VAR);
    size_t n = mxGetN(INPUT_VAR);

    mxArray *result = mxCreateDoubleMatrix( (mwSize)m, (mwSize)n, mxREAL);

    /* Remember, MATLAB stores matrices in their transposed form, i.e., columnwise, like FORTRAN. */
    for (int j = 0; j < n; j++) {
        mxGetPr(result)[j] = mxGetPr(prhs[0])[j] * mxGetPr(prhs[1])[j];
    }
    OUTPUT_VAR = result;
}
