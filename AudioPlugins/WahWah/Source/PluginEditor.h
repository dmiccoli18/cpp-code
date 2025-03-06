/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class WahWahAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    WahWahAudioProcessorEditor (WahWahAudioProcessor&);
    ~WahWahAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    //void sliderValueChanged(juce::Slider * slider) override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    WahWahAudioProcessor& audioProcessor;
    juce::Slider rateSlider;
    juce::Slider freqSlider; //DC offset
    juce::Slider widthSlider;
    juce::Slider wetDrySlider;
    
public:
    std::vector<std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>> sliderAttachments;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (WahWahAudioProcessorEditor)
};
