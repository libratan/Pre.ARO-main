using System;
using System.Net;
using System.Net.Sockets;

namespace EmuSample.Connections
{
    public class Connection
    {
        protected Socket _socket;
        protected Socket _handler;
        protected const int bufSize = 8 * 1024;
        protected EndPoint epFrom = new IPEndPoint(IPAddress.Any, 0);
        protected AsyncCallback recv = null;

        public virtual void Server(string address, int port)
        {

        }
        public virtual void ServerMulti(string address, int port)
        {

        }
        public virtual void Client(string address, int port)
        {

        }
        public virtual void ClientMulti(string address, int port)
        {

        }
        public virtual void Send(byte[] data)
        {

        }
        public virtual void Receive()
        {

        }
    }
}
