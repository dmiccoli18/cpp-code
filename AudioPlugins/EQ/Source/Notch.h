/*
  ==============================================================================

    Notch.h
    Created: 4 Dec 2024 10:06:50pm
    Author:  Drew Miccoli

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "EQ4band.h"

class Notch : public EQ4Band {
public:
    void setFreq (double newFreq);
    void setQ (double newQ);
private:
    void updateCoefficients();
    double freq = 20;
};

