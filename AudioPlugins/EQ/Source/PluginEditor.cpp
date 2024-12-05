/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
EQAudioProcessorEditor::EQAudioProcessorEditor (EQAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 300);
    
    // LPF
    lowPassSlider.addListener(this);
    lowPassSlider.setBounds(40,10,240,120);
    lowPassSlider.setValue(audioProcessor.LFreq);
    lowPassSlider.setRange(8000,20000, 1);
    lowPassSlider.setSliderStyle(juce::Slider::LinearHorizontal);
    addAndMakeVisible(lowPassSlider);
    
    // ComboBox
    lowPassShelf.addListener(this);
    lowPassShelf.addItem("Low Pass",1);
    lowPassShelf.addItem("Low Shelf",2);
    lowPassShelf.setSelectedId(1);
    lowPassShelf.setBounds(40, 10, 80, 40);
    addAndMakeVisible(lowPassShelf);
    
    // Bypass
    LPFToggle.addListener(this);
    LPFToggle.setBounds(170, 40, 120, 20);
    LPFToggle.setButtonText("Bypass");
    LPFToggle.setToggleState(audioProcessor.LPFOn, juce::dontSendNotification);
    addAndMakeVisible(LPFToggle);
    
    // LPF Q
    lowPassQ.addListener(this);
    lowPassQ.setBounds(300, 37, 65, 65);
    lowPassQ.setValue(audioProcessor.LQ);
    lowPassQ.setRange(.1, 10, .1);
    lowPassQ.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    lowPassQ.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 60, 20);
    addAndMakeVisible(lowPassQ);
    
    // Notch Filter
    notchSlider.addListener(this);
    notchSlider.setBounds(40,65,240,120);
    notchSlider.setValue(audioProcessor.NFreq);
    notchSlider.setRange(800, 6000, 1);
    notchSlider.setSliderStyle(juce::Slider::LinearHorizontal);
    addAndMakeVisible(notchSlider);
    
    // Bypass
    NToggle.addListener(this);
    NToggle.setBounds(170, 95, 120, 20);
    NToggle.setButtonText("Bypass");
    NToggle.setToggleState(audioProcessor.NFOn, juce::dontSendNotification);
    addAndMakeVisible(NToggle);
    
    // Notch Q
    notchQ.addListener(this);
    notchQ.setBounds(300, 97, 65, 65);
    notchQ.setValue(audioProcessor.NQ);
    notchQ.setRange(.1, 10, .1);
    notchQ.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    notchQ.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 60, 20);
    addAndMakeVisible(notchQ);
    
    
    // Notch1 Filter
    notch1Slider.addListener(this);
    notch1Slider.setBounds(40,125,240,120);
    notch1Slider.setValue(audioProcessor.N1Freq);
    notch1Slider.setRange(4000, 10000, 1);
    notch1Slider.setSliderStyle(juce::Slider::LinearHorizontal);
    addAndMakeVisible(notch1Slider);
    
    // Bypass
    N1Toggle.addListener(this);
    N1Toggle.setBounds(170, 155, 120, 20);
    N1Toggle.setButtonText("Bypass");
    N1Toggle.setToggleState(audioProcessor.NF1On, juce::dontSendNotification);
    addAndMakeVisible(N1Toggle);
    
    // Notch1 Q
    notch1Q.addListener(this);
    notch1Q.setBounds(300, 157, 65, 65);
    notch1Q.setValue(audioProcessor.N1Q);
    notch1Q.setRange(.1, 10, .1);
    notch1Q.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    notch1Q.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 60, 20);
    addAndMakeVisible(notch1Q);
    
    // HPF
    highPassSlider.addListener(this);
    highPassSlider.setBounds(40,180,240,120);
    highPassSlider.setValue(audioProcessor.HFreq);
    highPassSlider.setRange(20, 1000, 1);
    highPassSlider.setSliderStyle(juce::Slider::LinearHorizontal);
    addAndMakeVisible(highPassSlider);
    
    // Combo Box
    highPassShelf.addListener(this);
    highPassShelf.addItem("High Pass",1);
    highPassShelf.addItem("High Shelf",2);
    highPassShelf.setSelectedId(1);
    highPassShelf.setBounds(40, 260, 80, 40);
    addAndMakeVisible(highPassShelf);
    
    // Bypass
    HPFToggle.addListener(this);
    HPFToggle.setBounds(170, 210, 120, 20);
    HPFToggle.setButtonText("Bypass");
    HPFToggle.setToggleState(audioProcessor.HPFOn, juce::dontSendNotification);
    addAndMakeVisible(HPFToggle);
    
    // HPF Q
    highPassQ.addListener(this);
    highPassQ.setBounds(300, 217, 65, 65);
    highPassQ.setValue(audioProcessor.LQ);
    highPassQ.setRange(.1, 10, .1);
    highPassQ.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    highPassQ.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 60, 20);
    addAndMakeVisible(highPassQ);
    
}

EQAudioProcessorEditor::~EQAudioProcessorEditor()
{
}

//==============================================================================
void EQAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
    g.drawFittedText ("Notch",20,95,120,20, juce::Justification::centred, 1);
    g.drawFittedText ("Notch",20,155,120,20, juce::Justification::centred, 1);
    g.drawFittedText ("Q Factor",270,20,120,20, juce::Justification::centred, 1);
}

void EQAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}

void EQAudioProcessorEditor::comboBoxChanged(juce::ComboBox *comboBox){
    if (comboBox == &lowPassShelf){
        if (lowPassShelf.getSelectedId() == 1){
            audioProcessor.passShelf = EQ4LPF::filterType::PASS;
        }
        if (lowPassShelf.getSelectedId() == 2){
            audioProcessor.passShelf = EQ4LPF::filterType::SHELF;
        }
    }
    
    if (comboBox == &highPassShelf){
        if (highPassShelf.getSelectedId() == 1){
            audioProcessor.PassShelf = EQ4HPF::filterType::PASS;
        }
        if (highPassShelf.getSelectedId() == 2){
            audioProcessor.PassShelf = EQ4HPF::filterType::SHELF;
        }
    }
}

void EQAudioProcessorEditor::sliderValueChanged(juce::Slider *slider){
    if (slider == &lowPassSlider){
        audioProcessor.LFreq = lowPassSlider.getValue();
    }
    
    if (slider == &highPassSlider){
        audioProcessor.HFreq = highPassSlider.getValue();
    }
    
    if (slider == &notchSlider){
        audioProcessor.NFreq = notchSlider.getValue();
    }
    
    // NFreq -> N1Freq
    if (slider == &notch1Slider){
        audioProcessor.N1Freq = notch1Slider.getValue();
    }
    
    if (slider == &lowPassQ){
        audioProcessor.LQ = lowPassQ.getValue();
    }
    
    if (slider == &highPassQ){
        audioProcessor.HQ = highPassQ.getValue();
    }
    
    if (slider == &notchQ){
        audioProcessor.NQ = notchQ.getValue();
    }
    
    // NQ -> N1Q
    if (slider == &notch1Q){
        audioProcessor.N1Q = notch1Q.getValue();
    }
}

void EQAudioProcessorEditor::buttonClicked(juce::Button *button){
    if (button == &LPFToggle){
        audioProcessor.LPFOn = !audioProcessor.LPFOn;
    }
    if (button == &NToggle){
        audioProcessor.NFOn = !audioProcessor.NFOn;
    }
    if (button == &N1Toggle){
        audioProcessor.NF1On = !audioProcessor.NF1On;
    }
    if (button == &HPFToggle){
        audioProcessor.HPFOn = !audioProcessor.HPFOn;
    }
}
