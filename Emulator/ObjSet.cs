using System.Collections.Generic;
using System.Xml;

namespace EmuSample.Initialisation
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

    public class SearchParameters
    {
        public string Title { get; set; }
        public string Priority { get; set; }
        public string Information { get; set; }

        public List<SearchParameters> searchParameters_A { get; set; }
        public List<SearchParameters> searchParameters_P { get; set; }
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
