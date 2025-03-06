/*
  ==============================================================================

    EQ4Band.cpp
    Created: 3 Dec 2024 6:17:21pm
    Author:  Drew Miccoli

  ==============================================================================
*/

#include "EQ4Band.h"

double EQ4Band::filterSample(double x, int channel)
{

    // Direct Form 1
    double y = b0 * x + b1 * x1[channel] + b2 * x2[channel]
            + (-a1) * y1[channel] + (-a2) * y2[channel];

    // store delay samples for next process step
    x2[channel] = x1[channel];
    x1[channel] = x;
    y2[channel] = y1[channel];
    y1[channel] = y;

    return y;
};

void EQ4Band::setFs(double newFs)
{
    Fs = newFs;
    updateCoefficients(); // Need to update if Fs changes, chances are mostly not
};

void EQ4Band::setFreq(double newFreq)
{
    freq = newFreq;
    updateCoefficients();
};

void EQ4Band::setQ(double newQ)
{
    Q = newQ;
    updateCoefficients();
};

void EQ4Band::setAmpdB(double newAmpdB)
{
    ampdB = newAmpdB;
    updateCoefficients();
};
    
void EQ4Band::updateCoefficients(){
    
    double A = std::pow(10.0, ampdB / 40.0); // Linear amplitude
    
    // Normalize frequency
    double w0 = (2.0 * M_PI) * freq / Fs;
    
    // Bandwidth/slope/resonance parameter
    double alpha = std::sin(w0) / (2.0 * Q);
    double cw0 = std::cos(w0);
};
