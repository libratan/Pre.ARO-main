using EmuSample.Functions;
using EmuSample.Initialisation;
using EmuSample.UDP;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Threading;
using System.Windows;
using System.Windows.Media;

namespace EmuSample
{
    // x:Class="EmuSample.MainWindow"

    public partial class MainWindow : Window, INotifyPropertyChanged
    {
        // Private
        private DataLogger dataLogger = new DataLogger("../../../Content/Files/MessageLogs.csv");
        // private FlightData ownship = new FlightData();

        // Global Objects 
        public UDPSocket s = new UDPSocket();
        public UDPSocket c = new UDPSocket();
        public UDPSocket sc_s1 = new UDPSocket();
        public UDPSocket sc_s2 = new UDPSocket();
        public UDPSocket sc_c1 = new UDPSocket();
        public UDPSocket sc_c2 = new UDPSocket();
        public SearchParameters search = new SearchParameters();
        public List<FlightData> flightdata = new List<FlightData>();
        public List<SymbolsData> symboldata = new List<SymbolsData>();
        public dataType periodic_choice;
        public XMLInfo xmlItem = new XMLInfo();
        public Periodic p_msg = new Periodic();

        // Global Conditions
        public bool serverbutton = false;
        public bool client1button = false;
        public bool client2button = false;

        // Interaction logic for MainWindow.xaml
        public MainWindow()
        {
            InitializeComponent();

            // Load UDP Connection Info
            xmlItem.xReader.Load(@"../../../Content/Files/XMLFile1.xml");

            // CSV Objects 
            DataTable csvTable_A = new DataTable();
            string file_A = "../../../Content/Files/AperiodicInfo.csv";
            DataTable csvTable_P = new DataTable();
            string file_P = "../../../Content/Files/PeriodicInfo.csv";
            DataTable csvTable_Flight = new DataTable();
            string file_Flight = "../../../Content/Files/ICD_Positions.csv";
            DataTable csvTable_Symbols = new DataTable();
            string file_Symbols = "../../../Content/Files/ICD_Symbols.csv";

            // Load & Read CSV
            BasicFunctions.csvRead(csvTable_A, file_A);
            BasicFunctions.csvRead(csvTable_P, file_P);
            BasicFunctions.csvRead(csvTable_Flight, file_Flight);
            BasicFunctions.csvRead(csvTable_Symbols, file_Symbols);

            // Flight Data Transfer (List)
            FlightData.add2List_flight(csvTable_Flight, flightdata);
            // _ownshiplog.ItemsSource = ownship.get_ownship(); - not updating * 

            // Symbols Data Transfer (List)
            SymbolsData.add2List_symbols(csvTable_Symbols, symboldata);

            // Combobox Lists 
            search.searchParameters_A = new List<SearchParameters>();
            search.searchParameters_P = new List<SearchParameters>();
            List<string> combo_A = new List<string>();
            List<string> combo_P = new List<string>();

            // Add Aperiodic & Periodic Data into Individual Lists
            BasicFunctions.add2List(csvTable_A, search.searchParameters_A, combo_A);
            BasicFunctions.add2List(csvTable_P, search.searchParameters_P, combo_P);

            // Update Aperiodic & Periodic ItemSource
            cmbAperiodic.ItemsSource = combo_A;
            cmbPeriodic.ItemsSource = combo_P;

            // View Sent & Received Messages 
            _dataLog.ItemsSource = dataLogger.get_msgCarrier();
        }

        public enum dataType
        {
            FLIGHT = 0,
            SYMBOLS
        }

        // Declarations for ReceivedMsg UI 
        private string _incText;
        public string IncText
        {
            get => _incText;
            set
            {
                if (string.Equals(value, _incText))
                {
                    return;
                }
                _incText = value;
                Received_OnPropertyChanged("IncText");
            }
        }

        private void IncText_PropertyChanged(object sender, string newtext) // event handler when msg is received
        {
            // trigger UI receivedmsg property change event
            IncText = newtext;
            ReceivedText_Save(IncText);
        }

        private void ReceivedText_Save(string newtext) // save received msg to csv 
        {
            if (Dispatcher.Thread != Thread.CurrentThread)
            {
                // Invoke Required
                Dispatcher.BeginInvoke(new Action(() => dataLogger.Log(newtext, LogType.RECEIVED)), System.Windows.Threading.DispatcherPriority.Background, null);
            }
        }

        // Event : INotifyPropertyChanged Members
        public event PropertyChangedEventHandler PropertyChanged;
        protected virtual void Received_OnPropertyChanged(string propertyName)
        {
            PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(propertyName));
        }

        // --- From Here Onwards ---
        // --- Functions for Every Button ---

