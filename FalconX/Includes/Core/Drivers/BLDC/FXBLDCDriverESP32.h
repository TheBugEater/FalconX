#pragma once
#include "Core/Drivers/BLDC/FXBLDCDriver.h"

class FXBLDCDriverESP32 : public FXBLDCDriver
{
public:
    FXBLDCDriverESP32(FXBLDCDriverConfig& config);

    virtual void            SetSpeed(float speed) override;

private:
    uint8                   m_ledcChannel;
    static uint8            m_availableChannels[8];
    static bool             m_isTimerInitialised;

    float                   m_minPercentageValue;
    float                   m_maxPercentageValue;
    float                   m_percentageValueRange;
};

