/*
  ==============================================================================

    EQ4Band.h
    Created: 3 Dec 2024 6:17:21pm
    Author:  Drew Miccoli

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class EQ4Band
{
public:

    double filterSample(double x, int channel);

    void setFs(double Fs);

    void setFreq(double freq);

    void setQ(double Q);

    void setAmpdB(double ampdB);
    
protected:
    void updateCoefficients();
    double Fs = 48000.0; // Sampling Rate

    // Variables for User to Modify Filter
    double freq; // frequency in Hz
    double Q = 0.707; // Q => [0.1 - 10]
    double ampdB = 0.0; // Amplitude on dB scale

    // Variables for Biquad Implementation
    // 2 channels - L,R : Up to 2nd Order
    
    //LPF/LS
    double x1[2] = { 0.0 }; // 1 sample of delay feedforward
    double x2[2] = { 0.0 }; // 2 samples of delay feedforward
    double y1[2] = { 0.0 }; // 1 sample of delay feedback
    double y2[2] = { 0.0 }; // 2 samples of delay feedback

    // Filter coefficients
    double b0 = 1.0; // initialized to pass signal
    double b1 = 0.0; // without filtering
    double b2 = 0.0;
    double a0 = 1.0;
    double a1 = 0.0;
    double a2 = 0.0;
};
