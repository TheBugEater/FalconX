#include "Engine/FXEngine.h"
#include "Utils/FXUtils.h"
#include "Controllers/FXInputController.h"
#include <assert.h>

FalconXEngine* FalconXEngine::s_instance = nullptr;

FalconXEngine::FalconXEngine(FalconXEngineConfig& engineConfig)
    : m_engineConfig(engineConfig)
    , m_flightController(nullptr)
    , m_networkStatus(ENetworkStatus::None)
{
}

FalconXEngine& FalconXEngine::CreateInstance(FalconXEngineConfig& config)
{
    assert(!s_instance);

    s_instance = new FalconXEngine(config);
    return *s_instance;
}

FalconXEngine& FalconXEngine::GetInstance()
{
    assert(s_instance);

    return *s_instance;
}

void FalconXEngine::DestroyInstance()
{
    if (s_instance)
    {
        delete s_instance;
        s_instance = nullptr;
    }
}

void FalconXEngine::AddModules(IFXModule* fxModule)
{
    m_modules.push_back(fxModule);
}

void FalconXEngine::AddInputController(IFXInputController* controller)
{
    m_inputControllers.push_back(controller);
}

void FalconXEngine::SetNetworkStatus(ENetworkStatus status)
{
    m_networkStatus = status;
}

ENetworkStatus FalconXEngine::GetNetworkStatus() const
{
    return m_networkStatus;
}

void FalconXEngine::Start()
{
    m_flightController = FXFlightController::CreateInstance(m_engineConfig.FlightConfig);
    m_flightController->Init();

    for (auto mod : m_modules)
    {
        mod->Init();
    }

    for (auto inputController : m_inputControllers)
    {
        inputController->Init();
    }

    FX_Sleep(200);

    int64 lastTime = FX_GetMicros();
    while (true) 
    {
        int64 currentTime = FX_GetMicros();
        float currentMs = (float)(currentTime - lastTime) / 1000000;
        lastTime = currentTime;

        for (auto mod : m_modules)
        {
            mod->Update(currentMs);
        }

        for (auto inputController : m_inputControllers)
        {
            inputController->Update(currentMs);
        }

        m_flightController->Update(currentMs);

        FX_Sleep(1);
    }

    FXFlightController::DestroyInstance();
    m_flightController = nullptr;
}
