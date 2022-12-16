/*
  ==============================================================================

    DynamicEQ.h
    Created: 14 Dec 2022 5:47:47pm
    Author:  nikid

  ==============================================================================
*/

#pragma once
//#include <FilterBank.h>
#include <JuceHeader.h>


#define DEFAULT_COMP 0.0f
#define DEFAULT_EXP 0.0f
#define DEFAULT_ATQ 0.0f
#define DEFAULT_SL 0.0f
#define DEFAULT_MIX 1.0f
#define DEFAULT_IN 0.0f
#define DEFAULT_OUT 0.0f
#define DEFAULT_SC 0.0f

class DynamicEQ {
public:
    DynamicEQ() {}
    ~DynamicEQ() {}

    void prepareToPlay(float* frequencies, int nfilts) 
    {
        //fbank = new FilterBank(frequencies, nfilts);
    }

    void releaseResources()
    {

    }

    void processBlock(AudioBuffer<float>& mainBuffer, AudioBuffer<float>& scBuffer)
    {

    }

    void setComp(float newValue) {
        compAmount = newValue;
    }

    void setExp(float newValue) {
        expAmount = newValue;
    }

    void setAtq(float newValue) {
        atqWeight = newValue;
    }

    void setStereoLinked(float newValue) {
        stereoLinkAmt = newValue;
    }

    void setMix(float newValue) {
        mixAmount = newValue;
    }

    void setInGain(float newValue) {
        inGain = Decibels::decibelsToGain(newValue);
    }

    void setOutGain(float newValue) {
        outGain = Decibels::decibelsToGain(newValue);
    }

    void setScGain(float newValue) {
        scGain = Decibels::decibelsToGain(newValue);
    }

private:
    float compAmount = DEFAULT_COMP;
    float expAmount = DEFAULT_EXP;
    float atqWeight = DEFAULT_ATQ;
    float stereoLinkAmt = DEFAULT_SL;
    float mixAmount = DEFAULT_MIX;
    float inGain = Decibels::decibelsToGain(DEFAULT_IN);
    float outGain = Decibels::decibelsToGain(DEFAULT_OUT);
    float scGain = Decibels::decibelsToGain(DEFAULT_SC);

    int nfilts;
    //FilterBank fbank;
    float* fCenters ;
};
