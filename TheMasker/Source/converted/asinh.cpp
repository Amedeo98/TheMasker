//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// asinh.cpp
//
// Code generation for function 'asinh'
//

// Include files
#include "asinh.h"
#include "rt_nonfinite.h"
#include "rt_nonfinite.h"
#include <math.h>

// Function Definitions
namespace coder {
void b_asinh(float *x)
{
  boolean_T xneg;
  xneg = (*x < 0.0F);
  if (xneg) {
    *x = -*x;
  }
  if (*x >= 2.68435456E+8F) {
    *x = static_cast<float>(log(static_cast<double>(*x))) + 0.693147182F;
  } else if (*x > 2.0F) {
    *x = static_cast<float>(log(static_cast<double>(
        2.0F * *x +
        1.0F / (static_cast<float>(sqrt(static_cast<double>(*x * *x + 1.0F))) +
                *x))));
  } else {
    float t;
    t = *x * *x;
    *x += t / (static_cast<float>(sqrt(static_cast<double>(t + 1.0F))) + 1.0F);
    t = static_cast<float>(fabs(static_cast<double>(*x)));
    if ((t > 8.388608E+6F) || (rtIsInfF(*x) || rtIsNaNF(*x))) {
      (*x)++;
      *x = static_cast<float>(log(static_cast<double>(*x)));
    } else if (!(t < 1.1920929E-7F)) {
      *x = static_cast<float>(log(static_cast<double>(*x + 1.0F))) *
           (*x / ((*x + 1.0F) - 1.0F));
    }
  }
  if (xneg) {
    *x = -*x;
  }
}

} // namespace coder

// End of code generation (asinh.cpp)
