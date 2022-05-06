using EmuSample.DataLoggers;
using System;
using System.Net;
using System.Net.Sockets;
using System.Collections.Generic;
using System.Text;

namespace EmuSample.Connections
{
    public class TCPServer
    {
        // Server Socket
        private Socket listener;
        private string directory_path;

        // List of Clients
        public static List<Client> Clients = new List<Client>();

        public TCPServer(string path)
        {
            directory_path = path;
        }

        ~TCPServer()
        {
            listener.Close();
        }

        public void StartServer()
        {
            // Establish Connection
            IPEndPoint localEndPoint = new IPEndPoint(IPAddress.Any, 63864);

            try
            {
                // Bind Socket 
                listener = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
                listener.Bind(localEndPoint);
                System.Diagnostics.Debug.WriteLine("Waiting for a connection...");
                System.Diagnostics.Debug.WriteLine("[ Connected ]");

                listener.Listen(10);

                // Wait for Message 
                System.Diagnostics.Debug.WriteLine("Waiting for message...");
                listener.BeginAccept(AcceptCallback, listener);
            }
            catch (Exception e)
            {
                System.Diagnostics.Debug.WriteLine(e.ToString());
            }
        }

        public void AcceptCallback(IAsyncResult ar)
        {
            try
            {
                Socket clientSocket = listener.EndAccept(ar);

                // Establish Client 
                int clientId = Clients.Count + 1;
                string logPath = directory_path + "TCPLogs" + clientId + ".csv";

                System.Diagnostics.Debug.WriteLine("Client(" + clientId + "): Sent");
                Client newClient = new Client(clientSocket, clientId, logPath);
                Clients.Add(newClient);

                // This is to prepare for 2nd client
                listener.BeginAccept(AcceptCallback, listener);
            }
            catch (Exception ex)
            {
                throw new Exception("Base Accept error" + ex);
            }
        }
    }

    public class Client
    {
        public int clientId { get; set; }
        public Socket acceptedSocket { get; set; }  // Client socket

        private Logger m_datalogger;
        private const int bufSize = 8 * 1024;
        private byte[] _bytes_buffer;
        private string data;

        public Client(Socket socket, int id, string path)
        {
            acceptedSocket = socket;
            clientId = id;

            m_datalogger = new Logger(path);
            _bytes_buffer = new byte[bufSize];
            data = null;

            StartReceiving();
        }

        public void StartReceiving()
        {
            acceptedSocket.BeginReceive(_bytes_buffer, 0, bufSize, SocketFlags.None, ReceiveCallback, null);
        }

        private void ReceiveCallback(IAsyncResult AR)
        {
            try
            {
                // if bytes are less than 1 takes place when a client disconnect from the server.
                int bytes = acceptedSocket.EndReceive(AR);

                if (bytes > 1)
                {
                    data += Encoding.ASCII.GetString(_bytes_buffer, 0, bytes);

                    // Log Data
                    m_datalogger.Log(data, LogType.RECEIVED);

                    System.Diagnostics.Debug.WriteLine(data);

                    // Echo Back
                    // byte[] msg = Encoding.ASCII.GetBytes(data);
                    // handler.Send(msg);

                    // Re-Init
                    data = null;

                    StartReceiving();     // wait for more data to arrive

                }
                else
                {
                    // disconnect
                    acceptedSocket.Disconnect(true);
                }
            }
            catch (Exception)
            {
                System.Diagnostics.Debug.WriteLine("Client Disconnected");
                // throw new Exception("Receive Data error" + ex);
            }
        }
    }
}
