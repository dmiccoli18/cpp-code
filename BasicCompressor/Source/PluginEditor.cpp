/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
BasicCompressorAudioProcessorEditor::BasicCompressorAudioProcessorEditor (BasicCompressorAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 300);
    
    // attack
    attackSlider.addListener(this);
    attackSlider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    attackSlider.setBounds(10,10,120,120);
    attackSlider.setRange(1, 100, 1);
    attackSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 60, 30);
    attackSlider.setValue(audioProcessor.attack);
    addAndMakeVisible(attackSlider);
    
    // release
    releaseSlider.addListener(this);
    releaseSlider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    releaseSlider.setBounds(10,140,120,120);
    releaseSlider.setRange(1, 100, 1);
    releaseSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 60, 30);
    releaseSlider.setValue(audioProcessor.release);
    addAndMakeVisible(releaseSlider);
    
    // threshold
    thresholdSlider.addListener(this);
    thresholdSlider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    thresholdSlider.setBounds(140,10,120,120);
    thresholdSlider.setRange(-30.f, 0.f,.1f);
    thresholdSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 60, 30);
    thresholdSlider.setValue(audioProcessor.threshold);
    addAndMakeVisible(thresholdSlider);
    
    // ratio
    ratioSlider.addListener(this);
    ratioSlider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    ratioSlider.setBounds(140,140,120,120);
    ratioSlider.setRange(1.f, 20.f,.1f);
    ratioSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 60, 30);
    ratioSlider.setValue(audioProcessor.ratio);
    addAndMakeVisible(ratioSlider);
    
    // gain
    gainKnob.addListener(this);
    gainKnob.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    gainKnob.setBounds(260,85,120,120);
    gainKnob.setRange(0.f, 10.f, .1f);
    gainKnob.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 60, 30);
    gainKnob.setValue(audioProcessor.gain);
    addAndMakeVisible(gainKnob);
    
    // bypass
    bypassButton.addListener(this);
    bypassButton.setBounds(307, 240, 120, 20);
    bypassButton.setButtonText("Bypass");
    bypassButton.setToggleState(audioProcessor.bypassOn, juce::dontSendNotification);
    addAndMakeVisible(bypassButton);
    
}

BasicCompressorAudioProcessorEditor::~BasicCompressorAudioProcessorEditor()
{
}

//==============================================================================
void BasicCompressorAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
    // add text for knobs
    g.drawFittedText ("Attack", 20,120,100,40, juce::Justification::centred, 1);
    g.drawFittedText ("Release", 20,250,100,40, juce::Justification::centred, 1);
    g.drawFittedText ("Threshold", 150,120,100,40, juce::Justification::centred, 1);
    g.drawFittedText ("Ratio", 150,250,100,40, juce::Justification::centred, 1);
    g.drawFittedText ("Gain", 270,195,100,40, juce::Justification::centred, 1);
}

void BasicCompressorAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}

void BasicCompressorAudioProcessorEditor::sliderValueChanged(juce::Slider *slider){
    if(slider == &attackSlider){
        audioProcessor.attack = attackSlider.getValue();
    }
    
    if(slider == &releaseSlider){
        audioProcessor.release = releaseSlider.getValue();
    }
    
    if(slider == &thresholdSlider){
        audioProcessor.threshold = thresholdSlider.getValue();
    }
    
    if(slider == &ratioSlider){
        audioProcessor.ratio = ratioSlider.getValue();
    }
    
    if(slider == &gainKnob){
        audioProcessor.gain= gainKnob.getValue();
    }
}

void BasicCompressorAudioProcessorEditor::buttonClicked(juce::Button *button){
    if(button == &bypassButton){
        audioProcessor.bypassOn = !audioProcessor.bypassOn;
    }
}