        private void btn_setServer(object sender, RoutedEventArgs e) // assign field as server (Connections Page) 
        {
            s.Server("127.0.0.1", 63864);
            serverbutton = true; // set application as server 

            s._ReceivedMsg += IncText_PropertyChanged; // register main with receivemsg event 

            sc_c1.Client("127.0.0.1", 50057); // client port to talk to Client1
            sc_c2.Client("127.0.0.1", 50058); // client port to talk to Client2

            // UI Updates
            btn_Server.Background = Brushes.LightGreen;
        }

        private void btn_setClient1(object sender, RoutedEventArgs e) // assign field as client1 (Connections Page) 
        {
            c.Client("127.0.0.1", 63864);
            client1button = true; // set application as Client1 

            sc_s1.Server("127.0.0.1", 50057); // server port to listen to Server

            sc_s1._ReceivedMsg += IncText_PropertyChanged; // register main with receivemsg event 

            // UI Updates
            btn_Client1.Background = Brushes.LightSalmon;
        }

        private void btn_setClient2(object sender, RoutedEventArgs e) // assign field as client2 (Connections Page) 
        {
            c.Client("127.0.0.1", 63864);
            client2button = true; // set application as Client2 

            sc_s2.Server("127.0.0.1", 50058); // server port to listen to Server
            sc_s2._ReceivedMsg += IncText_PropertyChanged; // register main with receivemsg event 

            // UI Updates
            btn_Client2.Background = Brushes.LightSalmon;
        }

        private void btn_Connect2DMM(object sender, RoutedEventArgs e) // assign field as client2DMM (Connections Page) 
        {
            // extracting UDP host info 
            xmlItem.MyNodeHost = xmlItem.xReader.SelectSingleNode("XML/Connection/Host/text()");
            xmlItem.HostInfo = xmlItem.MyNodeHost.Value;

            // extracting UDP port info 
            xmlItem.MyNodePort = xmlItem.xReader.SelectSingleNode("XML/Connection/Port/text()");
            xmlItem.PortInfo = int.Parse(xmlItem.MyNodePort.Value);

            // connect to DMM
            p_msg.connectDMM(xmlItem.HostInfo, xmlItem.PortInfo);

            // UI Updates
            btn_sendDMM.Background = Brushes.LightGreen;
        }

        private void btn_Send2DMM(object sender, RoutedEventArgs e) // assign field as client2DMM (Connections Page) 
        {
            p_msg.flightdata = flightdata;
            p_msg.symboldata = symboldata;

            // Starts Timer 
            p_msg.f_InitTimer();
            p_msg.s_InitTimer();

            // UI Updates 
            // ...
        }

        private void btn_PSend2DMM(object sender, RoutedEventArgs e) // assign field as client2DMM 
        {
            // select between Flight/Symbol file functions here
            if (periodic_choice == dataType.SYMBOLS)
            {
                p_msg.symboldata = symboldata;
                p_msg.s_InitTimer();
            }
            else if (periodic_choice == dataType.FLIGHT)
            {
                p_msg.flightdata = flightdata;
                p_msg.f_InitTimer();
            }

            // UI Updates 
            // ...
        }

        private void btn_Stop2DMM(object sender, RoutedEventArgs e) // stop timer for DMM sending interval (Connections Page) 
        {
            p_msg.stopSend();
        }

        private void btn_SendCli(object sender, RoutedEventArgs e) // send message as client (Connections Page) 
        {
            // update log
            dataLogger.Log(SendingMsg.Text, LogType.SENT);

            if (serverbutton && (client1button || client2button)) // localhost condition - same app 
            {
                c.Send(SendingMsg.Text); // client sends a message 
            }
            else if (serverbutton)
            {
                sc_c1.Send(SendingMsg.Text); // server sends a message to Client1
                sc_c2.Send(SendingMsg.Text); // server sends a message to Client2
            }
            else if (client1button)
            {
                c.Send(SendingMsg.Text); // client sends a message 
            }
            else if (client2button)
            {
                c.Send(SendingMsg.Text); // client sends a message 
            }

            // clear textbox after sending
            SendingMsg.Text = "";
        }

        private void btn_clearmsg(object sender, RoutedEventArgs e) // clear received message (Connections Page) 
        {
            // clear received text
            IncText = "";
        }

