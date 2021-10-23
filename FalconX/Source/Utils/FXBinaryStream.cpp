#include "Utils/FXBinaryStream.h"

FXBinraryStream::FXBinraryStream(uint8* buffer, uint32 bufferSize)
    : m_buffer(buffer)
    , m_capacity(bufferSize)
    , m_size(0)
    , m_streamMode(FXBinraryStreamMode::None)
{
}

bool FXBinraryStream::WriteUint8(uint8 value)
{
    if (m_streamMode == FXBinraryStreamMode::Read)
    {
        m_size = 0;
    }

    if (m_size + sizeof(uint8) > m_capacity)
    {
        return false;
    }

    *(int8*)(m_buffer + m_size) = value;
    m_size += sizeof(uint8);

    m_streamMode = FXBinraryStreamMode::Write;

    return true;
}

bool FXBinraryStream::WriteUint16(uint16 value)
{
    if (m_streamMode == FXBinraryStreamMode::Read)
    {
        m_size = 0;
    }

    if (m_size + sizeof(uint16) > m_capacity)
    {
        return false;
    }

    *(uint16*)(m_buffer + m_size) = value;
    m_size += sizeof(uint16);
    m_streamMode = FXBinraryStreamMode::Write;
    return true;
}

bool FXBinraryStream::WriteUint32(uint32 value)
{
    if (m_streamMode == FXBinraryStreamMode::Read)
    {
        m_size = 0;
    }

    if (m_size + sizeof(uint32) > m_capacity)
    {
        return false;
    }

    *(uint32*)(m_buffer + m_size) = value;
    m_size += sizeof(uint32);
    m_streamMode = FXBinraryStreamMode::Write;
    return true;
}

bool FXBinraryStream::WriteUint64(uint64 value)
{
    if (m_streamMode == FXBinraryStreamMode::Read)
    {
        m_size = 0;
    }

    if (m_size + sizeof(uint64) > m_capacity)
    {
        return false;
    }

    *(uint64*)(m_buffer + m_size) = value;
    m_size += sizeof(uint64);
    m_streamMode = FXBinraryStreamMode::Write;
    return true;
}

bool FXBinraryStream::WriteInt8(int8 value)
{
    if (m_streamMode == FXBinraryStreamMode::Read)
    {
        m_size = 0;
    }

    if (m_size + sizeof(int8) > m_capacity)
    {
        return false;
    }

    *(int8*)(m_buffer + m_size) = value;
    m_size += sizeof(int8);
    m_streamMode = FXBinraryStreamMode::Write;
    return true;
}

bool FXBinraryStream::WriteInt16(int16 value)
{
    if (m_streamMode == FXBinraryStreamMode::Read)
    {
        m_size = 0;
    }

    if (m_size + sizeof(int16) > m_capacity)
    {
        return false;
    }

    *(int16*)(m_buffer + m_size) = value;
    m_size += sizeof(int16);
    m_streamMode = FXBinraryStreamMode::Write;
    return true;
}

bool FXBinraryStream::WriteInt32(int32 value)
{
    if (m_streamMode == FXBinraryStreamMode::Read)
    {
        m_size = 0;
    }

    if (m_size + sizeof(int32) > m_capacity)
    {
        return false;
    }

    *(int32*)(m_buffer + m_size) = value;
    m_size += sizeof(int32);
    m_streamMode = FXBinraryStreamMode::Write;
    return true;
}

bool FXBinraryStream::WriteInt64(int64 value)
{
    if (m_streamMode == FXBinraryStreamMode::Read)
    {
        m_size = 0;
    }

    if (m_size + sizeof(int64) > m_capacity)
    {
        return false;
    }

    *(int64*)(m_buffer + m_size) = value;
    m_size += sizeof(int64);
    m_streamMode = FXBinraryStreamMode::Write;
    return true;
}

bool FXBinraryStream::ReadUint8(uint8& value)
{
    if (m_streamMode == FXBinraryStreamMode::Write)
    {
        m_size = 0;
    }

    if (m_size + sizeof(uint8) > m_capacity)
    {
        return false;
    }

    value = *(uint8*)(m_buffer + m_size);
    m_size += sizeof(uint8);
    m_streamMode = FXBinraryStreamMode::Read;
    return true;
}

bool FXBinraryStream::ReadUint16(uint16& value)
{
    if (m_streamMode == FXBinraryStreamMode::Write)
    {
        m_size = 0;
    }

    if (m_size + sizeof(uint16) > m_capacity)
    {
        return false;
    }

    value = *(uint16*)(m_buffer + m_size);
    m_size += sizeof(uint16);
    m_streamMode = FXBinraryStreamMode::Read;
    return true;
}

bool FXBinraryStream::ReadUint32(uint32& value)
{
    if (m_streamMode == FXBinraryStreamMode::Write)
    {
        m_size = 0;
    }

    if (m_size + sizeof(uint32) > m_capacity)
    {
        return false;
    }

    value = *(uint32*)(m_buffer + m_size);
    m_size += sizeof(uint32);
    m_streamMode = FXBinraryStreamMode::Read;
    return true;
}

bool FXBinraryStream::ReadUint64(uint64& value)
{
    if (m_streamMode == FXBinraryStreamMode::Write)
    {
        m_size = 0;
    }

    if (m_size + sizeof(uint64) > m_capacity)
    {
        return false;
    }

    value = *(uint64*)(m_buffer + m_size);
    m_size += sizeof(uint64);
    m_streamMode = FXBinraryStreamMode::Read;
    return true;
}

bool FXBinraryStream::ReadInt8(int8& value)
{
    if (m_streamMode == FXBinraryStreamMode::Write)
    {
        m_size = 0;
    }

    if (m_size + sizeof(int8) > m_capacity)
    {
        return false;
    }

    value = *(int8*)(m_buffer + m_size);
    m_size += sizeof(int8);
    m_streamMode = FXBinraryStreamMode::Read;
    return true;
}

bool FXBinraryStream::ReadInt16(int16& value)
{
    if (m_streamMode == FXBinraryStreamMode::Write)
    {
        m_size = 0;
    }

    if (m_size + sizeof(int16) > m_capacity)
    {
        return false;
    }

    value = *(int16*)(m_buffer + m_size);
    m_size += sizeof(int16);
    m_streamMode = FXBinraryStreamMode::Read;
    return true;
}

bool FXBinraryStream::ReadInt32(int32& value)
{
    if (m_streamMode == FXBinraryStreamMode::Write)
    {
        m_size = 0;
    }

    if (m_size + sizeof(int32) > m_capacity)
    {
        return false;
    }

    value = *(int32*)(m_buffer + m_size);
    m_size += sizeof(int32);
    m_streamMode = FXBinraryStreamMode::Read;
    return true;
}

bool FXBinraryStream::ReadInt64(int64& value)
{
    if (m_streamMode == FXBinraryStreamMode::Write)
    {
        m_size = 0;
    }

    if (m_size + sizeof(int64) > m_capacity)
    {
        return false;
    }

    value = *(int64*)(m_buffer + m_size);
    m_size += sizeof(int64);
    m_streamMode = FXBinraryStreamMode::Read;
    return true;
}
