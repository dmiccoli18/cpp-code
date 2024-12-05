/*
  ==============================================================================

    EQ4HPF.h
    Created: 3 Dec 2024 7:34:52pm
    Author:  Drew Miccoli

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "EQ4Band.h"

class EQ4HPF : public EQ4Band {
public:
    enum filterType { PASS, SHELF };
    void setFilter (filterType newFilterType);
    void setFreq (double freq);
    void setQ (double Q);
    
private:
    filterType passShelf = PASS;
    void updateCoefficients();
    double freq = 20000;
};
