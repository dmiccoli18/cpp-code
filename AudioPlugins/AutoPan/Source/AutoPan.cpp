/*
  ==============================================================================

    AutoPan.cpp
    Created: 20 Oct 2024 8:32:33pm
    Author:  Drew Miccoli

  ==============================================================================
*/

#include "AutoPan.h"

AutoPan::AutoPan(float newRate, float newDepth, float newAngle) : Rate(newRate), depth(newDepth), phase(newAngle){
    setRate(Rate);
    setDepth(depth);
    setAngle(phase);
}

float AutoPan::processSample(float x, int c){
    // figure out how to stereo process
    
    float y;
    float lfo;
    
    if (c == 0){
        lfo = amplitude * sin(currentAngle[c]) + dc;
        y = x * lfo;
    }
    else if (c == 1){
        lfo = amplitude * sin(currentAngle[c] + phase) + dc;
        y = x * lfo;
    }
    else {
        y = x;
    }
    
    currentAngle[c] += angleChange;
    if (currentAngle[c] > pi2){
        currentAngle[c] -= pi2;
    }
    return y;
}

void AutoPan::prepare(float newFs){
    Fs = newFs;
}

void AutoPan::setRate(float newRate){
    Rate = newRate;
    
    // angle change
    angleChange = Rate * 2.f * M_PI / Fs;
}

void AutoPan::setAngle(float newPhase){
    phase = newPhase * (M_PI/180);
}

void AutoPan::setDepth(float newDepth){
    depth = newDepth;
    
    // determine depth + dc offset
    amplitude = depth/200.f;
    dc = 1.f - amplitude;
}
