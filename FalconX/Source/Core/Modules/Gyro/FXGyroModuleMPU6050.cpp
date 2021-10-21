#include "Core/Modules/Gyro/FXGyroModuleMPU6050.h"
#include "Core/Drivers/I2C/FXI2CDriverESP32.h"
#include "FlightController/FXFlightController.h"
#include "Utils/FXUtils.h"
#include <cmath> 

#define MPU_ADDRESS                 0x68
#define MPU_READ_GYRO_COMMAND       0x43
#define MPU_READ_ALL_COMMAND        0x3B
#define MPU_POWER_COMMAND           0x6B
#define MPU_GYRO_SENSITIVITY        131.0f
#define MPU_ACC_SENSITIVITY         16384.0f

#define CALIBRATE_TIMES             2000
#define MICROS_IN_SECONDS           1000000.0f

FXGyroModuleMPU6050::FXGyroModuleMPU6050()
    : m_i2cDriver(nullptr)
    , m_calibrated(false)
    , m_calibrateCounter(0)
    , m_lastSensorReadTime(0)
    , m_timeToPrint(0)
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

    m_i2cDriver->StartWrite(MPU_ADDRESS, EFXI2CAck::Ack);
    m_i2cDriver->Write(MPU_POWER_COMMAND, EFXI2CAck::Ack );
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

bool FXGyroModuleMPU6050::ReadSensorGyro(FXVector3& GyroRaw)
{
    uint8 buffer[6] = {};

    m_i2cDriver->StartRead(MPU_ADDRESS, MPU_READ_GYRO_COMMAND, EFXI2CAck::Ack);
    m_i2cDriver->Read(buffer, 6, EFXI2CAck::Nack);

    if (m_i2cDriver->End() == EFXI2CReturn::Success)
    {
        int16 GyroX = buffer[0] << 8 | buffer[1];
        int16 GyroY = buffer[2] << 8 | buffer[3];
        int16 GyroZ = buffer[4] << 8 | buffer[5];

        GyroRaw = FXVector3(GyroX, GyroY, GyroZ);

        return true;
    }

    return false;
}

bool FXGyroModuleMPU6050::ReadSensorAll(FXVector3& GyroRaw, FXVector3& AccRaw, float& temperature)
{
    uint8 buffer[14] = {};

    m_i2cDriver->StartRead(MPU_ADDRESS, MPU_READ_ALL_COMMAND, EFXI2CAck::Ack);
    m_i2cDriver->Read(buffer, 14, EFXI2CAck::Nack);

    if (m_i2cDriver->End() == EFXI2CReturn::Success)
    {
        int16 AccX = buffer[0] << 8 | buffer[1];
        int16 AccY = buffer[2] << 8 | buffer[3];
        int16 AccZ = buffer[4] << 8 | buffer[5];

        int16 temp = buffer[6] << 8 | buffer[7];

        int16 GyroX = buffer[8] << 8 | buffer[9];
        int16 GyroY = buffer[10] << 8 | buffer[11];
        int16 GyroZ = buffer[12] << 8 | buffer[13];

        AccRaw = FXVector3(AccX, AccY, AccZ);
        GyroRaw = FXVector3(GyroX, GyroY, GyroZ);
        temperature = temp;

        return true;
    }

    return false;
}

bool FXGyroModuleMPU6050::Calibrate()
{
    FXVector3 gyroRaw, accRaw;
    float temperature;
    if (ReadSensorAll(gyroRaw, accRaw, temperature))
    {
        m_gyroOffset += gyroRaw;

        m_calibrateCounter++;
        if (m_calibrateCounter == CALIBRATE_TIMES)
        {
            // Get the average offset
            m_gyroOffset /= m_calibrateCounter;

            printf("Calculated Gyro Offsets : X : %f, Y : %f, Z : %f\n", m_gyroOffset.X, m_gyroOffset.Y, m_gyroOffset.Z);

            m_lastSensorReadTime = FX_GetMicros();

            m_angles = FXVector3();
            m_calibrated = true;
        }
        return true;
    }

    return false;
}

bool FXGyroModuleMPU6050::UpdateAngle()
{
    FXVector3 gyroRaw, accRaw;
    float temperature;

    auto currentTime = FX_GetMicros();
    if (ReadSensorAll(gyroRaw, accRaw, temperature))
    {
        FXVector3 gyroAngles = ((gyroRaw - m_gyroOffset) / MPU_GYRO_SENSITIVITY)  * ((currentTime - m_lastSensorReadTime) / MICROS_IN_SECONDS);
        FXVector3 accValues = accRaw / MPU_ACC_SENSITIVITY;

        double pitch = atan2(accValues.Y, sqrt(accValues.Z * accValues.Z + accValues.X * accValues.X)) * (180 / M_PI);
        double roll = atan2(accValues.X, sqrt(accValues.Z * accValues.Z + accValues.Y * accValues.Y)) * -(180 / M_PI);

        m_angles.X = (0.98f * (m_angles.X + gyroAngles.X)) + (0.02f * pitch);
        m_angles.Y = (0.98f * (m_angles.Y + gyroAngles.Y)) + (0.02f * roll);
        m_angles.Z += gyroAngles.Z;

        // Update Flight Controller's Angle
        FXFlightController::GetInstance()->SetCurrentAngle(m_angles);

        m_lastSensorReadTime = currentTime;

        if (m_timeToPrint < currentTime)
        {
            m_timeToPrint = currentTime + MICROS_IN_SECONDS;

            printf("G | Roll : %f | Pitch : %f | Yaw : %f\n", m_angles.Y, m_angles.X, m_angles.Z);
        }

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
        UpdateAngle();
    }
}