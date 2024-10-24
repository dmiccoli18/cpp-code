/*
  ==============================================================================

    AmpModulation.h
    Created: 19 Oct 2024 11:57:32pm
    Author:  Drew Miccoli

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class AmpModulation{
public:
    
    AmpModulation(float newRate, float newDepth); // constructor
    float processSample(float x, int c);
    
    void prepare(float newFs);
    
    void setRate(float newRate);
    
    void setDepth(float newDepth);
    
    void setAngle(float newPhase);
    
private:
    float Fs = 48000.f;
    float Ts = 1.f/Fs;
    
    float Rate = 1.f; //Hz
    float depth = 100.f; // %
    float phase = 0.f; // phase angle offset for stereo
    
    float  angleChange = 0.f;
    float amplitude = 0.5f;
    float dc = 0.5f;
    
    float currentAngle[2] = {0.f};
    const float pi2 = 2.f * M_PI;
};
