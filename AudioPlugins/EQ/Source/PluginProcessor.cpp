/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
EQAudioProcessor::EQAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       ), state(*this, nullptr, "PARAMETERS", createParameterLayout())
#endif
{
}

EQAudioProcessor::~EQAudioProcessor()
{
}

juce::AudioProcessorValueTreeState::ParameterLayout EQAudioProcessor::createParameterLayout(){
    std::vector<std::unique_ptr<juce::RangedAudioParameter>> params;
    
    //LPF
    params.push_back(std::make_unique<juce::AudioParameterFloat>("LOW", "Low",8000.f, 20000.f, 1.f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("LOWQ", "LowQ",.1f, 10.f, .1f));
    params.push_back(std::make_unique<juce::AudioParameterBool>("LBP", "LowBP", true));
    params.push_back(std::make_unique<juce::AudioParameterChoice>("LCOMBO", "LowCombo", juce::StringArray("Low Pass","Low Shelf"), 0));
    
    //Notch 1
    params.push_back(std::make_unique<juce::AudioParameterFloat>("NOTCH1", "Notch1",800.f, 6000.f, 1.f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("NOTCH1Q", "Notch1Q",.1f, 10.f, .1f));
    params.push_back(std::make_unique<juce::AudioParameterBool>("NBP", "NotchBP", true));
    
    //Notch 2
    params.push_back(std::make_unique<juce::AudioParameterFloat>("NOTCH2", "Notch2",5000.f, 10000.f, 1.f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("NOTCH2Q", "Notch2Q",.1f, 10.f, .1f));
    params.push_back(std::make_unique<juce::AudioParameterBool>("N1BP", "Notch1BP", true));
    
    //HPF
    params.push_back(std::make_unique<juce::AudioParameterFloat>("HIGH", "High",20.f, 1000.f, 1.f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("HIGHQ", "HighQ",.1f, 10.f, .1f));
    params.push_back(std::make_unique<juce::AudioParameterBool>("HBP", "HighBP", true));
    params.push_back(std::make_unique<juce::AudioParameterChoice>("HCOMBO", "HighCombo", juce::StringArray("High Pass","High Shelf"), 0));
    
    return {params.begin(), params.end()};
}

//==============================================================================
const juce::String EQAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool EQAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool EQAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool EQAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double EQAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int EQAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int EQAudioProcessor::getCurrentProgram()
{
    return 0;
}

void EQAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String EQAudioProcessor::getProgramName (int index)
{
    return {};
}

void EQAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void EQAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void EQAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool EQAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void EQAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    // Make sure to reset the state if your inner loop is processing
    // the samples and the outer loop is handling the channels.
    // Alternatively, you can process the samples with the channels
    // interleaved by keeping the same state.
    
    float LFreq = *state.getRawParameterValue("LOW");
    lowPass.setFreq((double)LFreq);
    lowPass.setFs(48000);
    float LQ = *state.getRawParameterValue("LOWQ");
    lowPass.setQ((double)LQ);
    lowPass.setAmp(ampdB);
    lowPass.setFilter(passShelf);
    
    //passShelf = *state.getRawParameterValue("LCOMBO");
    
    float HFreq = *state.getRawParameterValue("HIGH");
    highPass.setFreq((double)HFreq);
    highPass.setFs(48000);
    float HQ = *state.getRawParameterValue("HIGHQ");
    highPass.setQ((double)HQ);
    highPass.setAmp(ampdB);
    highPass.setFilter(PassShelf);
    
    float NFreq = *state.getRawParameterValue("NOTCH1");
    notch.setFreq((double)NFreq);
    notch.setFs(48000);
    float NQ = *state.getRawParameterValue("NOTCH1Q");
    notch.setQ((double)NQ);
    
    float N1Freq = *state.getRawParameterValue("NOTCH2");
    notch1.setFreq((double)N1Freq);
    notch1.setFs(48000);
    float N1Q = *state.getRawParameterValue("NOTCH2Q");
    notch1.setQ((double)N1Q);
    
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        for (int n = 0; n < buffer.getNumSamples() ; ++n){
            float x = buffer.getReadPointer(channel)[n];
            double y = x;
            
            // LPF
            if (!LPFOn){
                y = lowPass.filterSample(y, channel);
            }
            
            double y1 = y;
            // Notch
            if (!NFOn){
                y1 = notch.filterSample(y, channel);
            }
            else{
                y1 = y;
            }
            
            double y2 = y1;
            // Notch 1
            if (!NF1On){
                y2 = notch1.filterSample(y, channel);
            }
            else {
                y2 = y1;
            }
            
            double y3 = y2;
            // HPF
            if (!HPFOn){
                y3 = highPass.filterSample(y2, channel);
            }
            
            buffer.getWritePointer(channel)[n] = y3;
        }
        auto* channelData = buffer.getWritePointer (channel);

        // ..do something to the data...
    }
}

//==============================================================================
bool EQAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* EQAudioProcessor::createEditor()
{
    return new EQAudioProcessorEditor (*this);
}

//==============================================================================
void EQAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
    
    auto currentState = state.copyState();
    std::unique_ptr<juce::XmlElement> xml (currentState.createXml());
    copyXmlToBinary(*xml, destData);
}

void EQAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
    std::unique_ptr<juce::XmlElement> xml (getXmlFromBinary(data, sizeInBytes));
    if (xml && xml->hasTagName(state.state.getType())){
        state.replaceState(juce::ValueTree::fromXml(*xml));
    }
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new EQAudioProcessor();
}
