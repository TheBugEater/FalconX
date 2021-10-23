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

class IFXInputController;

class FalconXEngine
{
public:
    static FalconXEngine&   CreateInstance(FalconXEngineConfig& config);
    static FalconXEngine&   GetInstance();
    static void             DestroyInstance();

    void                    AddModules(IFXModule* fxModule);
    void                    AddInputController(IFXInputController* controller);

    void                    SetNetworkStatus(ENetworkStatus status);
    ENetworkStatus          GetNetworkStatus() const;

    // This will block the current thread and start the FalconX Engine
    void                    Start();

private:
    static  FalconXEngine*  s_instance;
    FalconXEngine(FalconXEngineConfig& engineConfig);

    FalconXEngineConfig     m_engineConfig;
    FXFlightController*     m_flightController;
    ENetworkStatus          m_networkStatus;

    std::vector<IFXModule*>             m_modules;
    std::vector<IFXInputController*>    m_inputControllers;
};
