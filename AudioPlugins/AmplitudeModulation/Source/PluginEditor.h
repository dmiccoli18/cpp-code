/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
/**
*/
class AmplitudeModulationAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    AmplitudeModulationAudioProcessorEditor (AmplitudeModulationAudioProcessor&);
    ~AmplitudeModulationAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    //void sliderValueChanged(juce::Slider * slider) override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    AmplitudeModulationAudioProcessor& audioProcessor;
    
    juce::Slider rateSlider;
    juce::Slider depthSlider;
    
public:
    std::vector<std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>> sliderAttachments;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AmplitudeModulationAudioProcessorEditor)
};
