#include <stdio.h>
#include "Engine/FXEngine.h"
#include "Core/Modules/WiFi/FXWiFiModuleESP32.h"
#include "Core/Modules/Gyro/FXGyroModuleMPU6050.h"

extern "C"
{
        void app_main(void);
}

void app_main(void)
{
    FXWiFiModuleConfig  wifiConfig = { "TheBug's WiFi", "Fello@0123456"};
    FXWiFiModuleESP32* wifiModule = new FXWiFiModuleESP32(wifiConfig);

    FXGyroModuleMPU6050* gyroModule = new FXGyroModuleMPU6050();

    FalconXEngineConfig config;
    FalconXEngine& engine = FalconXEngine::CreateInstance(config);

    engine.AddModules(wifiModule);
    engine.AddModules(gyroModule);

    engine.Start();
}
