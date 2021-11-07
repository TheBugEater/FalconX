#pragma once
#include "Core/FXTypes.h"

int64   FX_GetMicros();
void    FX_Sleep(int32 ms);

template<typename T, typename C>
T FX_Clamp(T a, C min, C max)
{
    if (a > max)
        return max;
    else if (a < min)
        return min;

    return a;
}