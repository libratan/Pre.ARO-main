using System;
using System.Net;
using System.Net.Sockets;
using System.Text;

namespace Client
{
    class ClientSender
    {
        public static int Main(String[] args)
        {
            Console.WriteLine("Send Message: ");
            string data = Console.ReadLine();

            StartClient(data);
            return 0;
        }

        public static void StartClient(string sendmsg)
        {
            byte[] bytes = new byte[1024];

            try
            {
                // Connect to a Remote server
                // Get Host IP Address that is used to establish a connection
                // In this case, we get one IP address of localhost that is IP : 127.0.0.1
                // If a host has multiple addresses, you will get a list of addresses
                //IPHostEntry host = Dns.GetHostEntry("localhost");
                //IPAddress ipAddress = host.AddressList[0];
                IPEndPoint remoteEP = new IPEndPoint(IPAddress.Parse("127.0.0.2"), 63864);

                // Create a TCP/IP  socket.
                Socket sender = new Socket(AddressFamily.InterNetwork,
                    SocketType.Stream, ProtocolType.Tcp);

                // Connect the socket to the remote endpoint. Catch any errors.
                try
                {
                    // Connect to Remote EndPoint
                    sender.Connect(remoteEP);

                    System.Diagnostics.Debug.WriteLine("Socket connected to {0}",
                        sender.RemoteEndPoint.ToString());
                    Console.WriteLine("Socket connected to {0}",
                        sender.RemoteEndPoint.ToString());

                    // Encode the data string into a byte array.
                    byte[] msg = Encoding.ASCII.GetBytes(sendmsg + " <EOF>");

                    // Send the data through the socket.
                    int bytesSent = sender.Send(msg);

                    // Receive the response from the remote device.
                    int bytesRec = sender.Receive(bytes);
                    System.Diagnostics.Debug.WriteLine("Echoed test = {0}",
                        Encoding.ASCII.GetString(bytes, 0, bytesRec));
                    Console.WriteLine("Echoed test = {0}",
                        Encoding.ASCII.GetString(bytes, 0, bytesRec));

                    // Release the socket.
                    sender.Shutdown(SocketShutdown.Both);
                    sender.Close();

                }
                catch (ArgumentNullException ane)
                {
                    System.Diagnostics.Debug.WriteLine("ArgumentNullException : {0}", ane.ToString());
                }
                catch (SocketException se)
                {
                    System.Diagnostics.Debug.WriteLine("SocketException : {0}", se.ToString());
                }
                catch (Exception e)
                {
                    System.Diagnostics.Debug.WriteLine("Unexpected exception : {0}", e.ToString());
                }

            }
            catch (Exception e)
            {
                System.Diagnostics.Debug.WriteLine(e.ToString());
            }
        }
    }
}
