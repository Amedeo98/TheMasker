//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// spreadingFunctionMatrix.cpp
//
// Code generation for function 'spreadingFunctionMatrix'
//

// Include files
#include "spreadingFunctionMatrix.h"
#include "asinh.h"
#include "rt_nonfinite.h"
#include "spreadingFunctionMatrix_data.h"
#include "spreadingFunctionMatrix_initialize.h"
#include "coder_array.h"
#include "rt_nonfinite.h"
#include <math.h>

// Function Declarations
static float rt_powf_snf(float u0, float u1);

// Function Definitions
static float rt_powf_snf(float u0, float u1)
{
  float y;
  if (rtIsNaNF(u0) || rtIsNaNF(u1)) {
    y = rtNaNF;
  } else {
    float f;
    float f1;
    f = static_cast<float>(fabs(static_cast<double>(u0)));
    f1 = static_cast<float>(fabs(static_cast<double>(u1)));
    if (rtIsInfF(u1)) {
      if (f == 1.0F) {
        y = 1.0F;
      } else if (f > 1.0F) {
        if (u1 > 0.0F) {
          y = rtInfF;
        } else {
          y = 0.0F;
        }
      } else if (u1 > 0.0F) {
        y = 0.0F;
      } else {
        y = rtInfF;
      }
    } else if (f1 == 0.0F) {
      y = 1.0F;
    } else if (f1 == 1.0F) {
      if (u1 > 0.0F) {
        y = u0;
      } else {
        y = 1.0F / u0;
      }
    } else if (u1 == 2.0F) {
      y = u0 * u0;
    } else if ((u1 == 0.5F) && (u0 >= 0.0F)) {
      y = static_cast<float>(sqrt(static_cast<double>(u0)));
    } else if ((u0 < 0.0F) &&
               (u1 > static_cast<float>(floor(static_cast<double>(u1))))) {
      y = rtNaNF;
    } else {
      y = static_cast<float>(
          pow(static_cast<double>(u0), static_cast<double>(u1)));
    }
  }
  return y;
}

