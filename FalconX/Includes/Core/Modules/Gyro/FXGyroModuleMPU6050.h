#pragma once
#include "Core/Modules/Gyro/FXGyroModule.h"
#include "Utils/FXVector3.h"

class FXII2CDriver;

class FXGyroModuleMPU6050 : public FXGyroModule
{
public:
    FXGyroModuleMPU6050();
    virtual bool            Init() override;
    virtual void            Update(float deltaMs) override;

private:
    bool                    Calibrate();
    bool                    GetAngle(FXVector3& vector, FXVector3 offset, float deltaMs);
    FXII2CDriver*           m_i2cDriver;

    FXVector3               m_offset;
    FXVector3               m_angles;
    bool                    m_calibrated;
    uint16                  m_calibrateCounter;
};
