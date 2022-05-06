using EmuSample.Connections;
using EmuSample.ICDInit;
using EmuSample.Messages;
using Microsoft.Toolkit.Mvvm.Input;
using System.Windows.Input;
using System.Collections.ObjectModel;
using System.ComponentModel;

namespace EmuSample.ViewModel
{
    public class MainViewModel : INotifyPropertyChanged
    {
        public ICommand XML_ButtonCommand { get; private set; }
        public ICommand CSV_ButtonCommand { get; private set; }
        public ICommand UDP_ButtonCommand { get; private set; }
        public ICommand TCP_ButtonCommand { get; private set; }
        public ICommand SendPos_ButtonCommand { get; private set; }
        public ICommand SendSym_ButtonCommand { get; private set; }
        public ICommand Stop_ButtonCommand { get; private set; }
        public ICommand SendStatus_ButtonCommand { get; private set; }

        // --------------------------------------------------------------------------------------------
        public ObservableCollection<MsgData> updateList { get; private set; }
        public ObservableCollection<AllSystemsStatus> BOXA { get; private set; }
        public ObservableCollection<AllSystemsStatus> DISPLAY1 { get; private set; }
        public ObservableCollection<AllSystemsStatus> DISPLAY2 { get; private set; }
        public ObservableCollection<AllSystemsStatus> BOXB1 { get; private set; }
        public ObservableCollection<AllSystemsStatus> BOXB2 { get; private set; }
        public ObservableCollection<AllSystemsStatus> SDX1 { get; private set; }
        public ObservableCollection<AllSystemsStatus> SDX2 { get; private set; }
        public ObservableCollection<AllSystemsStatus> SDX3 { get; private set; }
        public ObservableCollection<AllSystemsStatus> SATXXX { get; private set; }

        // --------------------------------------------------------------------------------------------
        private AllSystemsStatus BOXA_Choice = new AllSystemsStatus() { DeviceValue = 0 , Device = "BOXA", StatValue = 2, Stat = "PASSED" };
        public AllSystemsStatus BOXAChoice
        {
            get => BOXA_Choice;
            set
            {
                BOXA_Choice = value;
                NotifyPropertyChanged("BOXAChoice");
                SendStatus();
            }
        }

        private AllSystemsStatus DISPLAY1_Choice = new AllSystemsStatus() { DeviceValue = 1, Device = "DISPLAY1", StatValue = 2, Stat = "PASSED" };
        public AllSystemsStatus DISPLAY1Choice
        {
            get => DISPLAY1_Choice;
            set
            {
                DISPLAY1_Choice = value;
                NotifyPropertyChanged("DISPLAY1Choice");
                SendStatus();
            }
        }

        private AllSystemsStatus DISPLAY2_Choice = new AllSystemsStatus() { DeviceValue = 2, Device = "DISPLAY2", StatValue = 2, Stat = "PASSED" };
        public AllSystemsStatus DISPLAY2Choice
        {
            get => DISPLAY2_Choice;
            set
            {
                DISPLAY2_Choice = value;
                NotifyPropertyChanged("DISPLAY2Choice");
                SendStatus();
            }
        }

        private AllSystemsStatus BOXB1_Choice = new AllSystemsStatus() { DeviceValue = 3, Device = "BOXB1", StatValue = 2, Stat = "PASSED" };
        public AllSystemsStatus BOXB1Choice
        {
            get => BOXB1_Choice;
            set
            {
                BOXB1_Choice = value;
                NotifyPropertyChanged("BOXB1Choice");
                SendStatus();
            }
        }

        private AllSystemsStatus BOXB2_Choice = new AllSystemsStatus() { DeviceValue = 4, Device = "BOXB2", StatValue = 2, Stat = "PASSED" };
        public AllSystemsStatus BOXB2Choice
        {
            get => BOXB2_Choice;
            set
            {
                BOXB2_Choice = value;
                NotifyPropertyChanged("BOXB2Choice");
                SendStatus();
            }
        }

