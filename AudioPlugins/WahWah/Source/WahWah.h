/*
  ==============================================================================

    WahWah.h
    Created: 12 Dec 2024 5:41:49pm
    Author:  Drew Miccoli

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "EQ4LPF.h"

class WahWah : public EQ4LPF {
public:
    void setWidth(double newWidth);
    void setDC(double newDC);
    void setRate(double newRate);
    void setWetDry(double wetDry);
    double processSample(double x, int c);
    
private:
    double rate = 1;
    double width = 1000;
    double amp = 500;
    double dc = 500; //acts as center freq
    double currentAngle[2] = {0};
    double angleChange = 0;
    double pi2 = M_PI * 2;
    double WetDry = 1;
};
