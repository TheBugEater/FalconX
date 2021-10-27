#pragma once
#include "Core/FXTypes.h"

class FXBLDCDriver;

class FXFlightPIDController
{
public:
    void                            Init();
    void                            Update(float deltaMs);

    void                            SetControllerData(FXFlightInputControllerData const& data);
    void                            SetFlightControllerStatus(EFXFlightControllerStatus const& status);

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

    FXFlightInputControllerData     m_controllerData;
    EFXFlightControllerStatus       m_flightControllerStatus;
};