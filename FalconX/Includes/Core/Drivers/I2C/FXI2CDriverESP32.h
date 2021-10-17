#pragma once
#include "Core/Drivers/I2C/FXI2CDriver.h"
#include "driver/i2c.h"

struct FXI2CDriverESP32Config
{
    EFXI2CMode          m_mode;
    uint32              m_clockSpeed;
    uint16              m_sdaPin;
    uint16              m_sclPin;
    bool                m_enableSdaPullup;
    bool                m_enableSclPullup;
    uint8               m_i2cPort;
};

class FXI2CDriverESP32 : public FXII2CDriver
{
public:
    FXI2CDriverESP32(FXI2CDriverESP32Config& config);
    ~FXI2CDriverESP32();

    virtual void            StartWrite(uint16 deviceAddress, EFXI2CAck i2cAck = EFXI2CAck::Ack) override;
    virtual void            StartRead(uint16 deviceAddress, uint8 readAddress, EFXI2CAck i2cAck = EFXI2CAck::Ack) override;
    virtual void            Write(uint8* data, uint32 dataLength, EFXI2CAck i2cAck = EFXI2CAck::Ack) override;
    virtual void            Write(uint8 data, EFXI2CAck i2cAck = EFXI2CAck::Ack) override;
    virtual void            Read(uint8* data, uint32 dataLength, EFXI2CAck i2cAck = EFXI2CAck::Nack) override;
    virtual void            Read(uint8 data, EFXI2CAck i2cAck = EFXI2CAck::Nack) override;
    virtual EFXI2CReturn    End() override;

private:
    FXI2CDriverESP32Config  m_config;
    i2c_cmd_handle_t        m_command;
    uint32                  m_communicationAddress;
};
