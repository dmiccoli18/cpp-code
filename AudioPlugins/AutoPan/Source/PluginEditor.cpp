/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
AutoPanAudioProcessorEditor::AutoPanAudioProcessorEditor (AutoPanAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 300);
    
    // rate slider
    // rateSlider.addListener(this);
    rateSlider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    rateSlider.setBounds(10,90,120,120);
    // rateSlider.setRange(1.f,5.f,.1f);
    rateSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 60, 30);
    //rateSlider.setValue(audioProcessor.Rate);
    addAndMakeVisible(rateSlider);
    
    sliderAttachments.emplace_back(new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.state,"RATE",rateSlider));
    
    
    // depth slider
    // depthSlider.addListener(this);
    depthSlider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    depthSlider.setBounds(150,90,120,120);
    //depthSlider.setRange(0.f,100.f,0.01f);
    depthSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 60, 30);
    // depthSlider.setValue(audioProcessor.depth);
    addAndMakeVisible(depthSlider);
    
    sliderAttachments.emplace_back(new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.state,"DEPTH",depthSlider));
    
    // angle slider
    // angleSlider.addListener(this);
    angleSlider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    angleSlider.setBounds(290,90,120,120);
    // angleSlider.setRange(0.f,180.f,1.f);
    // gainSlider.setSkewFactorFromMidPoint(1.f);
    angleSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 60, 30);
    // angleSlider.setValue(audioProcessor.phase);
    addAndMakeVisible(angleSlider);
    
    sliderAttachments.emplace_back(new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.state,"PHASE",angleSlider));
    
    // mute button
    bypassButton.addListener(this);
    bypassButton.setBounds(195, 240, 120, 20);
    bypassButton.setButtonText("Bypass");
    bypassButton.setToggleState(audioProcessor.bypassOn, juce::dontSendNotification);
    addAndMakeVisible(bypassButton);
}

AutoPanAudioProcessorEditor::~AutoPanAudioProcessorEditor()
{
}

//==============================================================================
void AutoPanAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
    //g.drawFittedText ("Hello World!", getLocalBounds(), juce::Justification::centred, 1);
    g.drawFittedText ("Rate", 20,115, 100,40, juce::Justification::centred, 1);
    g.drawFittedText ("Depth", 160,115, 100,40, juce::Justification::centred, 1);
    g.drawFittedText ("Angle", 300,115, 100,40, juce::Justification::centred, 1);
}

void AutoPanAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}

//void AutoPanAudioProcessorEditor::sliderValueChanged(juce::Slider *slider){
//    if (slider == &rateSlider){
//        audioProcessor.Rate = rateSlider.getValue();
//    }
//    if (slider == &depthSlider){
//        audioProcessor.depth = depthSlider.getValue();
//    }
//    if (slider == &angleSlider){
//        audioProcessor.phase = angleSlider.getValue();
//    }
//}

void AutoPanAudioProcessorEditor::buttonClicked(juce::Button *button){
    if (button == &bypassButton){
        audioProcessor.bypassOn = !audioProcessor.bypassOn;
    }
}
