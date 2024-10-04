#include "vstmath.h"

int VstMath::sign(float x) {
    int sign;
    if (x >= 0)
        sign = 1;
    else
        sign = -1;
    return sign;
}

float VstMath::rescale(float x, float maxX) {
    if (maxX > 2)
        if (x <= 0.5)
            return 2.0f * x;
        else
            return 2.0f * (maxX - 1.0f) * (x - 0.5f) + 1.0f;
    else
        return x * maxX;
}


