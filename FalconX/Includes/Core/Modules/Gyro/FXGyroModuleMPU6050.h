#pragma once
#include "Core/Modules/Gyro/FXGyroModule.h"
#include "Utils/FXVector3.h"

class IFXI2CDriver;

class FXGyroModuleMPU6050 : public FXGyroModule
{
public:
    FXGyroModuleMPU6050();
    virtual bool            Init() override;
    virtual void            Update(float deltaMs) override;

private:
    bool                    ReadSensorGyro(FXVector3& GyroRaw);
    bool                    ReadSensorAll(FXVector3& GyroRaw, FXVector3& AccRaw, float& temp);
    bool                    Calibrate();
    bool                    UpdateAngle();

    IFXI2CDriver*           m_i2cDriver;

    FXVector3               m_gyroOffset;
    FXVector3               m_angles;

    bool                    m_calibrated;
    uint16                  m_calibrateCounter;

    int64                   m_lastSensorReadTime;
    float                   m_timeToPrint;
};
