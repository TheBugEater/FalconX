#pragma once
#include "Core/FXTypes.h"

enum class FXBinraryStreamMode
{
    None,
    Write,
    Read
};

class FXBinraryStream
{
public:
    FXBinraryStream(uint8* buffer, uint32 bufferSize);

    bool        WriteUint8(uint8 value);
    bool        WriteUint16(uint16 value);
    bool        WriteUint32(uint32 value);
    bool        WriteUint64(uint64 value);

    bool        WriteInt8(int8 value);
    bool        WriteInt16(int16 value);
    bool        WriteInt32(int32 value);
    bool        WriteInt64(int64 value);

    bool        ReadUint8(uint8& value);
    bool        ReadUint16(uint16& value);
    bool        ReadUint32(uint32& value);
    bool        ReadUint64(uint64& value);

    bool        ReadInt8(int8& value);
    bool        ReadInt16(int16& value);
    bool        ReadInt32(int32& value);
    bool        ReadInt64(int64& value);

    uint32      GetSize() const { return m_size; }
    uint8*      GetBuffer() const { return m_buffer; }

private:
    uint8*                  m_buffer;
    uint32                  m_capacity;
    uint32                  m_size;
    FXBinraryStreamMode     m_streamMode;
};