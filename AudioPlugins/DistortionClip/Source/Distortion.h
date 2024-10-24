/*
  ==============================================================================

    Distortion.h
    Created: 19 Oct 2024 4:54:11pm
    Author:  Drew Miccoli

  ==============================================================================
*/

#pragma once

class Distortion {
public:
    float processSample(float x);
    
    void setDrive(float newDrive);
    
    void gainChange(float newGain);
    
private:
    float drive = 1.f;
    float gain = 0.f;
};
