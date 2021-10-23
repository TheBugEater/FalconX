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

    m_currentThrust = 1;
}

void FXFlightPIDController::Update(float deltaMs)
{
    if (!m_calibrated)
    {
        CalibrateESC(deltaMs);
    }
}

void FXFlightPIDController::CalibrateESC(float deltaMs)
{
    m_currentThrust -= deltaMs;
    printf("ESC Calibration Pulse : %f\n", m_currentThrust);
    if (m_currentThrust <= 0)
    {
        m_currentThrust = 0;
        m_calibrated = true;
    }

    m_frontLeft->SetSpeed(m_currentThrust);
    m_frontRight->SetSpeed(m_currentThrust);
    m_rearLeft->SetSpeed(m_currentThrust);
    m_rearRight->SetSpeed(m_currentThrust);
}
