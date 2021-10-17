#pragma once
#include "Core/Drivers/BLDC/FXBLDCDriver.h"

class FXBLDCDriverESP32 : public FXBLDCDriver
{
public:
    FXBLDCDriverESP32(FXBLDCDriverConfig& config);

    virtual void            SetPulseWidth(uint32 pulseWidth) override;

private:
    uint8                   m_ledcChannel;
    static uint8            m_availableChannels[8];
    static bool             m_isTimerInitialised;
};

