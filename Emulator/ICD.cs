using System;
using System.Collections.Generic;
using System.Data;
using System.Text;

namespace EmuSample.Initialisation
{
    public enum LogType
    {
        SENT = 0,
        RECEIVED
    }

    public struct header
    {
        public int msg_id;
    };

    public struct data
    {
        public int veh_index;
        public bool position_valid;
        public double lat;
        public double lon;
        public bool heading_valid;
        public double heading;
        public bool attitude_valid;
        public double pitch;
        public double roll;
        public double mag_yaw;
        public bool altitude_valid;
        public int altitude;
        public bool velocity_valid;
        public double velocity;
    };

    // The data structure by which the server and the client interact with each other
    public class FlightData
    {
        public string Timestamp;
        public header header;
        public data message;

        // Default constructor
        public FlightData()
        {
            this.Timestamp = "";
            this.header.msg_id = 0;
            this.message.veh_index = 0;
            this.message.position_valid = true;
            this.message.lat = 0.0D;
            this.message.lon = 0.0D;
            this.message.heading_valid = true;
            this.message.heading = 0.0D;
            this.message.attitude_valid = true;
            this.message.pitch = 0.0D;
            this.message.roll = 0.0D;
            this.message.mag_yaw = 0.0D;
            this.message.altitude_valid = true;
            this.message.altitude = 0;
            this.message.velocity_valid = true;
            this.message.velocity = 0.0D;
        }

        // Converts the bytes into an object of type Data
        public FlightData(byte[] data)
        {
            // The first 4 bytes are for the Msg Header
            this.header.msg_id = BitConverter.ToInt32(data, 0);

            // The next 4 byes store the vehicle index
            this.message.veh_index = BitConverter.ToInt32(data, 4);

            // The next 1 byte store the position valid
            this.message.position_valid = BitConverter.ToBoolean(data, 8);

            // The next 8 bytes are for the latitude
            this.message.lat = BitConverter.ToDouble(data, 9);

            // The next 8 bytes are for the longtitude
            this.message.lon = BitConverter.ToDouble(data, 17);

            // The next 1 byte store the heading valid
            this.message.heading_valid = BitConverter.ToBoolean(data, 25);

            // The next 8 bytes are for the heading
            this.message.heading = BitConverter.ToDouble(data, 26);

            // The next 1 byte store the attitude valid
            this.message.attitude_valid = BitConverter.ToBoolean(data, 34);

            // The next 8 bytes are for the pitch
            this.message.pitch = BitConverter.ToDouble(data, 35);

            // The next 8 bytes are for the roll
            this.message.roll = BitConverter.ToDouble(data, 43);

            // The next 8 bytes are for the yaw
            this.message.mag_yaw = BitConverter.ToDouble(data, 51);

            // The next 1 byte store the altitude valid
            this.message.altitude_valid = BitConverter.ToBoolean(data, 59);

            // The next 4 bytes are for the altitude
            this.message.altitude = BitConverter.ToInt32(data, 60);

            // The next 1 byte store the velocity valid
            this.message.velocity_valid = BitConverter.ToBoolean(data, 64);

            // The next 8 bytes are for the velocity
            this.message.velocity = BitConverter.ToDouble(data, 65);
        }

