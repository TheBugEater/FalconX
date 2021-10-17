#pragma once
#include "Core/FXTypes.h"
#include "Utils/FXVector3.h"

class FXEngine;

struct FXFlightControllerConfig
{
    // PWM Signal Pinouts
    uint8           FrontLeftPin;
    uint8           FrontRightPin;
    uint8           BackLeftPin;
    uint8           BackRightPin;
};

class FXBLDCDriverESP32;

class FXFlightController
{
public:
    FXFlightController(FXFlightControllerConfig& config);

    void                        Init();
    void                        Update(float deltaMs);
    void                        SetCurrentAngle(FXVector3 vector);
    void                        SetCurrentAltitude(float altitude);

private:

    FXFlightControllerConfig    m_config;
    float                       m_frontLeftMotorSpeed;
    float                       m_frontRightMotorSpeed;
    float                       m_backLeftMotorSpeed;
    float                       m_backRightMotorSpeed;

    FXBLDCDriverESP32*          m_frontLeftDriver;
    FXBLDCDriverESP32*          m_frontRightDriver;
    FXBLDCDriverESP32*          m_backLeftDriver;
    FXBLDCDriverESP32*          m_backRightDriver;

    FXVector3                   m_currentAngle;
    float                       m_currentAltitude;
};