#pragma once

class IFXInputController
{
public:
    virtual bool            Init()                  = 0;
    virtual void            Update(float deltaMs)   = 0;
};