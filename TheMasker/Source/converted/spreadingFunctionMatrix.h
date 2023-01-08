//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// spreadingFunctionMatrix.h
//
// Code generation for function 'spreadingFunctionMatrix'
//

#ifndef SPREADINGFUNCTIONMATRIX_H
#define SPREADINGFUNCTIONMATRIX_H

// Include files
#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

// Function Declarations
extern void
spreadingFunctionMatrix(float maxfreq, float nfilts, float alpha_exp,
                        coder::array<float, 2U> &spreadingfuncmatrix);

#endif
// End of code generation (spreadingFunctionMatrix.h)