        // Converts the Data structure into an array of bytes
        public byte[] ToByte()
        {
            List<byte> result = new List<byte>();

            //The first 4 bytes are for the Msg Header
            result.AddRange(BitConverter.GetBytes((int)this.header.msg_id));

            //The next 4 byes store the vehicle index
            result.AddRange(BitConverter.GetBytes((int)this.message.veh_index));

            //The next 1 byte store the position valid
            result.AddRange(BitConverter.GetBytes((bool)this.message.position_valid));

            //The next 8 bytes are for the latitude
            result.AddRange(BitConverter.GetBytes((double)this.message.lat));

            //The next 8 bytes are for the longtitude
            result.AddRange(BitConverter.GetBytes((double)this.message.lon));

            //The next 1 byte store the heading valid
            result.AddRange(BitConverter.GetBytes((bool)this.message.heading_valid));

            //The next 8 bytes are for the heading
            result.AddRange(BitConverter.GetBytes((double)this.message.heading));

            //The next 1 byte store the attitude valid
            result.AddRange(BitConverter.GetBytes((bool)this.message.attitude_valid));

            //The next 8 bytes are for the pitch
            result.AddRange(BitConverter.GetBytes((double)this.message.pitch));

            //The next 8 bytes are for the roll
            result.AddRange(BitConverter.GetBytes((double)this.message.roll));

            //The next 8 bytes are for the yaw
            result.AddRange(BitConverter.GetBytes((double)this.message.mag_yaw));

            //The next 1 byte store the altitude valid
            result.AddRange(BitConverter.GetBytes((bool)this.message.altitude_valid));

            //The next 4 bytes are for the altitude
            result.AddRange(BitConverter.GetBytes((int)this.message.altitude));

            //The next 1 byte store the velocity valid
            result.AddRange(BitConverter.GetBytes((bool)this.message.velocity_valid));

            //The next 8 bytes are for the velocity
            result.AddRange(BitConverter.GetBytes((double)this.message.velocity));

            return result.ToArray();
        }

        public string ToCsv()
        {
            StringBuilder sb = new StringBuilder();
            sb.Append("Timestamp: " + this.Timestamp + ",");
            sb.Append("Message Header ID: " + this.header.msg_id + ",");
            sb.Append("Vehicle Index: " + this.message.veh_index + ",");
            sb.Append("Position Validity: " + this.message.position_valid + ",");
            sb.Append("Latitude: " + this.message.lat + ",");
            sb.Append("Longitude: " + this.message.lon + ",");
            sb.Append("Heading Validity: " + this.message.heading_valid + ",");
            sb.Append("Heading: " + this.message.heading + ",");
            sb.Append("Attitude Validity: " + this.message.attitude_valid + ",");
            sb.Append("Pitch: " + this.message.pitch + ",");
            sb.Append("Roll: " + this.message.roll + ",");
            sb.Append("Magenetic Yaw: " + this.message.mag_yaw + ",");
            sb.Append("Altitude Validity: " + this.message.altitude_valid + ",");
            sb.Append("Altitude: " + this.message.altitude + ",");
            sb.Append("Velocity Validity: " + this.message.velocity_valid + ",");
            sb.Append("Velocity: " + this.message.velocity);
            return sb.ToString();
        }

        public static void add2List_flight(DataTable dataTable, List<FlightData> datalist)
        {
            for (int i = 0; i < dataTable.Rows.Count; i++)
            {
                FlightData fltdata = new FlightData();
                fltdata.Timestamp = dataTable.Rows[i][0].ToString();
                fltdata.header.msg_id = Convert.ToInt32(dataTable.Rows[i][1]);
                fltdata.message.veh_index = Convert.ToInt32(dataTable.Rows[i][2]);
                fltdata.message.position_valid = Convert.ToBoolean(dataTable.Rows[i][3]);
                fltdata.message.lat = Convert.ToDouble(dataTable.Rows[i][4]);
                fltdata.message.lon = Convert.ToDouble(dataTable.Rows[i][5]);
                fltdata.message.heading_valid = Convert.ToBoolean(dataTable.Rows[i][6]);
                fltdata.message.heading = Convert.ToDouble(dataTable.Rows[i][7]);
                fltdata.message.attitude_valid = Convert.ToBoolean(dataTable.Rows[i][8]);
                fltdata.message.pitch = Convert.ToDouble(dataTable.Rows[i][9]);
                fltdata.message.roll = Convert.ToDouble(dataTable.Rows[i][10]);
                fltdata.message.mag_yaw = Convert.ToDouble(dataTable.Rows[i][11]);
                fltdata.message.altitude_valid = Convert.ToBoolean(dataTable.Rows[i][12]);
                fltdata.message.altitude = Convert.ToInt32(dataTable.Rows[i][13]);
                fltdata.message.velocity_valid = Convert.ToBoolean(dataTable.Rows[i][14]);
                fltdata.message.velocity = Convert.ToDouble(dataTable.Rows[i][15]);
                datalist.Add(fltdata);
            }
        }
    }
}
