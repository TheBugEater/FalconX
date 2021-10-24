#pragma once
#include "Utils/FXBinaryStream.h"

enum class EUDPMessageTypes : uint8
{
    Ping,
    ControllerInput
};

class IFXUDPMessage
{
public:
    virtual bool        Serialize(FXBinraryStream* stream)      = 0;
    virtual bool        Deserialize(FXBinraryStream* stream)    = 0;
};

class FXUDPPingMessage : public IFXUDPMessage
{
public:
    FXUDPPingMessage() : m_magicNumber(0) {}

    bool                Serialize(FXBinraryStream* stream) override
    {
        return stream->WriteUint32(m_magicNumber);
    }

    bool                Deserialize(FXBinraryStream* stream) override
    {
        return stream->ReadUint32(m_magicNumber);
    }

    uint32              m_magicNumber;
};

class FXUDPControllerInputMessage : public IFXUDPMessage
{
public:
    FXUDPControllerInputMessage() : m_yaw(0), m_thrust(0), m_roll(0), m_pitch(0) {}

    bool                Serialize(FXBinraryStream* stream) override
    {
        bool res = stream->WriteInt32(m_yaw);
        res &= stream->WriteInt32(m_thrust);
        res &= stream->WriteInt32(m_roll);
        res &= stream->WriteInt32(m_pitch);

        return res;
    }

    bool                Deserialize(FXBinraryStream* stream) override
    {
        bool res = stream->ReadInt32(m_yaw);
        res &= stream->ReadInt32(m_thrust);
        res &= stream->ReadInt32(m_roll);
        res &= stream->ReadInt32(m_pitch);

        return res;
    }

    int32              m_yaw;
    int32              m_thrust;
    int32              m_roll;
    int32              m_pitch;
};