using System.Collections.Generic;
using System.Xml;

namespace EmuSample.ICDInit
{
    enum MessageID
    {
        SYSTEMS_STATUS_ID = 201,
        EO_CMD_ID = 202,
        SYSTEM_MODE_ID = 203,
        MSG_CMD_ID = 212,
        IBIT_CMD_ID = 213,
        UNKNOWN_ID
    }

    public class XMLInfo
    {
        public XmlDocument xReader = new XmlDocument();
        public XmlNode MyNode;
        public XmlNode MyNodeType;
        public XmlNode MyNodeHost;
        public XmlNode MyNodePort;
        public string HostInfo;
        public int PortInfo;
    }

    public class AllMessages
    {
        public string Type { get; set; }
        public string DateTime { get; set; }
        public string Text { get; set; }
    }

    public class MsgData
    {
        public string Field1 { get; set; }
        public string Field2 { get; set; }
        public string Field3 { get; set; }
        public string Field4 { get; set; }
        public string Field5 { get; set; }
        public string Field6 { get; set; }
        public string Field7 { get; set; }
        public string Field8 { get; set; }
        public string Field9 { get; set; }
        public string Field10 { get; set; }
        public string Field11 { get; set; }
        public string Field12 { get; set; }
        public string Field13 { get; set; }
        public string Field14 { get; set; }
        public string Field15 { get; set; }
        public string Field16 { get; set; }
    }

    public class AllSystemsStatus
    {
        public int DeviceValue { get; set; }
        public string Device { get; set; }
        public int StatValue { get; set; }
        public string Stat { get; set; }
    }
}