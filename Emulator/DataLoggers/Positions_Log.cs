using EmuSample.ICDInit;
using System.IO;
using System.Text;

namespace EmuSample.DataLoggers
{
    // Logger positions_log = new Positions_Log()
    // positions_log.current_index = flightPositions.datalist[f_indexcount] - is this convention bad? *
    // positions_log.ToCsv()

    class Positions_Log : Logger
    {
        public Positions current_index = new Positions();

        public Positions_Log(string path) // constructor with filepath set 
        {
            stringWriter = new StreamWriter(path, true);
        }

        ~Positions_Log()
        {
            stringWriter.Close();
        }

        public override string ToCsv()
        {
            StringBuilder sb = new StringBuilder();
            sb.Append("Timestamp: " + current_index.Timestamp + ",");
            sb.Append("Message Header ID: " + current_index.header.msg_id + ",");
            sb.Append("Vehicle Index: " + current_index.message.veh_index + ",");
            sb.Append("Position Validity: " + current_index.message.position_valid + ",");
            sb.Append("Latitude: " + current_index.message.lat + ",");
            sb.Append("Longitude: " + current_index.message.lon + ",");
            sb.Append("Heading Validity: " + current_index.message.heading_valid + ",");
            sb.Append("Heading: " + current_index.message.heading + ",");
            sb.Append("Attitude Validity: " + current_index.message.attitude_valid + ",");
            sb.Append("Pitch: " + current_index.message.pitch + ",");
            sb.Append("Roll: " + current_index.message.roll + ",");
            sb.Append("Magenetic Yaw: " + current_index.message.mag_yaw + ",");
            sb.Append("Altitude Validity: " + current_index.message.altitude_valid + ",");
            sb.Append("Altitude: " + current_index.message.altitude + ",");
            sb.Append("Velocity Validity: " + current_index.message.velocity_valid + ",");
            sb.Append("Velocity: " + current_index.message.velocity);
            return sb.ToString();
        }
    }
}
