#pragma once
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <system_error>
#include <string>
#include <iostream>

using namespace std;

namespace Network
{
    enum class UDP_TYPE
    {
        UDP_UNICAST,
        UDP_MULTICAST,
        UDP_BROADCAST
    };

    class WSASession
    {
    public:
        WSASession()
        {
            int ret = WSAStartup(MAKEWORD(2, 2), &data);
            if (ret != 0)
                throw system_error(WSAGetLastError(), system_category(), "WSAStartup Failed");
        }
        ~WSASession()
        {
            WSACleanup();
        }
    private:
        WSAData data;
    };

    class UDPSocket
    {
    public:
        UDPSocket()
        {
            sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
            if (sock == INVALID_SOCKET)
                throw system_error(WSAGetLastError(), system_category(), "Error opening socket");
        }
        ~UDPSocket()
        {
            closesocket(sock);
        }
    
        void udpClientBind(UDP_TYPE udptype, const string& address, unsigned short port);
        void SendTo(const string& address, unsigned short port, const char* buffer, int len, int flags = 0);
        void SendTo(sockaddr_in& address, const char* buffer, int len, int flags = 0);
        int Listen(char* message);

    private:
        SOCKET sock;

        void broadcastUDPClient(unsigned short port);
        void unicastUDPClient(const string& address, unsigned short port);
        void multicastUDPClient(const string& address, unsigned short port);
        int RecvFrom(char* buffer, int len, int flags = 0);
    };
}
