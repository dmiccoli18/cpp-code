/*
  ==============================================================================

    EQ4LPF.h
    Created: 3 Dec 2024 7:07:53pm
    Author:  Drew Miccoli

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "EQ4Band.h"

class EQ4LPF : public EQ4Band {
public:
    enum filterType { PASS, SHELF };
    void setFilter (filterType newFilterType);
    void setFreq (double newFreq);
    void setQ (double newQ);
    void setAmp (double ampdB);
    
private:
    filterType passShelf = PASS;
    void updateCoefficients();
    double freq = 20;
    double ampdB = 3;
};
