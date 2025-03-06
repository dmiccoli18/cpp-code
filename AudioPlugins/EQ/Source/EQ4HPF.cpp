/*
  ==============================================================================

    EQ4HPF.cpp
    Created: 3 Dec 2024 7:34:52pm
    Author:  Drew Miccoli

  ==============================================================================
*/

#include "EQ4HPF.h"

void EQ4HPF::setFilter (filterType newFilterType){
    passShelf = newFilterType;
    EQ4HPF::updateCoefficients();
}

void EQ4HPF::setFreq (double newFreq){
    freq = newFreq;
    EQ4HPF::updateCoefficients();
}

void EQ4HPF::setQ (double newQ){
    Q = newQ;
    EQ4HPF::updateCoefficients();
}

void EQ4HPF::setAmp (double newAmp){
    ampdB = newAmp;
    EQ4HPF::updateCoefficients();
}

// code doesn't pull from this update coefficients, find out why
void EQ4HPF::updateCoefficients(){
    double A = std::pow(10.0, ampdB / 40.0); // Linear amplitude
    
    // Normalize frequency
    double w0 = (2.0 * M_PI) * freq / Fs;
    
    // Bandwidth/slope/resonance parameter
    double alpha = std::sin(w0) / (2.0 * Q);
    double cw0 = std::cos(w0);
    double S = freq/Fs;
    
    if (passShelf == SHELF){
        alpha = (std::sin(w0)/2.0) * std::sqrt(((A + 1/A) * (1/S + 1)) + 2);
        cw0 = std::cos(w0);
    }
    
    switch(passShelf){
        case PASS: {
            a0 = 1.0 + alpha;
            double B0 = (1.0 + cw0) / 2.0;
            b0 = B0/a0;
            double B1 = -(1.0 + cw0);
            b1 = B1/a0;
            double B2 = (1.0 + cw0) / 2.0;
            b2 = B2/a0;
            double A1 = -2.0 * cw0;
            a1 = A1/a0;
            double A2 = 1.0 - alpha;
            a2 = A2/a0;
            break;
        }
            
        case SHELF: {
            double sqA = std::sqrt(A);
            a0 = (A + 1.0) - (A - 1.0) * cw0 + 2.0 * sqA * alpha;
            double B0 = A * ((A + 1.0) + (A - 1.0) * cw0 + 2.0 * sqA * alpha);
            b0 = B0/a0;
            double B1 = -2.0 * A * ((A - 1.0) + (A + 1.0) * cw0);
            b1 = B1/a0;
            double B2 = A * ((A + 1.0) + (A - 1.0) * cw0 - 2.0 * sqA * alpha);
            b2 = B2/a0;
            double A1 = 2.0 * ((A - 1.0) - (A + 1.0) * cw0);
            a1 = A1/a0;
            double A2 = (A + 1.0) - (A - 1.0) * cw0 - 2.0 * sqA * alpha;
            a2 = A2/a0;
            break;
        }
}
}
