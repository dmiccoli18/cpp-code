/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "EQ4HPF.h"
#include "EQ4LPF.h"
#include "Notch.h"

//==============================================================================
/**
*/
class EQAudioProcessor  : public juce::AudioProcessor
{
public:
    //==============================================================================
    EQAudioProcessor();
    ~EQAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

    EQ4LPF::filterType passShelf = EQ4LPF::filterType::PASS;
    EQ4HPF::filterType PassShelf = EQ4HPF::filterType::PASS;
    
    double LFreq = 20000;
    double HFreq = 20;
    double NFreq = 1000;
    double N1Freq = 2000;
    double Fs = 48000;
    double LQ = .707;
    double HQ = .707;
    double NQ = .707;
    double N1Q = .707;
    
    bool LPFOn = true;
    bool NFOn = true;
    bool NF1On = true;
    bool HPFOn = true;
private:
    
    EQ4LPF lowPass;
    EQ4HPF highPass;
    Notch notch;
    Notch notch1;
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (EQAudioProcessor)
};
