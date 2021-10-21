#include "FlightController/FXFlightController.h"
#include "FlightController/FXFlightPIDController.h"
#include <assert.h>

FXFlightController* FXFlightController::s_instance = nullptr;

FXFlightController* FXFlightController::CreateInstance(FXFlightControllerConfig& config)
{
    assert(!s_instance);

    s_instance = new FXFlightController(config);
    return s_instance;
}

void FXFlightController::DestroyInstance()
{
    if (s_instance)
    {
        delete s_instance;
        s_instance = nullptr;
    }
}

FXFlightController* FXFlightController::GetInstance()
{
    return s_instance;
}


FXFlightController::FXFlightController(FXFlightControllerConfig& config)
    : m_config(config)
    , m_pidController(nullptr)
{
    assert(!s_instance);
}

void FXFlightController::Init()
{
    m_pidController = new FXFlightPIDController();
}

void FXFlightController::Update(float deltaMs)
{
    m_pidController->Update(deltaMs);
}

void FXFlightController::SetCurrentAngle(FXVector3 vector)
{
}

void FXFlightController::SetCurrentAltitude(float altitude)
{
}
