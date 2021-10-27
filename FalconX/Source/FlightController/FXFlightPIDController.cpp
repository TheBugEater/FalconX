#include "FlightController/FXFlightPIDController.h"
#include "Core/Drivers/BLDC/FXBLDCDriverESP32.h"
#include <cstdio>

void FXFlightPIDController::Init()
{
    FXBLDCDriverConfig config = {};
    config.PinOut = 13;
    m_frontLeft = new FXBLDCDriverESP32(config);
    config.PinOut = 12;
    m_frontRight = new FXBLDCDriverESP32(config);
    config.PinOut = 5;
    m_rearLeft = new FXBLDCDriverESP32(config);
    config.PinOut = 2;
    m_rearRight = new FXBLDCDriverESP32(config);

    m_thrust = 1;
}

void FXFlightPIDController::Update(float deltaMs)
{
    if (m_flightControllerStatus != EFXFlightControllerStatus::Started)
    {
        return;
    }

    if (m_calibrated)
    {
        m_thrust += m_controllerData.Thrust * deltaMs * 0.5f;
        if (m_thrust > 1)
        {
            m_thrust = 1;
        }
        else if (m_thrust < 0)
        {
            m_thrust = 0;
        }

        printf("Thrust: %.2f | Controller Thrust : %.2f\n", m_thrust, m_controllerData.Thrust);
        m_frontLeft->SetSpeed(m_thrust);
        m_frontRight->SetSpeed(m_thrust);
        m_rearLeft->SetSpeed(m_thrust);
        m_rearRight->SetSpeed(m_thrust);
    }
    else
    {
        CalibrateESC(deltaMs);
    }
}

void FXFlightPIDController::CalibrateESC(float deltaMs)
{
    m_thrust -= deltaMs;
    printf("ESC Calibration Pulse : %f\n", m_thrust);
    if (m_thrust <= 0)
    {
        m_thrust = 0;
        m_calibrated = true;
    }

    m_frontLeft->SetSpeed(m_thrust);
    m_frontRight->SetSpeed(m_thrust);
    m_rearLeft->SetSpeed(m_thrust);
    m_rearRight->SetSpeed(m_thrust);
}

void FXFlightPIDController::SetControllerData(FXFlightInputControllerData const& data)
{
    m_controllerData = data;
}

void FXFlightPIDController::SetFlightControllerStatus(EFXFlightControllerStatus const& status)
{
    m_flightControllerStatus = status;
}
