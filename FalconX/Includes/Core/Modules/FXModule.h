#pragma once
#include "Core/FXTypes.h"

class IFXModule
{
public:
    virtual bool            Init()                  = 0;
    virtual void            Update(float deltaMs)   = 0;
};