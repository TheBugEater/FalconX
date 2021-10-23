#pragma once
#include "Core/Drivers/FXDriver.h"
#include "Core/FXTypes.h"

struct FXBLDCDriverConfig
{
    uint8               PinOut;
};

class FXBLDCDriver : public IFXDriver
{
public:
    FXBLDCDriver(FXBLDCDriverConfig& config);

    // Set Motor Speed 0 - 1
    virtual void                    SetSpeed(float speed) {};

protected:
    FXBLDCDriverConfig              m_config;
};
