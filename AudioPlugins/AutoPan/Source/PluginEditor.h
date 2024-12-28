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
class AutoPanAudioProcessorEditor  : public juce::AudioProcessorEditor,
                                     public juce::Button::Listener
{
public:
    AutoPanAudioProcessorEditor (AutoPanAudioProcessor&);
    ~AutoPanAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    // void sliderValueChanged(juce::Slider * slider) override;
    void buttonClicked(juce::Button * button) override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    AutoPanAudioProcessor& audioProcessor;
    
    juce::Slider rateSlider;
    juce::Slider depthSlider;
    juce::Slider angleSlider;
    juce::ToggleButton bypassButton;
    
public:
    std::vector<std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>> sliderAttachments;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AutoPanAudioProcessorEditor)
};