        private void btn_LocalDisCn(object sender, RoutedEventArgs e) // disconnect all client server connections (Connections Page)
        {
            // Close Connection
            if (serverbutton && client1button)
            {
                c._socket.Close(); // Client1 sending port closed
                s._socket.Close(); // Server listening port closed
                sc_s1._socket.Close(); // Client1 listening port closed
                sc_c1._socket.Close(); // Server sending port1 closed
                sc_c2._socket.Close(); // Server sending port2 closed
            }
            else if (serverbutton && client2button)
            {
                c._socket.Close();
                s._socket.Close();
                sc_s2._socket.Close();
                sc_c1._socket.Close();
                sc_c2._socket.Close();
            }
            else if (serverbutton)
            {
                s._socket.Close();
                sc_c1._socket.Close();
                sc_c2._socket.Close();
            }
            else if (client1button)
            {
                c._socket.Close();
                sc_s1._socket.Close();
            }
            else if (client2button)
            {
                c._socket.Close();
                sc_s2._socket.Close();
            }

            System.Diagnostics.Debug.WriteLine(">>>>>> Closed Server \n");

            // UI Changes 
            IncText = "";
            btn_Server.Background = Brushes.LightGray;
            btn_Client1.Background = Brushes.LightGray;
            btn_Client2.Background = Brushes.LightGray;

            // Condition Changes 
            serverbutton = false;
            if (client1button)
            {
                client1button = false;
            }
            else
            {
                client2button = false;
            }
        }

        private void Msg_DblClick(object sender, RoutedEventArgs e) // double click to view more details of message 
        {
            // Fetch related message 
            // Not using this function yet
            MessageBox.Show("Extra Information Displays Here");
        }

        private void btn_ClearAll(object sender, RoutedEventArgs e) // function to clear all messages shown 
        {
            dataLogger.get_msgCarrier().Clear();
        }

        private void ViewMore_A(object sender, RoutedEventArgs e) // view details of selected msg 
        {
            string combochoice = cmbAperiodic.SelectedItem.ToString();
            string chosenData;
            List<string> choices = new List<string>();

            for (int i = 0; i < search.searchParameters_A.Count; i++)
            {
                chosenData = search.searchParameters_A[i].Title;

                if (combochoice == chosenData)
                {
                    choices.Add(string.Concat("Title: ", search.searchParameters_A[i].Title));
                    choices.Add(string.Concat("Priority: ", search.searchParameters_A[i].Priority));
                    choices.Add(string.Concat("Information: ", search.searchParameters_A[i].Information));
                }
            }
            aperiodiclist.ItemsSource = choices;
        }

        private void ViewMore_P(object sender, RoutedEventArgs e) // view details of selected msg 
        {
            string combochoice = cmbPeriodic.SelectedItem.ToString();
            string chosenData;
            List<string> choices = new List<string>();

            for (int i = 0; i < search.searchParameters_P.Count; i++)
            {
                chosenData = search.searchParameters_P[i].Title;

                if (combochoice == chosenData)
                {
                    choices.Add(string.Concat("Title: ", search.searchParameters_P[i].Title));
                    choices.Add(string.Concat("Priority: ", search.searchParameters_P[i].Priority));
                    choices.Add(string.Concat("Information: ", search.searchParameters_P[i].Information));

                    periodic_choice = dataType.FLIGHT;
                }
                else
                {
                    periodic_choice = dataType.SYMBOLS;
                }
            }
            periodiclist.ItemsSource = choices;
        }

        private void btn_Send(object sender, RoutedEventArgs e) // send selected message 
        {
            aperiodiclist.Items.Clear();

            // other send functions to be created later as necessary
        }

        private void btn_UDPtype(object sender, RoutedEventArgs e) // check if app is Client/Server & extract host/port info 
        {
            /*
            // extracting UDP connection info 
            xmlItem.MyNodeType = xmlItem.xReader.SelectSingleNode("XML/Connection/Type/text()");
            UDPType.Text = String.Concat(xmlItem.MyNodeType.Value);

            // extracting UDP host info 
            xmlItem.MyNodeHost = xmlItem.xReader.SelectSingleNode("XML/Connection/Host/text()");
            xmlItem.HostInfo = String.Concat(xmlItem.MyNodeHost.Value);

            // extracting UDP port info 
            xmlItem.MyNodePort = xmlItem.xReader.SelectSingleNode("XML/Connection/Port/text()");
            xmlItem.PortInfo = int.Parse(xmlItem.MyNodePort.Value);

            // Connection Type 
            if (UDPType.Text == "Server" || UDPType.Text == "server")
            {
                s.Server(xmlItem.HostInfo, xmlItem.PortInfo);
            }
            else if (UDPType.Text == "Client" || UDPType.Text == "client")
            {
                c.Client(xmlItem.HostInfo, xmlItem.PortInfo);
            }
            else
            {
                MessageBox.Show("No Connection Type Selected");
            }

            // represent successful connection
            Connected.IsChecked = true;*/
        }
    }
}
