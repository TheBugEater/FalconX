#include "Core/Modules/WiFi/FXWiFiModuleESP32.h"

#include "nvs_flash.h"
#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_log.h"
#include <cstring>

void    WiFiControllerEventHandler(void* arg, esp_event_base_t event_base, int32_t event_id, void* event_data)
{
    FXWiFiModuleESP32* wifiModule = (FXWiFiModuleESP32*)arg;
    if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_START)
    {
        ESP_LOGI("FluxWiFiInputController", "Connecting to WiFi...");
        esp_wifi_connect();
        wifiModule->SetStatus(EWiFiStatus::Connecting);
    }
    else if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_DISCONNECTED)
    {
        ESP_LOGI("FluxWiFiInputController", "Connecting to WiFi...");
        esp_wifi_connect();
        wifiModule->SetStatus(EWiFiStatus::Connecting);
    }
    else if (event_base == IP_EVENT && event_id == IP_EVENT_STA_GOT_IP)
    {
        ip_event_got_ip_t* event = (ip_event_got_ip_t*)event_data;
        ESP_LOGI("FluxWiFiInputController", "Connected: Local IP :" IPSTR, IP2STR(&event->ip_info.ip));
        wifiModule->SetStatus(EWiFiStatus::Connected);
    }
}

FXWiFiModuleESP32::FXWiFiModuleESP32(FXWiFiModuleConfig& config)
    : FXWiFiModule(config)
{
}

bool FXWiFiModuleESP32::Init()
{
    ESP_LOGI("FluxWiFiInputController", "Initializing WiFi...");

    ESP_ERROR_CHECK(nvs_flash_init());
    ESP_ERROR_CHECK(esp_netif_init());
    ESP_ERROR_CHECK(esp_event_loop_create_default());

    esp_netif_create_default_wifi_sta();
    wifi_init_config_t init_config = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&init_config));

    esp_event_handler_instance_t instance_any_id;
    esp_event_handler_instance_t instance_got_ip;

    ESP_ERROR_CHECK(esp_event_handler_instance_register(WIFI_EVENT,
        ESP_EVENT_ANY_ID,
        &WiFiControllerEventHandler,
        this,
        &instance_any_id));
    ESP_ERROR_CHECK(esp_event_handler_instance_register(IP_EVENT,
        IP_EVENT_STA_GOT_IP,
        &WiFiControllerEventHandler,
        this,
        &instance_got_ip));

    wifi_config_t wifi_config = {};
    memcpy(wifi_config.sta.ssid, m_config.m_ssid, sizeof(m_config.m_ssid));
    memcpy(wifi_config.sta.password, m_config.m_password, sizeof(m_config.m_password));

    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));
    ESP_ERROR_CHECK(esp_wifi_set_config(WIFI_IF_STA, &wifi_config));
    ESP_ERROR_CHECK(esp_wifi_start());

    SetStatus(EWiFiStatus::Connecting);

    return true;
}

void FXWiFiModuleESP32::Update(float deltaMs)
{
}

