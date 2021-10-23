#include "Core/Modules/WiFi/FXWiFiModule.h"
#include "Engine/FXEngine.h"

FXWiFiModule::FXWiFiModule(FXWiFiModuleConfig& config)
    : m_config(config)
    , m_wifiStatus(EWiFiStatus::Idle)
{
}

void FXWiFiModule::SetStatus(EWiFiStatus status)
{
    m_wifiStatus = status;
    if (m_wifiStatus == EWiFiStatus::Connected)
    {
        FalconXEngine::GetInstance().SetNetworkStatus(ENetworkStatus::Connected);
    }
    else
    {
        FalconXEngine::GetInstance().SetNetworkStatus(ENetworkStatus::Error);
    }
}

EWiFiStatus FXWiFiModule::GetStatus() const
{
    return m_wifiStatus;
}
