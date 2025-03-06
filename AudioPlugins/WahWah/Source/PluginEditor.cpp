/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
WahWahAudioProcessorEditor::WahWahAudioProcessorEditor (WahWahAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 300);
    
    //rateSlider.addListener(this);
    rateSlider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    rateSlider.setBounds(80,10,110,110);
    //rateSlider.setRange(.1,5,.01);
    rateSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 60, 30);
    //rateSlider.setValue(audioProcessor.rate);
    addAndMakeVisible(rateSlider);
    sliderAttachments.emplace_back(new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.state,"RATE",rateSlider));
    
    //freqSlider.addListener(this);
    freqSlider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    freqSlider.setBounds(220,10,110,110);
    //freqSlider.setRange(250,5000,1);
    freqSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 60, 30);
    //freqSlider.setValue(audioProcessor.dc);
    addAndMakeVisible(freqSlider);
    sliderAttachments.emplace_back(new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.state,"FREQ",freqSlider));
    
    //widthSlider.addListener(this);
    widthSlider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    widthSlider.setBounds(80,150,110,110);
    //widthSlider.setRange(250,2000,1);
    widthSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 60, 30);
    //widthSlider.setValue(audioProcessor.width);
    addAndMakeVisible(widthSlider);
    sliderAttachments.emplace_back(new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.state,"WIDTH",widthSlider));
    
    //wetDrySlider.addListener(this);
    wetDrySlider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    wetDrySlider.setBounds(220,150,110,110);
    //wetDrySlider.setRange(0,1,.01);
    wetDrySlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 60, 30);
    //wetDrySlider.setValue(audioProcessor.width);
    addAndMakeVisible(wetDrySlider);
    sliderAttachments.emplace_back(new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.state,"WETDRY",wetDrySlider));
    
}

WahWahAudioProcessorEditor::~WahWahAudioProcessorEditor()
{
}

//==============================================================================
void WahWahAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
    g.drawFittedText ("Rate",75,120,120,20, juce::Justification::centred, 1);
    g.drawFittedText ("Width",75,260,120,20, juce::Justification::centred, 1);
    g.drawFittedText ("Center Frequency",215,120,120,20, juce::Justification::centred, 1);
    g.drawFittedText ("Dry/Wet",215,260,120,20, juce::Justification::centred, 1);
}

void WahWahAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}

//void WahWahAudioProcessorEditor::sliderValueChanged(juce::Slider *slider){
//    if(slider == &rateSlider){
//        audioProcessor.rate = rateSlider.getValue();
//    }
//
//    if(slider == &freqSlider){
//        audioProcessor.dc = freqSlider.getValue();
//    }
//
//    if(slider == &widthSlider){
//        audioProcessor.width = widthSlider.getValue();
//    }
//
//    if(slider == &wetDrySlider){
//        audioProcessor.wetDry = wetDrySlider.getValue();
//    }
