using System.Xml;

namespace EmuSample.ICDInit
{
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

    public class AllData
    {
        public string DataType { get; set; }
        public string Value { get; set; }
    }
}