void spreadingFunctionMatrix(float maxfreq, float nfilts, float alpha_exp,
                             coder::array<float, 2U> &spreadingfuncmatrix)
{
  coder::array<float, 2U> fcnOutput;
  coder::array<float, 2U> spreadingfunctionBarkdB;
  float d1;
  float delta1;
  float delta2;
  float maxbark;
  float varargin_2_tmp;
  int i;
  int i1;
  int k;
  int loop_ub_tmp;
  if (!isInitialized_spreadingFunctionMatrix) {
    spreadingFunctionMatrix_initialize();
  }
  // Arguments: maxfreq: half the sampling frequency
  // nfilts: Number of subbands in the Bark domain, for instance 64
  //  Simultaneous masking for tones at Bark band 12
  //  Upper slope of spreading function
  //  Lower slope of spreading function
  // HZ2BARK Convert frequency to barks
  //
  // [ bark ] = HZ2BARK( f )
  //
  //     Reference: Wang, Shihua, Andrew Sekey, and Allen Gersho. "An objective
  //                measure for predicting subjective quality of speech coders."
  //                IEEE Journal on selected areas in communications 10.5
  //                (1992): 819-829.
  //
  // (C)2018 G.Presti (LIM) - GPL license at the end of file
  //  See also BARK2HZ, GETFREQCONVERTERS, RESCALEFREQ
  delta1 = maxfreq / 600.0F;
  coder::b_asinh(&delta1);
  maxbark = 6.0F * delta1;
  varargin_2_tmp = 2.0F * nfilts;
  loop_ub_tmp = static_cast<int>(varargin_2_tmp);
  spreadingfunctionBarkdB.set_size(1, loop_ub_tmp);
  for (i = 0; i < loop_ub_tmp; i++) {
    spreadingfunctionBarkdB[i] = 0.0F;
  }
  // upper slope, fbdB attenuation per Bark, over maxbark Bark (full frequency
  // range), with fadB dB simultaneous masking:
  d1 = -maxbark * 7.5F;
  if (!(nfilts >= 0.0F)) {
    fcnOutput.set_size(1, 0);
  } else {
    delta1 = static_cast<float>(floor(static_cast<double>(nfilts)));
    fcnOutput.set_size(1, static_cast<int>(delta1));
    if (static_cast<int>(delta1) >= 1) {
      loop_ub_tmp = static_cast<int>(delta1) - 1;
      fcnOutput[static_cast<int>(delta1) - 1] = -2.5F;
      if (fcnOutput.size(1) >= 2) {
        fcnOutput[0] = d1;
        if (fcnOutput.size(1) >= 3) {
          if ((d1 == 2.5F) && (static_cast<int>(delta1) > 2)) {
            delta2 = -2.5F / static_cast<float>(static_cast<int>(delta1) - 1);
            for (k = 2; k <= loop_ub_tmp; k++) {
              fcnOutput[k - 1] =
                  static_cast<float>(((k << 1) - static_cast<int>(delta1)) -
                                     1) *
                  delta2;
            }
            if ((static_cast<int>(delta1) & 1) == 1) {
              fcnOutput[static_cast<int>(delta1) >> 1] = 0.0F;
            }
          } else if ((!(d1 < 0.0F)) && (d1 > 1.70141173E+38F)) {
            delta1 = d1 / static_cast<float>(
                              static_cast<double>(fcnOutput.size(1)) - 1.0);
            delta2 = -2.5F / static_cast<float>(
                                 static_cast<double>(fcnOutput.size(1)) - 1.0);
            i = fcnOutput.size(1);
            for (k = 0; k <= i - 3; k++) {
              fcnOutput[k + 1] =
                  (d1 +
                   delta2 * static_cast<float>(static_cast<double>(k) + 1.0)) -
                  delta1 * static_cast<float>(static_cast<double>(k) + 1.0);
            }
          } else {
            delta1 = (-2.5F - d1) /
                     static_cast<float>(static_cast<double>(fcnOutput.size(1)) -
                                        1.0);
            i = fcnOutput.size(1);
            for (k = 0; k <= i - 3; k++) {
              fcnOutput[k + 1] =
                  d1 +
                  static_cast<float>(static_cast<double>(k) + 1.0) * delta1;
            }
          }
        }
      }
    }
  }
  loop_ub_tmp = fcnOutput.size(1);
  for (i = 0; i < loop_ub_tmp; i++) {
    spreadingfunctionBarkdB[i] = fcnOutput[i] - 26.5F;
  }
  // lower slope fbbdb attenuation per Bark, over maxbark Bark (full frequency
  // range):
  if (nfilts + 1.0F > varargin_2_tmp) {
    i = 1;
  } else {
    i = static_cast<int>(nfilts + 1.0F);
  }
  delta2 = -maxbark * 26.0F;
  if (!(nfilts >= 0.0F)) {
    fcnOutput.set_size(1, 0);
  } else {
    delta1 = static_cast<float>(floor(static_cast<double>(nfilts)));
    fcnOutput.set_size(1, static_cast<int>(static_cast<float>(
                              floor(static_cast<double>(nfilts)))));
    if (static_cast<int>(delta1) >= 1) {
      loop_ub_tmp = static_cast<int>(delta1) - 1;
      fcnOutput[static_cast<int>(delta1) - 1] = delta2;
      if (fcnOutput.size(1) >= 2) {
        fcnOutput[0] = 1.0F;
        if (fcnOutput.size(1) >= 3) {
          if ((1.0F == -delta2) && (static_cast<int>(delta1) > 2)) {
            delta2 /= static_cast<float>(static_cast<int>(delta1) - 1);
            for (k = 2; k <= loop_ub_tmp; k++) {
              fcnOutput[k - 1] =
                  static_cast<float>(((k << 1) - static_cast<int>(delta1)) -
                                     1) *
                  delta2;
            }
            if ((static_cast<int>(delta1) & 1) == 1) {
              fcnOutput[static_cast<int>(delta1) >> 1] = 0.0F;
            }
          } else if ((delta2 < 0.0F) &&
                     (static_cast<float>(fabs(static_cast<double>(delta2))) >
                      1.70141173E+38F)) {
            delta1 = 1.0F / static_cast<float>(
                                static_cast<double>(fcnOutput.size(1)) - 1.0);
            delta2 /= static_cast<float>(
                static_cast<double>(fcnOutput.size(1)) - 1.0);
            i1 = fcnOutput.size(1);
            for (k = 0; k <= i1 - 3; k++) {
              fcnOutput[k + 1] =
                  (delta2 * static_cast<float>(static_cast<double>(k) + 1.0) +
                   1.0F) -
                  delta1 * static_cast<float>(static_cast<double>(k) + 1.0);
            }
          } else {
            delta1 = (delta2 - 1.0F) /
                     static_cast<float>(static_cast<double>(fcnOutput.size(1)) -
                                        1.0);
            i1 = fcnOutput.size(1);
            for (k = 0; k <= i1 - 3; k++) {
              fcnOutput[k + 1] =
                  static_cast<float>(static_cast<double>(k) + 1.0) * delta1 +
                  1.0F;
            }
          }
        }
      }
    }
  }
  loop_ub_tmp = fcnOutput.size(1);
  for (i1 = 0; i1 < loop_ub_tmp; i1++) {
    spreadingfunctionBarkdB[(i + i1) - 1] = fcnOutput[i1] - 26.5F;
  }
  // Convert from dB to "voltage" and include a exponent
  spreadingfunctionBarkdB.set_size(1, spreadingfunctionBarkdB.size(1));
  loop_ub_tmp = spreadingfunctionBarkdB.size(1) - 1;
  for (i = 0; i <= loop_ub_tmp; i++) {
    delta2 = spreadingfunctionBarkdB[i] / 20.0F * alpha_exp;
    spreadingfunctionBarkdB[i] = rt_powf_snf(10.0F, delta2);
  }
  // Spreading functions for all bark scale bands in a matrix:
  i = static_cast<int>(nfilts);
  spreadingfuncmatrix.set_size(i, i);
  loop_ub_tmp = static_cast<int>(nfilts) * static_cast<int>(nfilts);
  for (i1 = 0; i1 < loop_ub_tmp; i1++) {
    spreadingfuncmatrix[i1] = 0.0F;
  }
  for (k = 0; k < i; k++) {
    delta1 = (nfilts - (static_cast<float>(k) + 1.0F)) + 1.0F;
    if (delta1 > varargin_2_tmp - (static_cast<float>(k) + 1.0F)) {
      i1 = 1;
    } else {
      i1 = static_cast<int>(delta1);
    }
    loop_ub_tmp = spreadingfuncmatrix.size(0);
    for (int i2 = 0; i2 < loop_ub_tmp; i2++) {
      spreadingfuncmatrix[i2 +
                          spreadingfuncmatrix.size(0) *
                              (static_cast<int>(static_cast<float>(k) + 1.0F) -
                               1)] = spreadingfunctionBarkdB[(i1 + i2) - 1];
    }
  }
}

// End of code generation (spreadingFunctionMatrix.cpp)
