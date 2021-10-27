#include "Controllers/FXInputController.h"
#include "Controllers/FXUDPMessages.h"
#include "Core/FXTypes.h"

#ifdef FALCONX_ESP_IDF
#include "lwip/sockets.h"
#include "lwip/sys.h"
#endif

enum class EUDPControllerStatus
{
    WaitingForNetwork,
    ListeningForBroadcasts,
    Connected,
    ConnectionError
};

struct FXUDPControllerConfig
{
    uint16              BroadcastPort;
    uint16              CommunicationPort;
    uint32              MagicNumber;
    float               PingFrequency;
};

class FXUDPController : public IFXInputController
{
public:
    FXUDPController(FXUDPControllerConfig const& config);
    virtual bool            Init() override;
    virtual void            Update(float deltaMs) override;

private:
    void                    CheckForNetworkStatus();
    bool                    InitSocket(uint16 port);
    void                    ListenBroadcasts();
    void                    UpdateConnected(float dt);
    void                    CloseSocket();

    void                    HandleControllerInputMessage(FXBinraryStream& stream);
    void                    HandleFlightStatusMessage(FXBinraryStream& stream);
    bool                    SendMessage(IFXUDPMessage*  message);

    FXUDPControllerConfig   m_config;
    struct sockaddr_in      m_remoteAddr;
    int                     m_socket;
    EUDPControllerStatus    m_status;

    float                   m_pingTimer;
    static const uint16     c_workBufferSize = 1024;
    uint8                   m_workBuffer[c_workBufferSize];
};