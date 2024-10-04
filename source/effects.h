
#pragma once

class Effects {
public:
    static float muLaw(float input, float normalizedMu);
    static float gain(float input, float normalizedGain, float gainMax);

private:
    static float convertMu(float normalizedMu, float maxMu);
    static float muLawImpl(float input, float mu);
};
