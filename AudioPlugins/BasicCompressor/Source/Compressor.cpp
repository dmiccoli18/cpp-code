/*
  ==============================================================================

    Compressor.cpp
    Created: 24 Oct 2024 12:28:35am
    Author:  Drew Miccoli

  ==============================================================================
*/

#include "Compressor.h"

// compressor constructor
Compressor::Compressor(float newAttack, float newRelease, float newThreshold, float newRatio) : attack(newAttack), release(newRelease), threshold(newThreshold), ratio(newRatio)
{
    setAttack(attack);
    setRelease(release);
    setThreshold(threshold);
    setRatio(ratio);
}

// make these all into constructors:
void Compressor::setAttack(float newAttack){
    attack = newAttack / 1000;
}

void Compressor::setRelease(float newRelease){
    release = newRelease / 1000;
}

void Compressor::setThreshold(float newThreshold){
    threshold = newThreshold;
}

void Compressor::setRatio(float newRatio){
    ratio = newRatio;
}

void Compressor::setGain(float newGain){
    gain = newGain;
}

float Compressor::Compress(float x){
    /*
     x_abs = abs(x);
     x_dB = 20*log10(x_abs);
     if (x_dB < -144)
         x_dB = -144;
     end
     */
    float x_dB = 20.f * log10(abs(x));
    
    if (x_dB < -144.f){
        x_dB = -144.f;
    }
    
    float x_sc;
    if (x_dB < threshold){
        x_sc = x_dB;
    }
    else{
        x_sc = threshold + (x_dB - threshold)/ratio;
    }
    
    float x_gr = x_sc - x_dB;
    
    // attack and release
    if (x_gr < gainSmoothPrev){
        gainSmooth = ((1-alphaA)*x_gr) + (alphaA*gainSmoothPrev);
    }
    else {
        gainSmooth = ((1-alphaR)*x_gr) + (alphaR*gainSmoothPrev);
    }
    
    // wrong
    float g_lin = pow(10.f, gainSmooth/20);
    
    float y = g_lin * x;
    
    gainSmoothPrev = gainSmooth;
    return y;
}

float Compressor::makeupGain(float x){
    float ampGain = pow(10, gain/20);
    float y = ampGain * x;
    return y;
}


/*
 N = length(in);

 R = 3;
 T = -10;
 Att = .5;
 Rel = .1;
 alphaA = exp(-log(9)/(Att*Fs));
 alphaR = exp(-log(9)/(Rel*Fs));

 g_smoothPrev = 0;

 y = zeros(N,1);
 for n = 1:N
     x = in(n,1);
     x_abs = abs(x);
     x_dB = 20*log10(x_abs);
     if (x_dB < -144)
         x_dB = -144;
     end
     
     if (x_dB < T)
         x_sc = x_dB;
     else
         x_sc = T + (x_dB - T)/R;
     end
     x_gr = x_sc - x_dB;
 %     g_lin = 10^(x_gr/20);
 %     g_smooth = (1-alpha) * x_gr + alpha * g_smoothPrev;
      if (x_gr < g_smoothPrev)
          %attack
          g_smooth = (1-alphaA) * x_gr + alphaA * g_smoothPrev;
      else
          %release
          g_smooth = (1-alphaR) * x_gr + alphaR * g_smoothPrev;
      end
      g_lin = 10^(g_smoothPrev/20);
      y(n,1) = g_lin * x
 */