        private AllSystemsStatus SDX1_Choice = new AllSystemsStatus() { DeviceValue = 5, Device = "SDX1", StatValue = 2, Stat = "PASSED" };
        public AllSystemsStatus SDX1Choice
        {
            get => SDX1_Choice;
            set
            {
                SDX1_Choice = value;
                NotifyPropertyChanged("SDX1Choice");
                SendStatus();
            }
        }

        private AllSystemsStatus SDX2_Choice = new AllSystemsStatus() { DeviceValue = 6, Device = "SDX2", StatValue = 2, Stat = "PASSED" };
        public AllSystemsStatus SDX2Choice
        {
            get => SDX2_Choice;
            set
            {
                SDX2_Choice = value;
                NotifyPropertyChanged("SDX2Choice");
                SendStatus();
            }
        }

        private AllSystemsStatus SDX3_Choice = new AllSystemsStatus() { DeviceValue = 7, Device = "SDX3", StatValue = 2, Stat = "PASSED" };
        public AllSystemsStatus SDX3Choice
        {
            get => SDX3_Choice;
            set
            {
                SDX3_Choice = value;
                NotifyPropertyChanged("SDX3Choice");
                SendStatus();
            }
        }

        private AllSystemsStatus SATXXX_Choice = new AllSystemsStatus() { DeviceValue = 8, Device = "SATXXX", StatValue = 2, Stat = "PASSED" };
        public AllSystemsStatus SATXXXChoice
        {
            get => SATXXX_Choice;
            set
            {
                SATXXX_Choice = value;
                NotifyPropertyChanged("SATXXXChoice");
                SendStatus();
            }
        }

        // Event : INotifyPropertyChanged Members
        public event PropertyChangedEventHandler PropertyChanged;
        protected virtual void NotifyPropertyChanged(string propertyName)
        {
            PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(propertyName));
        }

        // --------------------------------------------------------------------------------------------
        MsgExecutor msgExecutor = new MsgExecutor("../../../Content/Files/Logs.csv");
        XMLInfo xmlItem = new XMLInfo();

        // Socket Declarations
        UDPSocket udp_socket = new UDPSocket();
        TCPServer tcp_socket = new TCPServer("../../../Content/Files/");

        // Message Declarations
        FltPositionMsg fltPositionMsg = new FltPositionMsg("../../../Content/Files/ICD_Positions.csv");
        FltSymbolsMsg fltSymbolsMsg = new FltSymbolsMsg("../../../Content/Files/ICD_Symbols.csv");
        SystemsStatusMsg systemsStatusMsg = new SystemsStatusMsg("");

        // --------------------------------------------------------------------------------------------
        public MainViewModel()
        {
            XML_ButtonCommand = new RelayCommand(LoadXML);
            CSV_ButtonCommand = new RelayCommand(LoadCSV);
            UDP_ButtonCommand = new RelayCommand(ConnectUDP);
            TCP_ButtonCommand = new RelayCommand(ConnectTCP);
            SendPos_ButtonCommand = new RelayCommand(SendPositions);
            SendSym_ButtonCommand = new RelayCommand(SendSymbols);
            Stop_ButtonCommand = new RelayCommand(StopData);
            SendStatus_ButtonCommand = new RelayCommand(SendStatus);

            updateList = msgExecutor.get_msgCarrier();

            BOXA = systemsStatusMsg.current_index.BOXA_List;
            DISPLAY1 = systemsStatusMsg.current_index.DISPLAY1_List;
            DISPLAY2 = systemsStatusMsg.current_index.DISPLAY2_List;
            BOXB1 = systemsStatusMsg.current_index.BOXB1_List;
            BOXB2 = systemsStatusMsg.current_index.BOXB2_List;
            SDX1 = systemsStatusMsg.current_index.SDX1_List;
            SDX2 = systemsStatusMsg.current_index.SDX2_List;
            SDX3 = systemsStatusMsg.current_index.SDX3_List;
            SATXXX = systemsStatusMsg.current_index.SATXXX_List;
        }

