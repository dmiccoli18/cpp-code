/*
  ==============================================================================

    Notch.cpp
    Created: 4 Dec 2024 10:06:50pm
    Author:  Drew Miccoli

  ==============================================================================
*/

#include "Notch.h"

void Notch::setFreq (double newFreq){
    freq = newFreq;
    Notch::updateCoefficients();
}

void Notch::setQ (double newQ){
    Q = newQ;
    Notch::updateCoefficients();
}

void Notch::updateCoefficients(){
    // Normalize frequency
    double w0 = (2.0 * M_PI) * freq / Fs;
    
    // Bandwidth/slope/resonance parameter
    double alpha = std::sin(w0) / (2.0 * Q);
    double cw0 = std::cos(w0);
    
    a0 = 1.0 + alpha;
    double B0 = 1.0;
    b0 = B0/a0;
    double B1 = -2.0 * cw0;
    b1 = B1/a0;
    double B2 = 1.0;
    b2 = B2/a0;
    double A1 = -2.0 * cw0;
    a1 = A1/a0;
    double A2 = 1.0 - alpha;
    a2 = A2/a0;
}
