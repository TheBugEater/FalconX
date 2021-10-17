#pragma once
#include "Core/Modules/WiFi/FXWiFiModule.h"

class FXWiFiModuleESP32 : public FXWiFiModule
{
public:

    FXWiFiModuleESP32(FXWiFiModuleConfig& config);

    virtual bool                        Init() override;
    virtual void                        Update(float deltaMs) override;
};