#pragma once
#include "Core/Drivers/FXDriver.h"
#include "Core/FXTypes.h"

enum class EFXI2CMode
{
    Master,
    Slave
};

enum class EFXI2CReturn
{
    Success,
    Failed,
    Timeout
};

enum class EFXI2CAck
{
    None,
    Ack,
    Nack
};

class IFXI2CDriver : public IFXDriver
{
public:
    IFXI2CDriver()          {};
    virtual ~IFXI2CDriver() {};

    virtual void            StartWrite(uint16 deviceAddress, EFXI2CAck i2cAck = EFXI2CAck::Ack)                     = 0;
    virtual void            StartRead(uint16 deviceAddress, uint8 readAddress, EFXI2CAck i2cAck = EFXI2CAck::Ack)   = 0;
    virtual void            Write(uint8* data, uint32 dataLength, EFXI2CAck i2cAck = EFXI2CAck::Ack)                = 0;
    virtual void            Write(uint8 data, EFXI2CAck i2cAck = EFXI2CAck::Ack)                                    = 0;
    virtual void            Read(uint8* data, uint32 dataLength, EFXI2CAck i2cAck = EFXI2CAck::Nack)                = 0;
    virtual void            Read(uint8 data, EFXI2CAck i2cAck = EFXI2CAck::Nack)                                    = 0;
    virtual EFXI2CReturn    End()                                                                                   = 0;
};
