#include "Controllers/FXUDPController.h"

FXUDPController::FXUDPController()
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
        UpdateConnected();
        break;
    case EUDPControllerStatus::ConnectionError:
        break;
    default:
        break;
    }
}

void FXUDPController::CheckForNetworkStatus()
{
}

bool FXUDPController::InitSocket(uint16 port)
{
    struct sockaddr_in local_addr = {};

    if ((m_broadcastSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
    {
        return false;
    }

    local_addr.sin_family = AF_INET;
    local_addr.sin_port = htons(port);
    local_addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(m_broadcastSocket, (struct sockaddr*)&local_addr, sizeof(local_addr)) == -1)
    {

        return false;
    }

    if (fcntl(m_broadcastSocket, F_SETFL, O_NONBLOCK) == -1)
    {
        return false;
    }

    return true;
}

void FXUDPController::ListenBroadcasts()
{
}

void FXUDPController::UpdateConnected()
{

}