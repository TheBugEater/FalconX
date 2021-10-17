#include "FlightController/FXFlightController.h"
#include "Core/Drivers/BLDC/FXBLDCDriverESP32.h"

FXFlightController::FXFlightController(FXFlightControllerConfig& config)
    : m_config(config)
{
}

void FXFlightController::Init()
{
    FXBLDCDriverConfig config = {};
    config.MaxPulseWidth = 1023;
    config.MinPulseWidth = 0;
    config.PinOut = 13;
    m_frontLeftDriver = new FXBLDCDriverESP32(config);
    config.PinOut = 12;
    m_frontRightDriver = new FXBLDCDriverESP32(config);
    config.PinOut = 5;
    m_backLeftDriver = new FXBLDCDriverESP32(config);
    config.PinOut = 2;
    m_backRightDriver = new FXBLDCDriverESP32(config);

    m_frontLeftDriver->SetPulseWidth(0);
    m_frontRightDriver->SetPulseWidth(0);
    m_backLeftDriver->SetPulseWidth(0);
    m_backRightDriver->SetPulseWidth(0);
}

void FXFlightController::Update(float deltaMs)
{
    static float counter = 0;
    static float direction = 1;
    counter += (deltaMs *direction * 10);

    if (counter > 1023)
    {
        direction = -1;
    }
    else if (counter < 0)
    {
        direction = 1;
    }
    counter = 1023;

    m_frontLeftDriver->SetPulseWidth((uint32)counter);
    m_frontRightDriver->SetPulseWidth((uint32)counter);
    m_backLeftDriver->SetPulseWidth((uint32)counter);
    m_backRightDriver->SetPulseWidth((uint32)counter);
}

void FXFlightController::SetCurrentAngle(FXVector3 vector)
{
    m_currentAngle = vector;
}

void FXFlightController::SetCurrentAltitude(float altitude)
{
    m_currentAltitude = altitude;
}
