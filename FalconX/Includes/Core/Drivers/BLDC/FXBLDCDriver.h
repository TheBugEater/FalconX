#pragma once
#include "Core/Drivers/FXDriver.h"
#include "Core/FXTypes.h"

struct FXBLDCDriverConfig
{
    uint8               PinOut;
    uint16              MinPulseWidth;
    uint16              MaxPulseWidth;
};

class FXBLDCDriver : public IFXDriver
{
public:
    FXBLDCDriver(FXBLDCDriverConfig& config);

    virtual void                    SetPulseWidth(uint32 pulseWidth) {};

protected:
    FXBLDCDriverConfig              m_config;
};
