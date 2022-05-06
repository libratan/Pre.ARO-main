#ifndef NETWORK_H
#define NETWORK_H

#pragma once
#include <windows.h>
#include <system_error>
#include <string>
#include <iostream>

using namespace std;

namespace Network
{
    enum class CONNECT_TYPE
    {
        UDP_UNICAST,
        UDP_MULTICAST,
        UDP_BROADCAST,
        TCP_UNICAST
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

        //*This enum to hold relevant constants
        enum NETWORK_CONSTANTS
        {
            msg_size = 1024             // buffer data size 
        };


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
    
        void udpClientBind(CONNECT_TYPE udptype, const string& address, unsigned short port);
        void SendTo(const string& address, unsigned short port, const char* buffer, int len, int flags = 0);
        void SendTo(sockaddr_in& address, const char* buffer, int len, int flags = 0);
        //JSF correct the type as well as passing by array object
        //this original code is commented off : int Listen(char* message);
        UINT32 Listen(char (&message)[msg_size]);


    private:
        SOCKET sock;

        void broadcastUDPClient(unsigned short port);
        void unicastUDPClient(const string& address, unsigned short port);
        void multicastUDPClient(const string& address, unsigned short port);
        int RecvFrom(char* buffer, int len, int flags = 0);
    };

    class TCPSocket
    {
    public:
        TCPSocket()
        {
            sock = socket(AF_INET, SOCK_STREAM, 0);
            if (sock == INVALID_SOCKET)
                throw system_error(WSAGetLastError(), system_category(), "Error opening socket");
        }
        ~TCPSocket()
        {
            closesocket(sock);
        }

        void tcpConnect(CONNECT_TYPE tcpType, const string& address, unsigned short port);

        void unicastTCPClient(const string& address, unsigned short port);

        void Send(const char* buffer, int len, int flags);
        bool checkConnection(void);
        //void SendTo(sockaddr_in& address, const char* buffer, int len, int flags = 0);
        //int Listen(char* message);

    private:
        SOCKET sock;

        //void broadcastUDPClient(unsigned short port);
        //void unicastUDPClient(const string& address, unsigned short port);
        //void multicastUDPClient(const string& address, unsigned short port);
        //int RecvFrom(char* buffer, int len, int flags = 0);
    };
}

#endif