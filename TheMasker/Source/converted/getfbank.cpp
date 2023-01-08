//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// getfbank.cpp
//
// Code generation for function 'getfbank'
//

// Include files
#include "getfbank.h"
#include "asinh.h"
#include "minOrMax.h"
#include "rt_nonfinite.h"
#include "spreadingFunctionMatrix_data.h"
#include "spreadingFunctionMatrix_initialize.h"
#include "coder_array.h"
#include "rt_nonfinite.h"
#include <math.h>

// Function Definitions
void getfbank(const coder::array<float, 2U> &F, const coder::array<char, 2U> &,
              float nb, const coder::array<char, 2U> &, float trans,
              coder::array<float, 2U> &fbank, coder::array<float, 2U> &bcen)
{
  coder::array<float, 2U> c;
  coder::array<float, 2U> fcnOutput;
  coder::array<float, 2U> infr;
  coder::array<float, 2U> supr;
  float xw[3];
  float bhop;
  float ex;
  float low;
  float m;
  int b_iindx;
  int b_loop_ub;
  int i;
  int iindx;
  int k;
  int loop_ub;
  int nx;
  signed char yw[3];
  if (!isInitialized_spreadingFunctionMatrix) {
    spreadingFunctionMatrix_initialize();
  }
  // GETFILTERBANK returns a filterbank with given properties
  //
  // [ fbank, bcen ] = GETFILTERBANK( F )
  // [ fbank, bcen ] = GETFILTERBANK( F, scale )
  // [ fbank, bcen ] = GETFILTERBANK( F, scale, nb )
  // [ fbank, bcen ] = GETFILTERBANK( F, scale, nb, bw)
  // [ fbank, bcen ] = GETFILTERBANK( F, scale, nb, bw, wType )
  // [ fbank, bcen ] = GETFILTERBANK( F, cf, __ )      :::::: to be implemented
  // [ fbank, bcen ] = GETFILTERBANK( F, [], xf, __ )  :::::: to be implemented
  //
  //    get a filterbank fbank such fbank*getFD(x) is a filtered version of x.
  //
  //    F:     Frequency of FFT bins (must be sorted in increasing order)
  //    scale: 'mel', 'bark', 'erbs', 'semitone', 'hz', 'log' (default: 'mel')
  //    nb:    number of bands (default [])
  //    bw:    badwidth of each filter (expressed in 'scale', default: [])
  //    xf:    Crossover frequencies array (expressed in 'scale')
  //    cf:    Center frequencies array (expressed in 'scale')
  //    wType: Filter window function ('tri','cos','pow'; default: 'tri')
  //    trans: Transition phase as ratio of bw (default: 1)
  //
  //    fbank: fbank such that fbank*GETFD(x) is the filtered version of x
  //    bcen:  band centers expressed in 'scale'
  //
  //    if 'nb' and 'bw' are set to [], they are automatically set to match as
  //    closely as possible the ERB scale subdivision, based on given 'scale'
  //    representation (usually used with 'bark' or 'mel')
  //
  //    if just one among 'nb' or 'bw' is set to [], it is automatically set to
  //    a value that results in a 50% overlapping bands given the provided
  //    parameter.
  //
  //    if both 'nb' and 'bw' are scalar values, overlappings other than 50%
  //    can be achieved.
  //
  //    Please note that the first and the last bands are a lowpass and a
  //    highpass respectively.
  //
  // (C)2022 G.Presti (LIM) - GPL license at the end of file
  //  See also GETFD, GETTD, RESCALEFREQ, GETFREQCONVERTERS
  //    scale: 'mel', 'bark', 'erbs', 'semitone', 'hz', 'log'
  //      [f2x, x2f, first_el] = getFreqConverters(scale, F);
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
  bhop = F[0] / 600.0F;
  coder::b_asinh(&bhop);
  low = 6.0F * bhop;
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
  //      if isempty(nb)
  //          if isempty(bw)
  //              nb = getErbEqNb(F, f2x);
  //          else
  //              nb = (high-low)/bw - 1;
  //          end
  //
  //          nb = max(1, round(nb));
  //      end
  bhop = F[static_cast<int>(static_cast<float>(F.size(1))) - 1] / 600.0F;
  coder::b_asinh(&bhop);
  bhop = (6.0F * bhop - low) / (nb + 1.0F);
  // olap = bw >= bhop;
  if (rtIsNaNF(nb)) {
    bcen.set_size(1, 1);
    bcen[0] = rtNaNF;
  } else if (nb < 1.0F) {
    bcen.set_size(bcen.size(0), 0);
  } else if (rtIsInfF(nb) && (1.0F == nb)) {
    bcen.set_size(1, 1);
    bcen[0] = rtNaNF;
  } else if (nb >= 1.07374182E+9F) {
    nx = static_cast<int>(floor(nb - 1.0));
    bcen.set_size(1, nx + 1);
    for (i = 0; i <= nx; i++) {
      bcen[i] = static_cast<float>(static_cast<double>(i) + 1.0);
    }
  } else {
    nx = static_cast<int>(static_cast<float>(floor(static_cast<double>(nb))));
    bcen.set_size(1, nx);
    for (k = 0; k < nx; k++) {
      bcen[k] = static_cast<float>(k + 1);
    }
  }
  bcen.set_size(1, bcen.size(1));
  nx = bcen.size(1) - 1;
  for (i = 0; i <= nx; i++) {
    bcen[i] = low + bcen[i] * bhop;
  }
  // BARK2HZ Convert barks to Hz
  //
  // [ f ] = BARK2HZ( brk )
  //
  //     Reference: Wang, Shihua, Andrew Sekey, and Allen Gersho. "An objective
  //                measure for predicting subjective quality of speech coders."
  //                IEEE Journal on selected areas in communications 10.5
  //                (1992): 819-829.
  //
  // (C)2014 G.Presti (LIM) - GPL license at the end of file
  //  See also HZ2BARK, GETFREQCONVERTERS, RESCALEFREQ
  infr.set_size(1, bcen.size(1));
  nx = bcen.size(1);
  for (i = 0; i < nx; i++) {
    infr[i] = (bcen[i] - bhop) / 6.0F;
  }
  nx = infr.size(1);
  for (k = 0; k < nx; k++) {
    infr[k] = static_cast<float>(sinh(static_cast<double>(infr[k])));
  }
  infr.set_size(1, infr.size(1));
  nx = infr.size(1) - 1;
  for (i = 0; i <= nx; i++) {
    infr[i] = 600.0F * infr[i];
  }
  // BARK2HZ Convert barks to Hz
  //
  // [ f ] = BARK2HZ( brk )
  //
  //     Reference: Wang, Shihua, Andrew Sekey, and Allen Gersho. "An objective
  //                measure for predicting subjective quality of speech coders."
  //                IEEE Journal on selected areas in communications 10.5
  //                (1992): 819-829.
  //
  // (C)2014 G.Presti (LIM) - GPL license at the end of file
  //  See also HZ2BARK, GETFREQCONVERTERS, RESCALEFREQ
  supr.set_size(1, bcen.size(1));
  nx = bcen.size(1);
  for (i = 0; i < nx; i++) {
    supr[i] = (bcen[i] + bhop) / 6.0F;
  }
  nx = supr.size(1);
  for (k = 0; k < nx; k++) {
    supr[k] = static_cast<float>(sinh(static_cast<double>(supr[k])));
  }
  supr.set_size(1, supr.size(1));
  nx = supr.size(1) - 1;
  for (i = 0; i <= nx; i++) {
    supr[i] = 600.0F * supr[i];
  }
  // BARK2HZ Convert barks to Hz
  //
  // [ f ] = BARK2HZ( brk )
  //
  //     Reference: Wang, Shihua, Andrew Sekey, and Allen Gersho. "An objective
  //                measure for predicting subjective quality of speech coders."
  //                IEEE Journal on selected areas in communications 10.5
  //                (1992): 819-829.
  //
  // (C)2014 G.Presti (LIM) - GPL license at the end of file
  //  See also HZ2BARK, GETFREQCONVERTERS, RESCALEFREQ
  bcen.set_size(1, bcen.size(1));
  nx = bcen.size(1) - 1;
  for (i = 0; i <= nx; i++) {
    bcen[i] = bcen[i] / 6.0F;
  }
  nx = bcen.size(1);
  for (k = 0; k < nx; k++) {
    bcen[k] = static_cast<float>(sinh(static_cast<double>(bcen[k])));
  }
  bcen.set_size(1, bcen.size(1));
  nx = bcen.size(1) - 1;
  for (i = 0; i <= nx; i++) {
    bcen[i] = 600.0F * bcen[i];
  }
  infr[0] = F[0];
  supr[static_cast<int>(static_cast<float>(supr.size(1))) - 1] =
      F[static_cast<int>(static_cast<float>(F.size(1))) - 1];
  fbank.set_size(static_cast<int>(nb),
                 static_cast<int>(static_cast<float>(F.size(1))));
  nx = static_cast<int>(nb) * static_cast<int>(static_cast<float>(F.size(1)));
  for (i = 0; i < nx; i++) {
    fbank[i] = 0.0F;
  }
  //      switch wType
  //          case 'cos'
  //              wfun = @(x) (0.5*(1-cos(pi*x)));
  //          case 'pow'
  //              wfun = @(x) (sqrt(x));
  //          otherwise
  //      end
  if ((2.22044605E-16F >= trans) || rtIsNaNF(trans)) {
    bhop = 2.22044605E-16F;
  } else {
    bhop = trans;
  }
  m = 1.0F / bhop;
  i = static_cast<int>(nb);
  if (0 <= static_cast<int>(nb) - 1) {
    yw[1] = 1;
    loop_ub = F.size(1);
    b_loop_ub = F.size(1);
  }
  for (int b = 0; b < i; b++) {
    int i1;
    int i2;
    int outsize_idx_1_tmp;
    boolean_T b1;
    boolean_T b2;
    boolean_T b_b;
    bhop = infr[static_cast<int>(static_cast<float>(b) + 1.0F) - 1];
    xw[0] = bhop;
    xw[1] = bcen[static_cast<int>(static_cast<float>(b) + 1.0F) - 1];
    low = supr[static_cast<int>(static_cast<float>(b) + 1.0F) - 1];
    xw[2] = low;
    b_b = (static_cast<float>(b) + 1.0F == 1.0F);
    b1 = (static_cast<float>(b) + 1.0F == nb);
    yw[0] = static_cast<signed char>(static_cast<float>(b) + 1.0F == 1.0F);
    yw[2] = static_cast<signed char>(static_cast<float>(b) + 1.0F == nb);
    //  -------------------------------------
    //  function nb = getErbEqNb(F, f2x)
    //  % Thanks Marco for the clever idea
    //      if F(1) <= 0
    //          lb = F(2);
    //      else
    //          lb = F(1);
    //      end
    //      ub = F(end);
    //      f = 10.^(linspace(log10(lb),log10(ub),1024));
    //      XERB = f2x([ f-hz2ERB(f)/2 ; f+hz2ERB(f)/2 ]);
    //      XERBbwdth = XERB(2,:)-XERB(1,:);
    //      bw = mean(XERBbwdth);
    //  %     nb = 2*(f2x(ub)-f2x(lb))/bw - 1;
    //      nb = (f2x(ub)-f2x(lb))/bw - 1;
    //  end
    c.set_size(1, F.size(1));
    for (i1 = 0; i1 < loop_ub; i1++) {
      c[i1] = F[i1] - bhop;
    }
    nx = c.size(1);
    fcnOutput.set_size(1, c.size(1));
    for (k = 0; k < nx; k++) {
      fcnOutput[k] = static_cast<float>(fabs(static_cast<double>(c[k])));
    }
    coder::internal::minimum(fcnOutput, &ex, &iindx);
    //  -------------------------------------
    //  function nb = getErbEqNb(F, f2x)
    //  % Thanks Marco for the clever idea
    //      if F(1) <= 0
    //          lb = F(2);
    //      else
    //          lb = F(1);
    //      end
    //      ub = F(end);
    //      f = 10.^(linspace(log10(lb),log10(ub),1024));
    //      XERB = f2x([ f-hz2ERB(f)/2 ; f+hz2ERB(f)/2 ]);
    //      XERBbwdth = XERB(2,:)-XERB(1,:);
    //      bw = mean(XERBbwdth);
    //  %     nb = 2*(f2x(ub)-f2x(lb))/bw - 1;
    //      nb = (f2x(ub)-f2x(lb))/bw - 1;
    //  end
    c.set_size(1, F.size(1));
    for (i1 = 0; i1 < b_loop_ub; i1++) {
      c[i1] = F[i1] - low;
    }
    nx = c.size(1);
    fcnOutput.set_size(1, c.size(1));
    for (k = 0; k < nx; k++) {
      fcnOutput[k] = static_cast<float>(fabs(static_cast<double>(c[k])));
    }
    coder::internal::minimum(fcnOutput, &ex, &b_iindx);
    if (static_cast<float>(iindx) > b_iindx) {
      i1 = 0;
      k = -1;
      i2 = 1;
    } else {
      i1 = static_cast<int>(static_cast<float>(iindx)) - 1;
      k = static_cast<int>(static_cast<float>(b_iindx)) - 1;
      i2 = static_cast<int>(static_cast<float>(iindx));
    }
    outsize_idx_1_tmp = (k - i1) + 1;
    c.set_size(1, outsize_idx_1_tmp);
    for (k = 0; k < outsize_idx_1_tmp; k++) {
      c[k] = 0.0F;
    }
    b2 = (outsize_idx_1_tmp == 0);
    if (!b2) {
      k = 0;
      int exitg1;
      do {
        exitg1 = 0;
        if (k < 3) {
          if (rtIsNaNF(xw[k])) {
            exitg1 = 1;
          } else {
            k++;
          }
        } else {
          if (xw[1] < bhop) {
            xw[0] = low;
            xw[2] = bhop;
            yw[0] = static_cast<signed char>(b1);
            yw[2] = static_cast<signed char>(b_b);
          }
          for (k = 0; k < outsize_idx_1_tmp; k++) {
            bhop = F[i1 + k];
            if (rtIsNaNF(bhop)) {
              c[k] = rtNaNF;
            } else if ((!(bhop > xw[2])) && (!(bhop < xw[0]))) {
              nx = 0;
              if (bhop >= xw[1]) {
                nx = 1;
              }
              bhop = (bhop - xw[nx]) / (xw[nx + 1] - xw[nx]);
              if (bhop == 0.0F) {
                c[k] = yw[nx];
              } else if (bhop == 1.0F) {
                c[k] = yw[nx + 1];
              } else if (yw[nx] == yw[nx + 1]) {
                c[k] = yw[nx];
              } else {
                c[k] = (1.0F - bhop) * static_cast<float>(yw[nx]) +
                       bhop * static_cast<float>(yw[nx + 1]);
              }
            }
          }
          exitg1 = 1;
        }
      } while (exitg1 == 0);
    }
    nx = c.size(1);
    for (i1 = 0; i1 < nx; i1++) {
      fbank[(static_cast<int>(static_cast<float>(b) + 1.0F) +
             fbank.size(0) * ((i2 + i1) - 1)) -
            1] = c[i1];
    }
    if (trans != 1.0F) {
      if (static_cast<float>(iindx) > b_iindx) {
        i1 = 0;
        k = 0;
        i2 = 1;
      } else {
        i1 = static_cast<int>(static_cast<float>(iindx)) - 1;
        k = static_cast<int>(static_cast<float>(b_iindx));
        i2 = static_cast<int>(static_cast<float>(iindx));
      }
      nx = k - i1;
      c.set_size(1, nx);
      for (k = 0; k < nx; k++) {
        bhop = (fbank[(static_cast<int>(static_cast<float>(b) + 1.0F) +
                       fbank.size(0) * (i1 + k)) -
                      1] -
                0.5F) *
                   m +
               0.5F;
        if ((1.0F <= bhop) || rtIsNaNF(bhop)) {
          c[k] = 1.0F;
        } else {
          c[k] = bhop;
        }
      }
      nx = c.size(1);
      for (i1 = 0; i1 < nx; i1++) {
        bhop = c[i1];
        if ((0.0F >= bhop) || rtIsNaNF(bhop)) {
          fbank[(static_cast<int>(static_cast<float>(b) + 1.0F) +
                 fbank.size(0) * ((i2 + i1) - 1)) -
                1] = 0.0F;
        } else {
          fbank[(static_cast<int>(static_cast<float>(b) + 1.0F) +
                 fbank.size(0) * ((i2 + i1) - 1)) -
                1] = bhop;
        }
      }
    }
    if (static_cast<float>(iindx) > b_iindx) {
      i1 = 0;
      k = 0;
      i2 = 1;
    } else {
      i1 = static_cast<int>(static_cast<float>(iindx)) - 1;
      k = static_cast<int>(static_cast<float>(b_iindx));
      i2 = static_cast<int>(static_cast<float>(iindx));
    }
    nx = k - i1;
    c.set_size(1, nx);
    for (k = 0; k < nx; k++) {
      c[k] = fbank[(static_cast<int>(static_cast<float>(b) + 1.0F) +
                    fbank.size(0) * (i1 + k)) -
                   1];
    }
    nx = c.size(1);
    for (i1 = 0; i1 < nx; i1++) {
      fbank[(static_cast<int>(static_cast<float>(b) + 1.0F) +
             fbank.size(0) * ((i2 + i1) - 1)) -
            1] = c[i1];
    }
  }
}

// End of code generation (getfbank.cpp)
