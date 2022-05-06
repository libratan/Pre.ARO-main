#ifndef TCPSOCKET_CPP
#define TCPSOCKET_CPP

#include <WinSock2.h>
#include <string.h>
#include <../DMM/header/Network.h>
#include "WS2tcpip.h"
#include <../MSG/header/Deserializer.h>

using namespace std;
using namespace Network;
// Public Functions

// This function binds the UDP client based on the type input.
void TCPSocket::tcpConnect(CONNECT_TYPE tcpType, const string& address = 0, unsigned short port = 8888)
{
    switch (tcpType)
    {
    case CONNECT_TYPE::TCP_UNICAST:
        TCPSocket::unicastTCPClient(address, port);
        break;
    default:
        printf("CONNECT type not found.\n");
        break;
    }
}

// This function creates a unicast UDP client (fixed IP, fixed port)
void TCPSocket::unicastTCPClient(const string& address, unsigned short port)
{
    sockaddr_in add;
    add.sin_family = AF_INET;
    inet_pton(AF_INET, (PCSTR)(address.c_str()), &add.sin_addr.s_addr);
    add.sin_port = htons(port);

    if (connect(sock, reinterpret_cast<SOCKADDR*>(&add), sizeof(add)) < 0) 
    {
        printf("\nConnection Failed \n");
    }
}

void TCPSocket::Send(const char* buffer, int len, int flags)
{
    if (checkConnection())
    {
        int ret = send(sock, buffer, len, flags);
        if (ret < 0)
        {
            //throw system_error(WSAGetLastError(), system_category(), "send failed");
        }
    }
}

bool TCPSocket::checkConnection(void)
{
    char error_code;
    int error_code_size = sizeof(error_code);
    if(getsockopt(sock, SOL_SOCKET, SO_ERROR, &error_code, &error_code_size) != SOCKET_ERROR)
    {
        if (WSAGetLastError() != WSAEWOULDBLOCK)
        {
            return false;
        }
    }
    return true;
}

#endif // !TCPSOCKET_CPP