/*
  ==============================================================================

    Compressor.h
    Created: 24 Oct 2024 12:28:35am
    Author:  Drew Miccoli

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class Compressor{
    
public:
    
    Compressor(float newAttack, float newRelease, float newThreshold, float newRatio);
    
    void setAttack(float newAttack);
    
    void setRelease(float newRelease);
    
    void setThreshold(float newThreshold);
    
    void setRatio(float newRatio);
    
    void setGain(float newGain);
    
    float Compress(float x);
    
    float makeupGain(float x);
    
    
private:
    float Fs = 48000.f;
    float gainSmooth;
    float gainSmoothPrev = 0;
    
    float attack;
    float release;
    float threshold;
    float ratio;
    float gain; // in dB
    
    // initialize smoothing variables
    float alphaA = exp(-log(9.f)/(Fs * attack));
    float alphaR = exp(-log(9.f)/(Fs * release));
};


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
 */
