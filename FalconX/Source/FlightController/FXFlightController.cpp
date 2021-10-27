#include "FlightController/FXFlightController.h"
#include "FlightController/FXFlightPIDController.h"
#include <assert.h>

FXFlightController* FXFlightController::s_instance = nullptr;

FXFlightController* FXFlightController::CreateInstance(FXFlightControllerConfig const& config)
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


FXFlightController::FXFlightController(FXFlightControllerConfig const& config)
    : m_config(config)
    , m_pidController(nullptr)
    , m_flightControllerStatus(EFXFlightControllerStatus::Idle)
{
    assert(!s_instance);
}

void FXFlightController::Init()
{
    m_pidController = new FXFlightPIDController();
    m_pidController->Init();
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

void FXFlightController::SetControllerData(FXFlightInputControllerData const& data)
{
    m_pidController->SetControllerData(data);
}

void FXFlightController::SetFlightControllerStatus(EFXFlightControllerStatus const& status)
{
    m_flightControllerStatus = status;
    m_pidController->SetFlightControllerStatus(status);
}
