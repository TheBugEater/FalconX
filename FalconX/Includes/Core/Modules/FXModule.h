#pragma once
#include "Core/FXTypes.h"

class FXIModule
{
public:
    virtual bool            Init()                  = 0;
    virtual void            Update(float deltaMs)   = 0;
};