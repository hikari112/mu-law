
#include "effects.h"
#include "vstmath.h"
#include <cmath>

float Effects::convertMu(float normalizedMu, float maxMu = 512){
    return 1.0f + normalizedMu * maxMu;
}

float Effects::muLawImpl(float input, float mu){
    return VstMath::sign(input) * (log(1.0f + mu * abs(input)) / log(1 + mu));
}

float Effects::muLaw(float input, float normalizedMu) {
    float mu = convertMu(normalizedMu);
    return muLawImpl(input, mu);
}

float Effects::gain(float input, float normalizedGain, float gainMax) {
    return input * VstMath::rescale(normalizedGain, gainMax);
}
