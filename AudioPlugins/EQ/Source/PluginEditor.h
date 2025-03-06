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
class EQAudioProcessorEditor  : public juce::AudioProcessorEditor,
juce::Button::Listener,
juce::ComboBox::Listener

{
public:
    EQAudioProcessorEditor (EQAudioProcessor&);
    ~EQAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    
    void buttonClicked (juce::Button *button) override;
    void comboBoxChanged (juce::ComboBox *comboBox) override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    EQAudioProcessor& audioProcessor;
    
    juce::Slider lowPassSlider;
    juce::Slider highPassSlider;
    juce::Slider notchSlider;
    juce::Slider notch1Slider;
    juce::Slider lowPassQ;
    juce::Slider highPassQ;
    juce::Slider notchQ;
    juce::Slider notch1Q;
    
    juce::ComboBox lowPassShelf;
    juce::ComboBox highPassShelf;
    
    juce::ToggleButton LPFToggle;
    juce::ToggleButton NToggle;
    juce::ToggleButton N1Toggle;
    juce::ToggleButton HPFToggle;
    
public:
    std::vector<std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>> sliderAttachments;
    std::vector<std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment>> buttonAttachments;
    std::vector<std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment>> comboAttachments;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (EQAudioProcessorEditor)
};
