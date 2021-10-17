#pragma once
#include "Core/Modules/FXModule.h"

struct FXWiFiModuleConfig
{
    char            m_ssid[32];
    char            m_password[32];
};

enum class EWiFiStatus
{
    Idle,
    Connecting,
    Connected,
    Error
};

class FXWiFiModule: public FXIModule
{
public:

    FXWiFiModule(FXWiFiModuleConfig& config);

    void                                SetStatus(EWiFiStatus status);
    EWiFiStatus                         GetStatus() const;

protected:
    FXWiFiModuleConfig                  m_config;
    EWiFiStatus                         m_wifiStatus;
};