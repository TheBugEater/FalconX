#include "FlightController/FXFlightPIDController.h"
#include "Core/Drivers/BLDC/FXBLDCDriverESP32.h"
#include <cstdio>
#include "Utils/FXUtils.h"

// Angle Formula
// Front Left  = -Pitch - Roll
// Front Right = -Pitch + Roll
// Rear Left   = Pitch - Roll
// Rear Right  = Pitch + Roll

const float c_propotionalGain = 5.0f;
const float c_integralGain = 0.001f;
const float c_derivativeGain = 0.007f;
const float c_maxAngularCorrection = 300.0f;
const float c_maxSpeed = 1000.0f;

void FXFlightPIDController::Init()
{
    m_pitchIntegral = 0;
    m_pitchLastError = 0;

    FXBLDCDriverConfig config = {};
    config.PinOut = 12;
    m_frontLeft = new FXBLDCDriverESP32(config);
    config.PinOut = 14;
    m_frontRight = new FXBLDCDriverESP32(config);
    config.PinOut = 27;
    m_rearLeft = new FXBLDCDriverESP32(config);
    config.PinOut = 26;
    m_rearRight = new FXBLDCDriverESP32(config);

    m_thrust = 1;
}

void FXFlightPIDController::Update(float deltaMs)
{
    if (m_flightControllerStatus != EFXFlightControllerStatus::Started)
    {
        return;
    }

    if (m_calibrated)
    {
        m_thrust += m_controllerData.Thrust * deltaMs * 0.5f;
        if (m_thrust > ((c_maxSpeed - c_maxAngularCorrection)/c_maxSpeed))
        {
            m_thrust = (c_maxSpeed - c_maxAngularCorrection)/c_maxSpeed;
        }
        else if (m_thrust < 0)
        {
            m_thrust = 0;
        }

        Calculate(deltaMs);
    }
    else
    {
        CalibrateESC(deltaMs);
    }
}

void FXFlightPIDController::SetCurrentAngle(FXVector3 const& angle)
{
    m_droneAngle = angle;
}

void FXFlightPIDController::CalibrateESC(float deltaMs)
{
    m_thrust -= deltaMs;
    printf("ESC Calibration Pulse : %f\n", m_thrust);
    if (m_thrust <= 0)
    {
        m_thrust = 0;
        m_calibrated = true;
    }

    m_frontLeft->SetSpeed(m_thrust);
    m_frontRight->SetSpeed(m_thrust);
    m_rearLeft->SetSpeed(m_thrust);
    m_rearRight->SetSpeed(m_thrust);
}

void FXFlightPIDController::SetControllerData(FXFlightInputControllerData const& data)
{
    m_controllerData = data;
}

void FXFlightPIDController::SetFlightControllerStatus(EFXFlightControllerStatus const& status)
{
    m_flightControllerStatus = status;
}

// PID Calculations
void FXFlightPIDController::Calculate(float dt)
{
    // Motor Speed Range = 0 - 1000 ( Later converted to 0 to 1 )
    // Pid Values should be only 300 max to allow 700 for the Thrust

    // This is to match up with Controller's Angular Change
    float dronePitchAngularVelocity = m_droneAngle.X / dt;
    float droneRollAngularVelocity = m_droneAngle.Y / dt;

    float pitchError = dronePitchAngularVelocity - 0;

    float pitch_Kp = c_propotionalGain * pitchError * dt;   // Kp * e(dt)
    m_pitchIntegral += pitchError * dt;
    float pitch_Ki = m_pitchIntegral * c_integralGain;      // Ki * _/` e(t)dt
    float pitch_Kd = c_derivativeGain * (pitchError - m_pitchLastError) / dt;  // Kd * de(t)/dt
    m_pitchLastError = pitchError;
    float pitchOutput = pitch_Kp + pitch_Ki + pitch_Kd;

    // Clamp
    pitchOutput = FX_Clamp(pitchOutput, -c_maxAngularCorrection, c_maxAngularCorrection);

    // printf("Pitch : Error : %f, Kp : %f, Ki : %f, Kd : %f, Delta : %f - Output: %f\n", pitchError, pitch_Kp, pitch_Ki, pitch_Kd, dt, pitchOutput);

    float rollError = droneRollAngularVelocity - 0;

    float roll_Kp = c_propotionalGain * rollError * dt;   // Kp * e(dt)
    m_rollIntegral += rollError * dt;
    float roll_Ki = m_rollIntegral * c_integralGain;      // Ki * _/` e(t)dt
    float roll_Kd = c_derivativeGain * (rollError - m_rollLastError) / dt;  // Kd * de(t)/dt
    m_rollLastError = rollError;
    float rollOutput = roll_Kp + roll_Ki + roll_Kd;

    // Clamp
    rollOutput = FX_Clamp(rollOutput, -c_maxAngularCorrection, c_maxAngularCorrection);
    // printf("Roll : Error : %f, Kp : %f, Ki : %f, Kd : %f, Delta : %f - Output: %f\n", rollError, roll_Kp, roll_Ki, roll_Kd, dt, rollOutput);

    float frontLeftSpeed = (-pitchOutput - rollOutput);
    float frontRightSpeed = (-pitchOutput + rollOutput);
    float rearLeftSpeed = (pitchOutput - rollOutput);
    float rearRightSpeed = (pitchOutput + rollOutput);

    float thrustFactor = m_thrust * c_maxSpeed;
    thrustFactor = FX_Clamp(thrustFactor, 0.0f, c_maxSpeed - c_maxAngularCorrection);
    frontLeftSpeed = FX_Clamp(thrustFactor + frontLeftSpeed, 0.0f, c_maxSpeed);
    frontRightSpeed = FX_Clamp(thrustFactor + frontRightSpeed, 0.0f, c_maxSpeed);
    rearLeftSpeed = FX_Clamp(thrustFactor + rearLeftSpeed, 0.0f, c_maxSpeed);
    rearRightSpeed = FX_Clamp(thrustFactor + rearRightSpeed, 0.0f, c_maxSpeed);

    m_frontLeft->SetSpeed(frontLeftSpeed / c_maxSpeed);
    m_frontRight->SetSpeed(frontRightSpeed / c_maxSpeed);
    m_rearLeft->SetSpeed(rearLeftSpeed / c_maxSpeed);
    m_rearRight->SetSpeed(rearRightSpeed / c_maxSpeed);

    printf("FL : %f , FR : %f , RL : %f , RR : %f\n",frontLeftSpeed, frontRightSpeed, rearLeftSpeed, rearRightSpeed);
}
