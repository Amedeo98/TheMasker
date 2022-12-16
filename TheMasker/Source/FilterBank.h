/*
  ==============================================================================

    FilterBank.h
    Created: 15 Dec 2022 3:06:00pm
    Author:  nikid

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class FilterBank {
public:
    FilterBank(float* frequencies, int nfilters) {
        nfilts = nfilters;
        freqs = frequencies;
        centerF[nfilters];
        values[nfilters, sizeof(frequencies)];
    }

    ~FilterBank() {}

    float* centerF;
    float* values;

private:
    float* freqs;
    int nfilts;
    
};