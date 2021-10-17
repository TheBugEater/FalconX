#pragma once

class IFXInputController
{
    virtual ~IInputController() {};

    virtual bool            Init() = 0;
    virtual void            Update(float deltaMs) = 0;
};