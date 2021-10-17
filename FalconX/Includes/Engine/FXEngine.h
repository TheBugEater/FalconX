#pragma once
#include "Core/FXTypes.h"
#include "Core/Modules/FXModule.h"
#include "Core/Drivers/FXDriver.h"
#include "FlightController/FXFlightController.h"

#include <vector>

struct FalconXEngineConfig
{
    FXFlightControllerConfig            FlightConfig;
};

class FalconXEngine
{
public:
    static FalconXEngine&   CreateInstance(FalconXEngineConfig& config);
    static FalconXEngine&   GetInstance();
    static void             DestroyInstance();

    void                    AddModules(FXIModule* fxModule);
    void                    AddDriver(FXIDriver* driver);

    template<typename T>
    T*                      GetDriverByType();

    // This will block the current thread and start the FalconX Engine
    void                    Start();

private:
    static  FalconXEngine*  s_instance;
    FalconXEngine(FalconXEngineConfig& engineConfig);

    FalconXEngineConfig     m_engineConfig;
    FXFlightController*     m_flightController;

    std::vector<FXIModule*> m_modules;
    std::vector<FXIDriver*> m_drivers;
};

template<typename T>
T* FalconXEngine::GetDriverByType()
{
    for (auto driver : m_drivers)
    {
        if (dynamic_cast<T>(driver))
        {
            return reinterpret_cast<T*>(driver);
        }
    }

    return nullptr;
}
