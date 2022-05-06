using System;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Windows;

namespace EmuSample.Connections
{
    class UDPSocket : Connection
    {
        private State state = new State();
        // Declarations for ReceivedMsg UI 
        private string _received;
        public string ReceivedText
        {
            get => _received;
            set
            {
                if (string.Equals(value, _received))
                {
                    return;
                }
                _received = value;
                Received_OnPropertyChanged(ReceivedText); // pass value to event action
            }
        }

        // Event : Event Handler Members
        public event EventHandler<string> _ReceivedMsg; // event delegate
        protected virtual void Received_OnPropertyChanged(string textmsg) // event action to register received string 
        {
            _ReceivedMsg?.Invoke(this, textmsg);
        }

        public class State
        {
            public byte[] buffer = new byte[bufSize];
        }

        public override void Server(string address, int port)
        {
            try
            {
                // Unicast
                _socket = new Socket(AddressFamily.InterNetwork, SocketType.Dgram, ProtocolType.Udp);
                _socket.SetSocketOption(SocketOptionLevel.IP, SocketOptionName.ReuseAddress, true);
                _socket.Bind(new IPEndPoint(IPAddress.Parse(address), port));

                Receive();
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }

        public override void ServerMulti(string address, int port)
        {
            try
            {
                // Multicast 
                _socket = new Socket(AddressFamily.InterNetwork, SocketType.Dgram, ProtocolType.Udp);
                _socket.Bind(new IPEndPoint(IPAddress.Any, port));
                _socket.SetSocketOption(SocketOptionLevel.IP, SocketOptionName.AddMembership, new MulticastOption(IPAddress.Parse(address), IPAddress.Any));

                Receive();
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }

        public override void Client(string address, int port)
        {
            // Unicast
            _socket = new Socket(AddressFamily.InterNetwork, SocketType.Dgram, ProtocolType.Udp);
            _socket.Connect(IPAddress.Parse(address), port);

            Receive();
        }

        public override void ClientMulti(string address, int port)
        {
            // Multicast
            _socket = new Socket(AddressFamily.InterNetwork, SocketType.Dgram, ProtocolType.Udp);
            _socket.SetSocketOption(SocketOptionLevel.IP, SocketOptionName.AddMembership, new MulticastOption(IPAddress.Parse(address)));
            _socket.SetSocketOption(SocketOptionLevel.IP, SocketOptionName.MulticastTimeToLive, 2);
            _socket.Connect(new IPEndPoint(IPAddress.Parse(address), port));

            Receive();
        }

        public override void Send(byte[] data)
        {
            try
            {
                _socket.BeginSend(data, 0, data.Length, SocketFlags.None, (ar) =>
                {
                    State so = (State)ar.AsyncState;
                    int bytes = _socket.EndSend(ar);
                    System.Diagnostics.Debug.WriteLine(">>>>>> SEND: {0}", bytes);
                }, state);
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }

        public override void Receive()
        {
            _socket.BeginReceiveFrom(state.buffer, 0, bufSize, SocketFlags.None, ref epFrom, recv = (ar) =>
            {
                try
                {
                    State so = (State)ar.AsyncState;
                    int bytes = _socket.EndReceiveFrom(ar, ref epFrom);
                    _socket.BeginReceiveFrom(so.buffer, 0, bufSize, SocketFlags.None, ref epFrom, recv, so);
                    System.Diagnostics.Debug.WriteLine(">>>>>> RECV: {0}: {1}, {2}", epFrom.ToString(), bytes, Encoding.ASCII.GetString(so.buffer, 0, bytes));

                    // Update UI 
                    ReceivedText = Encoding.ASCII.GetString(so.buffer, 0, bytes); // trigger event 
                }
                catch (Exception ex)
                {
                    MessageBox.Show(ex.Message);
                }

            }, state);
        }
    }
}
