#pragma once
#include "Core/FXTypes.h"
#include "Utils/FXVector3.h"

class FXEngine;
class FXFlightPIDController;

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

    static  FXFlightController* CreateInstance(FXFlightControllerConfig& config);
    static  void                DestroyInstance();
    static  FXFlightController* GetInstance();

private:
    static FXFlightController*  s_instance;

    FXFlightControllerConfig    m_config;
    FXFlightPIDController*      m_pidController;
};