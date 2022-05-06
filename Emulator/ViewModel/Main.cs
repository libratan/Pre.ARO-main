using EmuSample.Connections;
using EmuSample.DataTables;
using EmuSample.ICDInit;
using EmuSample.TimerEvent;
using System.Windows.Input;

namespace EmuSample.ViewModel
{
    // x:Class="EmuSample.ViewModel.MainViewModel"

    // Event Flow
    // 1. Load XML & CSV Files (DataTables)
    // 2. Assign CSV data into DataTables (DataTables)
    // 3. Connect UDP Multicast using XML Config Info (UDPSocket)
    // 4. Start Sending via UDP (Messages) 
    // 5. Log Items Sent (DataLoggers)

    public class MainViewModel
    {
        // --------------------------------------------------------------------------------------------

        private ICommand xml_button;
        public ICommand XML_ButtonCommand // in xaml : button Command = "{Binding XML_ButtonCommand}" 
        {
            get
            {
                return xml_button ??= new RelayCommand(
                   x =>
                   {
                       LoadXML();
                   });
            }
        }

        private ICommand csv_button;
        public ICommand CSV_ButtonCommand // in xaml : button Command = "{Binding CSV_ButtonCommand}" 
        {
            get
            {
                return csv_button ??= new RelayCommand(
                   x =>
                   {
                       LoadCSV();
                   });
            }
        }

        private ICommand udp_button;
        public ICommand UDP_ButtonCommand // in xaml : button Command = "{Binding UDP_ButtonCommand}" 
        {
            get
            {
                return udp_button ??= new RelayCommand(
                   x =>
                   {
                       ConnectUDP();
                   });
            }
        }

        private ICommand send_button;
        public ICommand Send_ButtonCommand // in xaml : button Command = "{Binding Send_ButtonCommand}" 
        {
            get
            {
                return send_button ??= new RelayCommand(
                   x =>
                   {
                       SendData();
                   });
            }
        }

        private ICommand stop_button;
        public ICommand Stop_ButtonCommand // in xaml : button Command = "{Binding Send_ButtonCommand}" 
        {
            get
            {
                return stop_button ??= new RelayCommand(
                   x =>
                   {
                       StopData();
                   });
            }
        }

        // --------------------------------------------------------------------------------------------

        XMLInfo xmlItem = new XMLInfo();
        UDPSocket pos_socket = new UDPSocket();
        UDPSocket sym_socket = new UDPSocket();

        FltData_Positions flightPositions = new FltData_Positions();
        Periodic_Pos p_timer = new Periodic_Pos();

        FltData_Symbols flightSymbols = new FltData_Symbols();
        Periodic_Sym s_timer = new Periodic_Sym();

        public void LoadXML()
        {
            xmlItem.xReader.Load(@"../../../Content/Files/XMLFile1.xml");

            // extracting UDP host info 
            xmlItem.MyNodeHost = xmlItem.xReader.SelectSingleNode("XML/Connection/Host/text()");
            xmlItem.HostInfo = xmlItem.MyNodeHost.Value;

            // extracting UDP port info 
            xmlItem.MyNodePort = xmlItem.xReader.SelectSingleNode("XML/Connection/Port/text()");
        }

        public void LoadCSV()
        {
            // Flight Positions 
            flightPositions.csvRead();
            flightPositions.add2List();

            // Flight Symbols 
            flightSymbols.csvRead();
            flightSymbols.add2List();
        }

        public void ConnectUDP()
        {
            pos_socket.ClientMulti(xmlItem.HostInfo, xmlItem.PortInfo);
            sym_socket.ClientMulti(xmlItem.HostInfo, xmlItem.PortInfo);
        }

        public void SendData()
        {
            // Flight Positions 
            p_timer.cm = pos_socket;
            p_timer.datalist = flightPositions.datalist;

            // Flight Symbols 
            s_timer.cm = sym_socket;
            s_timer.datalist = flightSymbols.datalist;

            // Start Timer Event
            p_timer.initTimer();
            s_timer.initTimer();
        }

        public void StopData()
        {
            p_timer.stopSend();
            s_timer.stopSend();

            System.Diagnostics.Debug.WriteLine("StopData() Activated");
        }
    }

    /*private ICommand xml_button;
        public ICommand XML_ButtonCommand // in xaml : button Command = "{Binding XML_ButtonCommand}" 
        {
            get
            {
                return xml_button;
            }
            set
            {
                xml_button = value;
            }
        }

        private ICommand csv_button;
        public ICommand CSV_ButtonCommand // in xaml : button Command = "{Binding CSV_ButtonCommand}" 
        {
            get
            {
                return csv_button;
            }
            set
            {
                csv_button = value;
            }
        }

        private ICommand udp_button;
        public ICommand UDP_ButtonCommand // in xaml : button Command = "{Binding UDP_ButtonCommand}" 
        {
            get
            {
                return udp_button;
            }
            set
            {
                udp_button = value;
            }
        }

        private ICommand send_button;
        public ICommand Send_ButtonCommand // in xaml : button Command = "{Binding Send_ButtonCommand}" 
        {
            get
            {
                return send_button;
            }
            set
            {
                send_button = value;
            }
        }

        // --------------------------------------------------------------------------------------------

        public MainViewModel()
        {
            // XML_ButtonCommand = LoadXML();
        }*/
}
