#include "Controllers/FXInputController.h"
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

class FXUDPController : public IFXInputController
{
public:
    FXUDPController();
    virtual bool            Init() override;
    virtual void            Update(float deltaMs) override;

private:
    void                    CheckForNetworkStatus();
    bool                    InitSocket(uint16 port);
    void                    ListenBroadcasts();
    void                    UpdateConnected();

    struct sockaddr_in      m_remoteAddr;
    int                     m_broadcastSocket;
    EUDPControllerStatus    m_status;
};