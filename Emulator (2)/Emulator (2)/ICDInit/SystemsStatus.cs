using System.Collections.ObjectModel;

namespace EmuSample.ICDInit
{
    public struct systemData
    {
        public int system1;
        public int status1;
        public int system2;
        public int status2;
        public int system3;
        public int status3;
        public int system4;
        public int status4;
        public int system5;
        public int status5;
        public int system6;
        public int status6;
        public int system7;
        public int status7;
        public int system8;
        public int status8;
        public int system9;
        public int status9;
    };

    public class SystemsStatus
    {
        public string Timestamp;
        public header header;
        public systemData message;

        // Default constructor
        public SystemsStatus()
        {
            this.Timestamp = "";
            this.header.msg_id = 0;
            this.message.system1 = 0;
            this.message.status1 = 0;
            this.message.system2 = 0;
            this.message.status2 = 0;
            this.message.system3 = 0;
            this.message.status3 = 0;
            this.message.system4 = 0;
            this.message.status4 = 0;
            this.message.system5 = 0;
            this.message.status5 = 0;
            this.message.system6 = 0;
            this.message.status6 = 0;
            this.message.system7 = 0;
            this.message.status7 = 0;
            this.message.system8 = 0;
            this.message.status8 = 0;
            this.message.system9 = 0;
            this.message.status9 = 0;
        }

        public ObservableCollection<AllSystemsStatus> BOXA_List = new ObservableCollection<AllSystemsStatus>()
            {
              new AllSystemsStatus() { DeviceValue = 0 , Device = "BOXA", StatValue = 0, Stat = "FAIL" }
                    , new AllSystemsStatus() { DeviceValue = 0 , Device = "BOXA", StatValue = 1, Stat = "DEGRADED" }
                    , new AllSystemsStatus() { DeviceValue = 0 , Device = "BOXA", StatValue = 2, Stat = "PASSED" }
                    , new AllSystemsStatus() { DeviceValue = 0 , Device = "BOXA", StatValue = 3, Stat = "IBIT" }
            };

        public ObservableCollection<AllSystemsStatus> DISPLAY1_List = new ObservableCollection<AllSystemsStatus>()
            {
              new AllSystemsStatus() { DeviceValue = 1 , Device = "DISPLAY1", StatValue = 0, Stat = "FAIL" }
                    , new AllSystemsStatus() { DeviceValue = 1 , Device = "DISPLAY1", StatValue = 1, Stat = "DEGRADED" }
                    , new AllSystemsStatus() { DeviceValue = 1 , Device = "DISPLAY1", StatValue = 2, Stat = "PASSED" }
                    , new AllSystemsStatus() { DeviceValue = 1 , Device = "DISPLAY1", StatValue = 3, Stat = "IBIT" }
        };

        public ObservableCollection<AllSystemsStatus> DISPLAY2_List = new ObservableCollection<AllSystemsStatus>()
            {
              new AllSystemsStatus() { DeviceValue = 2 , Device = "DISPLAY2", StatValue = 0, Stat = "FAIL" }
                    , new AllSystemsStatus() { DeviceValue = 2 , Device = "DISPLAY2", StatValue = 1, Stat = "DEGRADED" }
                    , new AllSystemsStatus() { DeviceValue = 2 , Device = "DISPLAY2", StatValue = 2, Stat = "PASSED" }
                    , new AllSystemsStatus() { DeviceValue = 2 , Device = "DISPLAY2", StatValue = 3, Stat = "IBIT" }
        };

        public ObservableCollection<AllSystemsStatus> BOXB1_List = new ObservableCollection<AllSystemsStatus>()
            {
              new AllSystemsStatus() { DeviceValue = 3 , Device = "BOXB1", StatValue = 0, Stat = "FAIL" }
                    , new AllSystemsStatus() { DeviceValue = 3 , Device = "BOXB1", StatValue = 1, Stat = "DEGRADED" }
                    , new AllSystemsStatus() { DeviceValue = 3 , Device = "BOXB1", StatValue = 2, Stat = "PASSED" }
                    , new AllSystemsStatus() { DeviceValue = 3 , Device = "BOXB1", StatValue = 3, Stat = "IBIT" }
        };

        public ObservableCollection<AllSystemsStatus> BOXB2_List = new ObservableCollection<AllSystemsStatus>()
            {
              new AllSystemsStatus() { DeviceValue = 4 , Device = "BOXB2", StatValue = 0, Stat = "FAIL" }
                    , new AllSystemsStatus() { DeviceValue = 4 , Device = "BOXB2", StatValue = 1, Stat = "DEGRADED" }
                    , new AllSystemsStatus() { DeviceValue = 4 , Device = "BOXB2", StatValue = 2, Stat = "PASSED" }
                    , new AllSystemsStatus() { DeviceValue = 4 , Device = "BOXB2", StatValue = 3, Stat = "IBIT" }
        };

        public ObservableCollection<AllSystemsStatus> SDX1_List = new ObservableCollection<AllSystemsStatus>()
            {
              new AllSystemsStatus() { DeviceValue = 5 , Device = "SDX1", StatValue = 0, Stat = "FAIL" }
                    , new AllSystemsStatus() { DeviceValue = 5 , Device = "SDX1", StatValue = 1, Stat = "DEGRADED" }
                    , new AllSystemsStatus() { DeviceValue = 5 , Device = "SDX1", StatValue = 2, Stat = "PASSED" }
                    , new AllSystemsStatus() { DeviceValue = 5 , Device = "SDX1", StatValue = 3, Stat = "IBIT" }
        };

        public ObservableCollection<AllSystemsStatus> SDX2_List = new ObservableCollection<AllSystemsStatus>()
            {
              new AllSystemsStatus() { DeviceValue = 6 , Device = "SDX2", StatValue = 0, Stat = "FAIL" }
                    , new AllSystemsStatus() { DeviceValue = 6 , Device = "SDX2", StatValue = 1, Stat = "DEGRADED" }
                    , new AllSystemsStatus() { DeviceValue = 6 , Device = "SDX2", StatValue = 2, Stat = "PASSED" }
                    , new AllSystemsStatus() { DeviceValue = 6 , Device = "SDX2", StatValue = 3, Stat = "IBIT" }
        };

        public ObservableCollection<AllSystemsStatus> SDX3_List = new ObservableCollection<AllSystemsStatus>()
            {
              new AllSystemsStatus() { DeviceValue = 7 , Device = "SDX3", StatValue = 0, Stat = "FAIL" }
                    , new AllSystemsStatus() { DeviceValue = 7 , Device = "SDX3", StatValue = 1, Stat = "DEGRADED" }
                    , new AllSystemsStatus() { DeviceValue = 7 , Device = "SDX3", StatValue = 2, Stat = "PASSED" }
                    , new AllSystemsStatus() { DeviceValue = 7 , Device = "SDX3", StatValue = 3, Stat = "IBIT" }
        };

        public ObservableCollection<AllSystemsStatus> SATXXX_List = new ObservableCollection<AllSystemsStatus>()
            {
              new AllSystemsStatus() { DeviceValue = 8 , Device = "SATXXX", StatValue = 0, Stat = "FAIL" }
                    , new AllSystemsStatus() { DeviceValue = 8 , Device = "SATXXX", StatValue = 1, Stat = "DEGRADED" }
                    , new AllSystemsStatus() { DeviceValue = 8 , Device = "SATXXX", StatValue = 2, Stat = "PASSED" }
                    , new AllSystemsStatus() { DeviceValue = 8 , Device = "SATXXX", StatValue = 3, Stat = "IBIT" }
        };
    }
}
