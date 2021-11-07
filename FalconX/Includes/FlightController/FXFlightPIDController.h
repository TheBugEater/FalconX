#pragma once
#include "Core/FXTypes.h"
#include "Utils/FXVector3.h"

class FXBLDCDriver;

class FXFlightPIDController
{
public:
    void                            Init();
    void                            Update(float deltaMs);

    void                            SetCurrentAngle(FXVector3 const& angle);
    void                            SetControllerData(FXFlightInputControllerData const& data);
    void                            SetFlightControllerStatus(EFXFlightControllerStatus const& status);

    void                            Calculate(float dt);

private:
    void                            CalibrateESC(float deltaMs);

    FXBLDCDriver*                   m_frontLeft;
    FXBLDCDriver*                   m_frontRight;
    FXBLDCDriver*                   m_rearLeft;
    FXBLDCDriver*                   m_rearRight;

    bool                            m_calibrated;

    float                           m_thrust;
    float                           m_yaw;
    float                           m_pitch;
    float                           m_roll;

    FXVector3                       m_droneAngle;

    // PID Variables
    float                           m_pitchIntegral;
    float                           m_pitchLastError;
    float                           m_rollIntegral;
    float                           m_rollLastError;

    FXFlightInputControllerData     m_controllerData;
    EFXFlightControllerStatus       m_flightControllerStatus;
};