/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
DistortionClipAudioProcessorEditor::DistortionClipAudioProcessorEditor (DistortionClipAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 300);
    
    // distortion
    //driveSlider.addListener(this);
    driveSlider.setSliderStyle(juce::Slider::LinearVertical);
    driveSlider.setBounds(110,90,120,120);
    //driveSlider.setRange(0.f,10.f,0.1f);
    driveSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 60, 30);
    //driveSlider.setValue(audioProcessor.drive);
    addAndMakeVisible(driveSlider);
    
    sliderAttachments.emplace_back(new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.state,"DRIVE",driveSlider));
    
    // gain reduction
    //gainSlider.addListener(this);
    gainSlider.setSliderStyle(juce::Slider::LinearVertical);
    gainSlider.setBounds(220,90,120,120);
    //gainSlider.setRange(-10.f,0.f,0.1f);
    // gainSlider.setSkewFactorFromMidPoint(1.f);
    gainSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 60, 30);
    //gainSlider.setValue(audioProcessor.gain);
    addAndMakeVisible(gainSlider);
    
    sliderAttachments.emplace_back(new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.state,"GAIN",gainSlider));
}

DistortionClipAudioProcessorEditor::~DistortionClipAudioProcessorEditor()
{
}

//==============================================================================
void DistortionClipAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
    g.drawFittedText ("Drive",120,200, 100,40, juce::Justification::centred, 1);
    g.drawFittedText ("Gain Reduction",230,200, 100,40, juce::Justification::centred, 1);
}

void DistortionClipAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}

//void DistortionClipAudioProcessorEditor::sliderValueChanged(juce::Slider *slider){
//    if (slider == &driveSlider){
//        audioProcessor.drive = driveSlider.getValue();
//    }
//
//    if (slider == &gainSlider){
//        audioProcessor.gain= gainSlider.getValue();
//    }
//}
