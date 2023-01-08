//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// main.cpp
//
// Code generation for function 'main'
//

/*************************************************************************/
/* This automatically generated example C++ main file shows how to call  */
/* entry-point functions that MATLAB Coder generated. You must customize */
/* this file for your application. Do not modify this file directly.     */
/* Instead, make a copy of this file, modify it, and integrate it into   */
/* your development environment.                                         */
/*                                                                       */
/* This file initializes entry-point function arguments to a default     */
/* size and value before calling the entry-point functions. It does      */
/* not store or use any values returned from the entry-point functions.  */
/* If necessary, it does pre-allocate memory for returned values.        */
/* You can use this file as a starting point for a main function that    */
/* you can deploy in your application.                                   */
/*                                                                       */
/* After you copy the file, and before you deploy it, you must make the  */
/* following changes:                                                    */
/* * For variable-size function arguments, change the example sizes to   */
/* the sizes that your application requires.                             */
/* * Change the example values of function arguments to the values that  */
/* your application requires.                                            */
/* * If the entry-point functions return values, store these values or   */
/* otherwise use them as required by your application.                   */
/*                                                                       */
/*************************************************************************/

// Include files
#include "main.h"
#include "getfbank.h"
#include "rt_nonfinite.h"
#include "spreadingFunctionMatrix.h"
#include "spreadingFunctionMatrix_terminate.h"
#include "coder_array.h"
#include "FilterBank.h"


// Function Declarations
static coder::array<char, 2U> argInit_1xUnbounded_char_T();

static coder::array<float, 2U> argInit_1xUnbounded_real32_T();

static char argInit_char_T();

static float argInit_real32_T();

static void main_getfbank();

static void main_spreadingFunctionMatrix();

// Function Definitions
static coder::array<char, 2U> argInit_1xUnbounded_char_T()
{
  coder::array<char, 2U> result;
  // Set the size of the array.
  // Change this size to the value that the application requires.
  result.set_size(1, 2);
  // Loop over the array to initialize each element.
  for (int idx0 = 0; idx0 < 1; idx0++) {
    for (int idx1 = 0; idx1 < result.size(1); idx1++) {
      // Set the value of the array element.
      // Change this value to the value that the application requires.
      result[idx1] = argInit_char_T();
    }
  }
  return result;
}

static coder::array<float, 2U> argInit_1xUnbounded_real32_T()
{
  coder::array<float, 2U> result;
  // Set the size of the array.
  // Change this size to the value that the application requires.
  result.set_size(1, 2);
  // Loop over the array to initialize each element.
  for (int idx0 = 0; idx0 < 1; idx0++) {
    for (int idx1 = 0; idx1 < result.size(1); idx1++) {
      // Set the value of the array element.
      // Change this value to the value that the application requires.
      result[idx1] = argInit_real32_T();
    }
  }
  return result;
}

static char argInit_char_T()
{
  return '?';
}

static float argInit_real32_T()
{
  return 0.0F;
}

static void main_getfbank()
{
  coder::array<float, 2U> F;
  coder::array<float, 2U> bcen;
  coder::array<float, 2U> fbank;
  coder::array<char, 2U> scale_tmp;
  float nb_tmp;
  // Initialize function 'getfbank' input arguments.
  // Initialize function input argument 'F'.
  F = argInit_1xUnbounded_real32_T();
  // Initialize function input argument 'scale'.
  scale_tmp = argInit_1xUnbounded_char_T();
  nb_tmp = argInit_real32_T();
  // Initialize function input argument 'bwt'.
  // Initialize function input argument 'wType'.
  // Call the entry-point 'getfbank'.
  getfbank(F, scale_tmp, nb_tmp, scale_tmp, nb_tmp, fbank, bcen);
}

static void main_spreadingFunctionMatrix()
{
  coder::array<float, 2U> spreadingfuncmatrix;
  float maxfreq_tmp;
  // Initialize function 'spreadingFunctionMatrix' input arguments.
  maxfreq_tmp = argInit_real32_T();
  // Call the entry-point 'spreadingFunctionMatrix'.
  spreadingFunctionMatrix(maxfreq_tmp, maxfreq_tmp, maxfreq_tmp,
                          spreadingfuncmatrix);
}

int main(int, char **)
{
  // The initialize function is being called automatically from your entry-point
  // function. So, a call to initialize is not included here. Invoke the
  // entry-point functions.
  // You can call entry-point functions multiple times.
    vector<vector<float>> spreadingMtx;
    FilterBank fbank;
    
    main_getfbank();
  main_spreadingFunctionMatrix();
  // Terminate the application.
  // You do not need to do this more than one time.
  spreadingFunctionMatrix_terminate();
  return 0;
}

// End of code generation (main.cpp)
