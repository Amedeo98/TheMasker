/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


TheMaskerAudioProcessor::TheMaskerAudioProcessor()
     : AudioProcessor (BusesProperties()
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                       .withInput("SideChain", juce::AudioChannelSet::stereo(), true)
     ),
    parameters(*this, nullptr, "TheMaskerCompressor", {
    std::make_unique<AudioParameterFloat>(NAME_COMP, "Comp", -1.0f, 1.0f, DEFAULT_COMP),
    std::make_unique<AudioParameterFloat>(NAME_EXP, "Exp", -1.0f, 1.0f, DEFAULT_EXP),
    std::make_unique<AudioParameterFloat>(NAME_ATQ, "CleanUp", 0.0f, 1.0f, DEFAULT_ATQ),
    std::make_unique<AudioParameterFloat>(NAME_SL, "StereoLinked", 0.0f, 1.0f, DEFAULT_SL),
    std::make_unique<AudioParameterFloat>(NAME_MIX, "Mix", 0.0f, 1.0f, DEFAULT_MIX),
    std::make_unique<AudioParameterFloat>(NAME_IN, "Input (dB)", -40.0f, 20.0f, DEFAULT_IN),
    std::make_unique<AudioParameterFloat>(NAME_OUT, "Output (dB)", -40.0f, 20.0f, DEFAULT_OUT),
    std::make_unique<AudioParameterFloat>(NAME_SC, "Sidechain (dB)", -40.0f, 20.0f, DEFAULT_SC)
        })

{
    parameters.addParameterListener(NAME_COMP, this);
    parameters.addParameterListener(NAME_EXP, this);
    parameters.addParameterListener(NAME_ATQ, this);
    parameters.addParameterListener(NAME_SL, this);
    parameters.addParameterListener(NAME_MIX, this);
    parameters.addParameterListener(NAME_IN, this);
    parameters.addParameterListener(NAME_OUT, this);
    parameters.addParameterListener(NAME_SC, this);
}

TheMaskerAudioProcessor::~TheMaskerAudioProcessor()
{
}

void TheMaskerAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    frequencies = getFrequencies(npoints, minFreq, maxFreq);
    dynEQ.prepareToPlay(frequencies, nfilts);
    /*
    auxBuffer.setSize(1, samplesPerBlock);
    */
}

void TheMaskerAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
    //auxBuffer.setSize(0, 0);

}

#ifndef JucePlugin_PreferredChannelConfigurations
bool TheMaskerAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
 
  
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    /*
     if (layouts.inputBuses[1] != juce::AudioChannelSet::mono()
     && layouts.inputBuses[1] != juce::AudioChannelSet::stereo()
     && layouts.inputBuses[1] != juce::AudioChannelSet::disabled())
        return false;
    */

    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   

    return true;
  
}
#endif

void TheMaskerAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    /*
    auto numSamples = buffer.getNumSamples();

    auto mainBuffer = getBusBuffer(buffer, true, 0);
    auto scBuffer = getBusBuffer(buffer, true, 1);

    auxBuffer.clear();

    */

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());


    /*
     {
        const AudioBuffer<float>& scSource = scBuffer.getNumChannels() ? scBuffer : mainBuffer;
        const int numScChannels = scSource.getNumChannels();

        for (int ch = 0; ch < numScChannels; ++ch)
            auxBuffer.addFrom(0, 0, scSource, ch, 0, numSamples, 1 / numScChannels);
    }
    */

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    // Make sure to reset the state if your inner loop is processing
    // the samples and the outer loop is handling the channels.
    // Alternatively, you can process the samples with the channels
    // interleaved by keeping the same state.

    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer (channel);

        // ..do something to the data...
    }

    //compressor.processBlock(mainBuffer, auxBuffer);
}



juce::AudioProcessorEditor* TheMaskerAudioProcessor::createEditor()
{
    return new TheMaskerAudioProcessorEditor (*this);
}

void TheMaskerAudioProcessor::parameterChanged(const String& paramID, float newValue)
{
    if (paramID == NAME_COMP)
        dynEQ.setComp(newValue);

    if (paramID == NAME_EXP)
        dynEQ.setExp(newValue);

    if (paramID == NAME_ATQ)
        dynEQ.setAtq(newValue);

    if (paramID == NAME_SL)
        dynEQ.setStereoLinked(newValue);

    if (paramID == NAME_MIX)
        dynEQ.setMix(newValue);

    if (paramID == NAME_IN)
        dynEQ.setInGain(newValue);

    if (paramID == NAME_OUT)
        dynEQ.setOutGain(newValue);

    if (paramID == NAME_SC)
        dynEQ.setScGain(newValue);
}


//==============================================================================
void TheMaskerAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    auto state = parameters.copyState();
    std::unique_ptr<XmlElement> xml(state.createXml());
    copyXmlToBinary(*xml, destData);
    
}

void TheMaskerAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{

    std::unique_ptr<XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes));
    if (xmlState.get() != nullptr)
        if (xmlState->hasTagName(parameters.state.getType()))
            parameters.replaceState(ValueTree::fromXml(*xmlState));
    
}

float* getFrequencies(int npoints, float minFreq, float maxFreq) {
    float* freqs = new float[npoints];
    float* barks = new float[npoints];
    float maxbark = hz2bark(maxFreq);
    float minbark = hz2bark(minFreq);
    float step_bark = (maxbark - minbark) / (npoints - 1);
    for (int i = 0; i < npoints; ++i){
        barks[i] = minbark + step_bark * i;
        freqs[i] = bark2hz(barks[i]);
    }
    return freqs;
}




//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new TheMaskerAudioProcessor();
}
