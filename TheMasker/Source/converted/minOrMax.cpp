//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// minOrMax.cpp
//
// Code generation for function 'minOrMax'
//

// Include files
#include "minOrMax.h"
#include "rt_nonfinite.h"
#include "coder_array.h"
#include "rt_nonfinite.h"

// Function Definitions
namespace coder {
namespace internal {
void minimum(const ::coder::array<float, 2U> &x, float *ex, int *idx)
{
  int last;
  last = x.size(1);
  if (x.size(1) <= 2) {
    if (x.size(1) == 1) {
      *ex = x[0];
      *idx = 1;
    } else if ((x[0] > x[x.size(1) - 1]) ||
               (rtIsNaNF(x[0]) && (!rtIsNaNF(x[x.size(1) - 1])))) {
      *ex = x[x.size(1) - 1];
      *idx = x.size(1);
    } else {
      *ex = x[0];
      *idx = 1;
    }
  } else {
    int k;
    if (!rtIsNaNF(x[0])) {
      *idx = 1;
    } else {
      boolean_T exitg1;
      *idx = 0;
      k = 2;
      exitg1 = false;
      while ((!exitg1) && (k <= last)) {
        if (!rtIsNaNF(x[k - 1])) {
          *idx = k;
          exitg1 = true;
        } else {
          k++;
        }
      }
    }
    if (*idx == 0) {
      *ex = x[0];
      *idx = 1;
    } else {
      int i;
      *ex = x[*idx - 1];
      i = *idx + 1;
      for (k = i; k <= last; k++) {
        float f;
        f = x[k - 1];
        if (*ex > f) {
          *ex = f;
          *idx = k;
        }
      }
    }
  }
}

} // namespace internal
} // namespace coder

// End of code generation (minOrMax.cpp)
