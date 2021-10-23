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