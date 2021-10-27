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

class FXFlightController
{
public:
    FXFlightController(FXFlightControllerConfig const& config);

    void                        Init();
    void                        Update(float deltaMs);
    void                        SetCurrentAngle(FXVector3 vector);
    void                        SetCurrentAltitude(float altitude);
    void                        SetControllerData(FXFlightInputControllerData const& data);
    void                        SetFlightControllerStatus(EFXFlightControllerStatus const& status);

    static  FXFlightController* CreateInstance(FXFlightControllerConfig const& config);
    static  void                DestroyInstance();
    static  FXFlightController* GetInstance();

private:
    static FXFlightController*  s_instance;

    FXFlightControllerConfig    m_config;
    FXFlightPIDController*      m_pidController;
    EFXFlightControllerStatus   m_flightControllerStatus;
};