//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// getfbank.h
//
// Code generation for function 'getfbank'
//

#ifndef GETFBANK_H
#define GETFBANK_H

// Include files
#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

// Function Declarations
extern void getfbank(const coder::array<float, 2U> &F,
                     const coder::array<char, 2U> &scale, float nb,
                     const coder::array<char, 2U> &wType, float trans,
                     coder::array<float, 2U> &fbank,
                     coder::array<float, 2U> &bcen);

#endif
// End of code generation (getfbank.h)
