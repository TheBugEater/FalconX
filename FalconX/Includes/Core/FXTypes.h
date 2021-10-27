#pragma once
#define FALCONX_ESP_IDF

using uint8     = unsigned char;
using uint16    = unsigned short;
using uint32    = unsigned int;
using uint64    = unsigned long long;

using int8      = char;
using int16     = short;
using int32     = int;
using int64     = long long;

constexpr uint16    FX_MAX_MODULES = 3;

enum class ENetworkStatus
{
    None,
    Connected,
    Error
};

enum class EFXFlightControllerStatus
{
    Idle,
    Started,
    Stopped
};

struct FXFlightInputControllerData
{
    FXFlightInputControllerData()
        : Thrust(0)
        , Yaw(0)
        , Pitch(0)
        , Roll(0)
    {
    }

    FXFlightInputControllerData(float thrust, float yaw, float pitch, float roll)
        : Thrust(thrust)
        , Yaw(yaw)
        , Pitch(pitch)
        , Roll(roll)
    {
    }

    float           Thrust;
    float           Yaw;
    float           Pitch;
    float           Roll;
};
