#include "Core/Modules/Gyro/FXGyroModuleMPU6050.h"
#include "Core/Drivers/I2C/FXI2CDriverESP32.h"

FXGyroModuleMPU6050::FXGyroModuleMPU6050()
    : m_i2cDriver(nullptr)
    , m_calibrated(false)
    , m_calibrateCounter(0)
{
}

bool FXGyroModuleMPU6050::Init()
{
    FXI2CDriverESP32Config config = {};
    config.m_clockSpeed = 400000;
    config.m_i2cPort = 0;
    config.m_mode = EFXI2CMode::Master;
    config.m_sdaPin = 21;
    config.m_sclPin = 22;
    config.m_enableSclPullup = true;
    config.m_enableSdaPullup = true;

    m_i2cDriver = new FXI2CDriverESP32(config);

    m_i2cDriver->StartWrite(0x68, EFXI2CAck::Ack);
    m_i2cDriver->Write(0x6B, EFXI2CAck::Ack );
    m_i2cDriver->Write(0x00, EFXI2CAck::Ack);
    if (m_i2cDriver->End() == EFXI2CReturn::Success)
    {
        printf("Connected to Gyro via I2C Successfully!\n");
        return true;
    }
    else
    {
        printf("Failed to Connect to Gyro\n");
        return false;
    }
}

bool FXGyroModuleMPU6050::Calibrate()
{
    uint8 buffer[6] = {};

    m_i2cDriver->StartRead(0x68, 0x43, EFXI2CAck::Ack);
    m_i2cDriver->Read(buffer, 6, EFXI2CAck::Nack);

    if (m_i2cDriver->End() == EFXI2CReturn::Success)
    {
        int16 GyroX = buffer[0] << 8 | buffer[1];
        int16 GyroY = buffer[2] << 8 | buffer[3];
        int16 GyroZ = buffer[4] << 8 | buffer[5];

        m_offset += FXVector3(GyroX, GyroY, GyroZ);

        m_calibrateCounter++;
        if (m_calibrateCounter == 1000)
        {
            m_offset /= m_calibrateCounter;

            m_angles = FXVector3();
            m_calibrated = true;
        }
        return true;
    }

    return false;
}

bool FXGyroModuleMPU6050::GetAngle(FXVector3& vector, FXVector3 offset, float deltaMs)
{
    uint8 buffer[6] = {};

    m_i2cDriver->StartRead(0x68, 0x43, EFXI2CAck::Ack);
    m_i2cDriver->Read(buffer, 6, EFXI2CAck::Nack);

    if (m_i2cDriver->End() == EFXI2CReturn::Success)
    {
        int16 GyroX = buffer[0] << 8 | buffer[1];
        int16 GyroY = buffer[2] << 8 | buffer[3];
        int16 GyroZ = buffer[4] << 8 | buffer[5];

        vector.X = ((GyroX - offset.X)/131) * (deltaMs / 1000);
        vector.Y = ((GyroY - offset.Y)/131) * (deltaMs / 1000);
        vector.Z = ((GyroZ - offset.Z)/131) * (deltaMs / 1000);
        return true;
    }

    return false;
}

void FXGyroModuleMPU6050::Update(float deltaMs)
{
    FXVector3 vector;
    if (!m_calibrated)
    {
        Calibrate();
    }
    else
    {
        if (GetAngle(vector, m_offset, deltaMs))
        {
            m_angles += vector;
            printf("Angle X: %f Y : %f Z: %f\n", m_angles.X, m_angles.Y, m_angles.Z);
        }
    }
}