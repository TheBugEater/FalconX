#pragma once

class FXBLDCDriver;

class FXFlightPIDController
{
public:
    void                    Init();
    void                    Update(float deltaMs);

private:
    void                    CalibrateESC(float deltaMs);

    FXBLDCDriver*           m_frontLeft;
    FXBLDCDriver*           m_frontRight;
    FXBLDCDriver*           m_rearLeft;
    FXBLDCDriver*           m_rearRight;

    bool                    m_calibrated;
    float                   m_currentThrust;
};