namespace EmuSample.Connections
{
    interface Connection
    {
        void Server(string address, int port);
        void ServerMulti(string address, int port);
        void Client(string address, int port);
        void ClientMulti(string address, int port);
        void Send(string text);
        void Receive();
    }
}
