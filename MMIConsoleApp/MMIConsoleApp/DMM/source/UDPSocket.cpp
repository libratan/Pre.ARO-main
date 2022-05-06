#include <WinSock2.h>
#include <string.h>
#include <../DMM/header/Network.h>
#include "WS2tcpip.h"
#include <../MSG/header/Deserializer.h>

using namespace std;
using namespace Network;


// Public Functions

// This function binds the UDP client based on the type input.
void UDPSocket::udpClientBind(CONNECT_TYPE udptype, const string& address = 0, unsigned short port = 8888)
{
    switch (udptype)
    {
    case CONNECT_TYPE::UDP_UNICAST:
        UDPSocket::unicastUDPClient(address, port);
        break;
    case CONNECT_TYPE::UDP_MULTICAST:
        UDPSocket::multicastUDPClient("224.0.0.51", 5000);
        break;
    case CONNECT_TYPE::UDP_BROADCAST:
        UDPSocket::broadcastUDPClient(port);
        break;
    default:
        printf("UDP type not found.\n");
        break;
    }
}

void UDPSocket::SendTo(const string& address, unsigned short port, const char* buffer, int len, int flags)
{
    sockaddr_in add;
    add.sin_family = AF_INET;
    inet_pton(AF_INET, (PCSTR)(address.c_str()), &add.sin_addr.s_addr);
    add.sin_port = htons(port);
    int ret = sendto(sock, buffer, len, flags, reinterpret_cast<SOCKADDR*>(&add), sizeof(add));
    if (ret < 0)
    {
        throw system_error(WSAGetLastError(), system_category(), "sendto failed");
    }
        
}

void UDPSocket::SendTo(sockaddr_in& address, const char* buffer, int len, int flags)
{
    int ret = sendto(sock, buffer, len, flags, reinterpret_cast<SOCKADDR*>(&address), sizeof(address));
    if (ret < 0)
    {
        throw system_error(WSAGetLastError(), system_category(), "sendto failed");
    }
        
}

// This function is called when UDP socket receives data.
//JSF change from basic type to typedef and avoid passing by array
UINT32 UDPSocket::Listen(char(&message)[msg_size])
{
    //JSF change basic type
    UINT32 msglen = RecvFrom(message, sizeof(message));
    printf("Data received.\n");

    return msglen;
}


// Private Functions

// This function creates a broadcast UDP client (any IP, fixed port)
void UDPSocket::broadcastUDPClient(unsigned short port)
{
    sockaddr_in add;
    add.sin_family = AF_INET;
    add.sin_addr.s_addr = htonl(INADDR_ANY);
    add.sin_port = htons(port);

    int ret = bind(sock, reinterpret_cast<SOCKADDR*>(&add), sizeof(add));
    if (ret < 0)
    {
        throw system_error(WSAGetLastError(), system_category(), "Bind failed");
    }
}

// This function creates a unicast UDP client (fixed IP, fixed port)
void UDPSocket::unicastUDPClient(const string& address, unsigned short port)
{
    sockaddr_in add;
    add.sin_family = AF_INET;
    inet_pton(AF_INET, (PCSTR)(address.c_str()), &add.sin_addr.s_addr);
    add.sin_port = htons(port);

    int ret = bind(sock, reinterpret_cast<SOCKADDR*>(&add), sizeof(add));
    if (ret < 0)
    {
        throw system_error(WSAGetLastError(), system_category(), "Bind failed");
    }
}

// This function creates a multicast UDP client (uses setsockopt() to join UDP group)
void UDPSocket::multicastUDPClient(const string& address, unsigned short port)
{
    sockaddr_in mc_addr;
    struct ip_mreq mc_req;

    // Construct a multicast address structure
    memset(&mc_addr, 0, sizeof(mc_addr));
    mc_addr.sin_family = AF_INET;
    mc_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    mc_addr.sin_port = htons(port);

    // Bind to multicast address to socket 
    if ((bind(sock, (struct sockaddr*)&mc_addr,
        sizeof(mc_addr))) < 0) 
    {
        perror("bind() failed");
        exit(1);
    }

    // Construct an IGMP join request structure 
    inet_pton(AF_INET, (PCSTR)(address.c_str()), &mc_req.imr_multiaddr.s_addr);
    mc_req.imr_interface.s_addr = htonl(INADDR_ANY);

    // Set ADD_MEMBERSHIP 
    if ((setsockopt(sock, IPPROTO_IP, IP_ADD_MEMBERSHIP,
        (char*)&mc_req, sizeof(mc_req))) < 0) 
    {
        perror("setsockopt() failed");
        exit(1);
    }
}

int UDPSocket::RecvFrom(char* buffer, int len, int flags)
{
    sockaddr_in from;
    int size = 1024;
    int ret = recvfrom(sock, buffer, size, flags, reinterpret_cast<SOCKADDR*>(&from), &size);
    if (ret < 0)
    {
        throw system_error(WSAGetLastError(), system_category(), "recvfrom failed");
    }

    return ret;
}



