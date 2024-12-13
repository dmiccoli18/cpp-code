/*
  ==============================================================================

    WahWah.cpp
    Created: 12 Dec 2024 5:41:49pm
    Author:  Drew Miccoli

  ==============================================================================
*/

#include "WahWah.h"

void WahWah::setWidth(double newWidth){
    width = newWidth;
    amp = width / 2;
    if (dc - amp <= 20){
        amp = dc + 1;
    }
}

void WahWah::setDC(double newDC){
    dc = newDC;
}

void WahWah::setWetDry(double newWetDry){
    WetDry = newWetDry;
}

void WahWah::setRate(double newRate){
    rate = newRate;
    angleChange = rate * 2.f * M_PI / Fs;
}

double WahWah::processSample(double x, int c){
    double freq = amp * cos(currentAngle[c]) + dc;
    
    // negative frequency bug
    if ((dc - amp) <= 0)
        freq = abs(freq);
    
    EQ4LPF::setFreq(freq);
    double y = EQ4Band::filterSample(x, c);
    
    currentAngle[c] += angleChange;
    if (currentAngle[c] > pi2){
        currentAngle[c] -= pi2;
    }
    
    // series
    //return y;
    // parallel
    double z = ((1-WetDry) * x) + (WetDry*y);
    return z;
}
