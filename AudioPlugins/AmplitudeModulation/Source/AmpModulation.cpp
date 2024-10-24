/*
  ==============================================================================

    AmpModulation.cpp
    Created: 19 Oct 2024 11:57:32pm
    Author:  Drew Miccoli

  ==============================================================================
*/

#include "AmpModulation.h"

AmpModulation::AmpModulation(float newRate, float newDepth) : Rate(newRate), depth(newDepth){
    setRate(Rate);
    setDepth(depth);
}

float AmpModulation::processSample(float x, int c){
// figure out how to stereo process
    float lfo = amplitude * sin(currentAngle[c]) + dc;
    float y = x * lfo;
    
    currentAngle[c] += angleChange;
    if (currentAngle[c] > pi2){
        currentAngle[c] -= pi2;
    }
    return y;
}

void AmpModulation::prepare(float newFs){
    Fs = newFs;
}

void AmpModulation::setRate(float newRate){
    Rate = newRate;
    
    // angle change
    angleChange = Rate * 2.f * M_PI / Fs;
}

void AmpModulation::setAngle(float newPhase){
    phase = newPhase * (M_PI/180);
}

void AmpModulation::setDepth(float newDepth){
    depth = newDepth;
    
    // determine depth + dc offset
    amplitude = depth/200.f;
    dc = 1.f - amplitude;
}