        // -------------------------------------------------------------------------------------------- 
        public void LoadXML()
        {
            xmlItem.xReader.Load(@"../../../Content/Files/XMLFile1.xml");

            // extracting UDP host info 
            xmlItem.MyNodeHost = xmlItem.xReader.SelectSingleNode("XML/Connection/Host/text()");
            xmlItem.HostInfo = xmlItem.MyNodeHost.Value;

            // extracting UDP port info 
            xmlItem.MyNodePort = xmlItem.xReader.SelectSingleNode("XML/Connection/Port/text()");
            xmlItem.PortInfo = int.Parse(xmlItem.MyNodePort.Value);

            System.Diagnostics.Debug.WriteLine("LoadXML() Activated");
        }

        public void LoadCSV()
        {
            System.Diagnostics.Debug.WriteLine("LoadCSV() Activated");
        }

        public void ConnectUDP()
        {
            udp_socket.ClientMulti(xmlItem.HostInfo, xmlItem.PortInfo);

            msgExecutor.AssociateMessage(fltPositionMsg, udp_socket);
            msgExecutor.AssociateMessage(fltSymbolsMsg, udp_socket);
            msgExecutor.AssociateMessage(systemsStatusMsg, udp_socket);

            System.Diagnostics.Debug.WriteLine("ConnectUDP() Activated");
        }

        public void ConnectTCP()
        {
            tcp_socket.StartServer();
        }

        public void SendPositions()
        {
            // Flight Positions 
            fltPositionMsg.State.RunState = RunState.RUNNING;

            System.Diagnostics.Debug.WriteLine("SendPositions() Activated");
        }

        public void SendSymbols()
        {
            // Flight Symbols 
            fltSymbolsMsg.State.RunState = RunState.RUNNING;

            System.Diagnostics.Debug.WriteLine("SendSymbols() Activated");
        }

        public void StopData()
        {
            msgExecutor.Stop();
            System.Diagnostics.Debug.WriteLine("StopData() Activated");
        }

        public void SendStatus()
        {
            systemsStatusMsg.State.RunState = RunState.RUNNING;

            systemsStatusMsg.current_index.message.system1 = BOXAChoice.DeviceValue;
            systemsStatusMsg.current_index.message.status1 = BOXAChoice.StatValue;
            systemsStatusMsg.current_index.message.system2 = DISPLAY1Choice.DeviceValue;
            systemsStatusMsg.current_index.message.status2 = DISPLAY1Choice.StatValue;
            systemsStatusMsg.current_index.message.system3 = DISPLAY2Choice.DeviceValue;
            systemsStatusMsg.current_index.message.status3 = DISPLAY2Choice.StatValue;
            systemsStatusMsg.current_index.message.system4 = BOXB1Choice.DeviceValue;
            systemsStatusMsg.current_index.message.status4 = BOXB1Choice.StatValue;
            systemsStatusMsg.current_index.message.system5 = BOXB2Choice.DeviceValue;
            systemsStatusMsg.current_index.message.status5 = BOXB2Choice.StatValue;
            systemsStatusMsg.current_index.message.system6 = SDX1Choice.DeviceValue;
            systemsStatusMsg.current_index.message.status6 = SDX1Choice.StatValue;
            systemsStatusMsg.current_index.message.system7 = SDX2Choice.DeviceValue;
            systemsStatusMsg.current_index.message.status7 = SDX2Choice.StatValue;
            systemsStatusMsg.current_index.message.system8 = SDX3Choice.DeviceValue;
            systemsStatusMsg.current_index.message.status8 = SDX3Choice.StatValue;
            systemsStatusMsg.current_index.message.system9 = SATXXXChoice.DeviceValue;
            systemsStatusMsg.current_index.message.status9 = SATXXXChoice.StatValue;
        }
    }
}
