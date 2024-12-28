/*
  ==============================================================================

    Distortion.cpp
    Created: 19 Oct 2024 4:54:11pm
    Author:  Drew Miccoli

  ==============================================================================
*/

#include "Distortion.h"
#include <JuceHeader.h>

float Distortion::processSample(float x){
    float y = gain * ((2/M_PI) * atan(drive * x));
    return y;
}

void Distortion::setDrive(float newDrive){
    if (newDrive <= 10.f && newDrive > 1.f){
        drive = pow(10, newDrive/20);
    }
}

void Distortion::gainChange(float newGain){
    if(newGain <= 0.f && newGain > -10.f)
        gain = pow(10, newGain/20);
}
