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
    FXUDPPingMessage() : m_currentMicros(0) {}

    bool                Serialize(FXBinraryStream* stream) override
    {
        return stream->WriteUint64(m_currentMicros);
    }

    bool                Deserialize(FXBinraryStream* stream) override
    {
        return stream->ReadUint64(m_currentMicros);
    }

    uint64              m_currentMicros;
};