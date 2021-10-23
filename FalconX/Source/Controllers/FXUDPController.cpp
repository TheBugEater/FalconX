#include "Controllers/FXUDPController.h"
#include "Controllers/FXUDPMessages.h"
#include "Engine/FXEngine.h"

FXUDPController::FXUDPController(FXUDPControllerConfig const& config)
    : m_config(config)
    , m_status(EUDPControllerStatus::WaitingForNetwork)
{
}

bool FXUDPController::Init()
{
    return true;
}

void FXUDPController::Update(float deltaMs)
{
    switch (m_status)
    {
    case EUDPControllerStatus::WaitingForNetwork:
        CheckForNetworkStatus();
        break;
    case EUDPControllerStatus::ListeningForBroadcasts:
        ListenBroadcasts();
        break;
    case EUDPControllerStatus::Connected:
        UpdateConnected(deltaMs);
        break;
    case EUDPControllerStatus::ConnectionError:
        break;
    default:
        break;
    }
}

void FXUDPController::CheckForNetworkStatus()
{
    if (FalconXEngine::GetInstance().GetNetworkStatus() != ENetworkStatus::Connected)
    {
        return;
    }

    if (InitSocket(m_config.BroadcastPort))
    {
        m_status = EUDPControllerStatus::ListeningForBroadcasts;
        printf("Listening for Broadcasts!\n");
    }
}

bool FXUDPController::InitSocket(uint16 port)
{
    struct sockaddr_in local_addr = {};

    if ((m_socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
    {
        printf("Failed to Create Socket!\n");
        return false;
    }

    local_addr.sin_family = AF_INET;
    local_addr.sin_port = htons(port);
    local_addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(m_socket, (struct sockaddr*)&local_addr, sizeof(local_addr)) == -1)
    {
        printf("Failed to Bind!\n");
        return false;
    }

    if (fcntl(m_socket, F_SETFL, O_NONBLOCK) == -1)
    {
        printf("Failed to Set Non Blocking!\n");
        return false;
    }

    return true;
}

void FXUDPController::ListenBroadcasts()
{
    socklen_t addrLen = sizeof(m_remoteAddr);
    int recvSize = recvfrom(m_socket, m_workBuffer, c_workBufferSize, 0, (struct sockaddr*)&m_remoteAddr, &addrLen);
    if (recvSize >= (int)sizeof(int))
    {
        FXBinraryStream stream(m_workBuffer,recvSize);
        int magicNumber = 0;
        stream.ReadInt32(magicNumber);
        printf("Received a Message! Magic Number : %d == %d\n", magicNumber, m_config.MagicNumber);
        if (magicNumber == m_config.MagicNumber)
        {
            CloseSocket();
            if (InitSocket(m_config.CommunicationPort))
            {
                printf("Communication Established!\n");
                // Just change the communication port of the address
                m_status = EUDPControllerStatus::Connected;
                m_remoteAddr.sin_port = htons(m_config.CommunicationPort);
            }
            else
            {
                m_status = EUDPControllerStatus::ConnectionError;
            }
        }
    }
    else
    {
        if (errno != EWOULDBLOCK)
        {
            m_status = EUDPControllerStatus::ConnectionError;
        }
    }
}

void FXUDPController::UpdateConnected(float deltaMs)
{
    struct sockaddr_in recvAddr = {};
    socklen_t addrLen = sizeof(recvAddr);

    int recvSize = recvfrom(m_socket, m_workBuffer, c_workBufferSize, 0, (struct sockaddr*)&recvAddr, &addrLen);
    if (recvSize > (int)sizeof(int32))
    {
        FXBinraryStream stream(m_workBuffer, recvSize);
        int32 messageType = 0;
        if (stream.ReadInt32(messageType))
        {
            if (messageType == 1)
            {
                int32 yaw, thrust, roll, pitch;
                stream.ReadInt32(yaw);
                stream.ReadInt32(thrust);
                stream.ReadInt32(roll);
                stream.ReadInt32(pitch);
                printf("Recieved Yaw : %d, Thrust : %d, Pitch : %d, Roll : %d\n", yaw, thrust, pitch, roll);
            }
        }
    }
    else
    {
        if (errno != EWOULDBLOCK)
        {
            m_status = EUDPControllerStatus::ConnectionError;
        }
    }

    m_pingTimer += deltaMs;
    if (m_pingTimer > m_config.PingFrequency)
    {
        m_pingTimer = 0;
        FXUDPPingMessage message;
        message.m_magicNumber = m_config.MagicNumber;
        printf("Sending a Ping!\n");
        SendMessage(&message);
    }
}

void FXUDPController::CloseSocket()
{
    shutdown(m_socket, SHUT_RDWR);
    close(m_socket);
}

bool FXUDPController::SendMessage(IFXUDPMessage* message)
{
    uint8    buffer[c_workBufferSize];
    FXBinraryStream stream(buffer, c_workBufferSize);
    stream.WriteInt32((int32)EUDPMessageTypes::Ping); // Temp
    if (message->Serialize(&stream))
    {
        return (sendto(m_socket, buffer, stream.GetSize(), 0, (struct sockaddr*)&m_remoteAddr, sizeof(m_remoteAddr)) > 0);
    }

    return false;
}
