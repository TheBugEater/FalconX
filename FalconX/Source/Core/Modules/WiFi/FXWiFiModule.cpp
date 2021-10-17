#include "Core/Modules/WiFi/FXWiFiModule.h"

FXWiFiModule::FXWiFiModule(FXWiFiModuleConfig& config)
    : m_config(config)
    , m_wifiStatus(EWiFiStatus::Idle)
{
}

void FXWiFiModule::SetStatus(EWiFiStatus status)
{
    m_wifiStatus = status;
}

EWiFiStatus FXWiFiModule::GetStatus() const
{
    return m_wifiStatus;
}
