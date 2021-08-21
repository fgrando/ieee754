#include <iostream>
#include <octave/oct.h>

#include "../../fmath.h"

DEFUN_DLD (oct_tan, args, nargout, "oct_tan Help String")
{
  octave_idx_type nargin = args.length();
  if (nargin != 1) {
  	error ("Need exactly 1 argin, got %ld", (long) nargin);
  }
  // our input
  NDArray inList = args(0).array_value();

  // create an output with the same number of input elements
  NDArray output = args(0).array_value();

  // iterate over all input elements calculating the respective result
  octave_idx_type inLen = inList.numel();
  //octave_stdout << "input has " << inLen << "elements\n";
  for (octave_idx_type i = 0; i < inLen; i++) {
    float result = fm_tan(inList.elem(i));
    //octave_stdout << "add " << result << "to list\n";
    output.elem(i) = result;

  }

  return ovl(output);
}
