using EmuSample.ICDInit;
using System.IO;
using System.Text;

namespace EmuSample.DataLoggers
{
    // Logger symbols_log = new Symbols_Log()
    // symbols_log.current_index = flightSymbols.datalist[s_indexcount] - is this convention bad? *
    // symbols_log.ToCsv()

    class Symbols_Log : Logger
    {
        public Symbols current_index = new Symbols();

        public Symbols_Log(string path) // constructor with filepath set 
        {
            stringWriter = new StreamWriter(path, true);
        }

        ~Symbols_Log()
        {
            stringWriter.Close();
        }

        public override string ToCsv()
        {
            StringBuilder sb = new StringBuilder();
            sb.Append("Timestamp: " + current_index.Timestamp + ",");
            sb.Append("Message Header ID: " + current_index.header.msg_id + ",");
            sb.Append("Symbol ID: " + current_index.message.sym_id + ",");
            sb.Append("SIDC: " + current_index.message.SIDC + ",");
            sb.Append("Modifier Count: " + current_index.message.mod_count + ",");
            sb.Append("Point Count: " + current_index.message.point_count + ",");
            sb.Append("Latitude: " + current_index.message.lat + ",");
            sb.Append("Longitude: " + current_index.message.lon + ",");
            sb.Append("Altitude: " + current_index.message.altitude + ",");
            sb.Append("Magnification: " + current_index.message.magnification + ",");
            sb.Append("Orientation: " + current_index.message.orientation + ",");
            sb.Append("Movement Enable: " + current_index.message.move_enable + ",");
            sb.Append("Movement Angle: " + current_index.message.move_angle + ",");
            return sb.ToString();
        }
    }
}
