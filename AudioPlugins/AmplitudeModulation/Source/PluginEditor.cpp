/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
AmplitudeModulationAudioProcessorEditor::AmplitudeModulationAudioProcessorEditor (AmplitudeModulationAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 300);
    
    // rate slider
    //rateSlider.addListener(this);
    rateSlider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    rateSlider.setBounds(40,90,120,120);
    //rateSlider.setRange(1.f,5.f,.1f);
    // gainSlider.setSkewFactorFromMidPoint(1.f);
    rateSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 60, 30);
    //rateSlider.setValue(audioProcessor.Rate);
    addAndMakeVisible(rateSlider);
    
    sliderAttachments.emplace_back(new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.state,"RATE",rateSlider));
    
    // depth slider
    //depthSlider.addListener(this);
    depthSlider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    depthSlider.setBounds(180,90,120,120);
    //depthSlider.setRange(0.f,100.f,0.01f);
    // gainSlider.setSkewFactorFromMidPoint(1.f);
    depthSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 60, 30);
    //depthSlider.setValue(audioProcessor.depth);
    addAndMakeVisible(depthSlider);
    
    sliderAttachments.emplace_back(new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.state,"DEPTH",depthSlider));
}

AmplitudeModulationAudioProcessorEditor::~AmplitudeModulationAudioProcessorEditor()
{
}

//==============================================================================
void AmplitudeModulationAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
    g.drawFittedText ("Rate", 50,115, 100,40, juce::Justification::centred, 1);
    g.drawFittedText ("Depth", 190,115, 100,40, juce::Justification::centred, 1);
    //g.drawFittedText(<#const String &text#>, <#int x#>, <#int y#>, <#int width#>, <#int height#>, <#Justification justificationFlags#>, <#int maximumNumberOfLines#>)
}

void AmplitudeModulationAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor.
}

//void AmplitudeModulationAudioProcessorEditor::sliderValueChanged(juce::Slider *slider){
//    if (slider == &rateSlider){
//        audioProcessor.Rate = rateSlider.getValue();
//    }
//    if (slider == &depthSlider){
//        audioProcessor.depth = depthSlider.getValue();
//    }
