using System;
using System.Collections.Generic;
using System.Data;
using System.Text;

namespace EmuSample.Initialisation
{
    public struct S_data
    {
        public int sym_id;
        public string SIDC;
        public int mod_count;
        public int point_count;
        public double lat;
        public double lon;
        public double altitude;
        public double magnification;
        public double orientation;
        public int move_enable;
        public double move_angle;
    };

    public class SymbolsData
    {
        public string Timestamp;
        public header header;
        public S_data message;

        // Default constructor
        public SymbolsData()
        {
            this.Timestamp = "";
            this.header.msg_id = 0;
            this.message.sym_id = 0;
            this.message.SIDC = "";
            this.message.mod_count = 0;
            this.message.point_count = 0;
            this.message.lat = 0.0d;
            this.message.lon = 0.0d;
            this.message.altitude = 0.0d;
            this.message.magnification = 0.0d;
            this.message.orientation = 0.0d;
            this.message.move_enable = 0;
            this.message.move_angle = 0.0d;
        }

        // Converts the bytes into an object of type Data
        public SymbolsData(byte[] data)
        {
            // The first 4 bytes are for the Msg Header (0-3)
            this.header.msg_id = BitConverter.ToInt32(data, 0);

            // The next 4 byes store the Symbold ID (4-7)
            this.message.sym_id = BitConverter.ToInt32(data, 4);

            // The next 16 bytes store the SIDC (8-23)
            this.message.SIDC = BitConverter.ToString(data, 24);

            // The next 4 bytes are for the Modifier Count (24-27)
            this.message.mod_count = BitConverter.ToInt32(data, 24);

            // The next 4 bytes are for the Point Count (28-31)
            this.message.point_count = BitConverter.ToInt32(data, 28);

            // The next 8 bytes are for the Latitude (32-39) 
            this.message.lat = BitConverter.ToDouble(data, 32);

            // The next 8 bytes are for the Longtitude (40-47)
            this.message.lon = BitConverter.ToDouble(data, 40);

            // The next 8 bytes are for the Altitude (48-55)
            this.message.altitude = BitConverter.ToDouble(data, 48);

            // The next 8 bytes are for the Magnification (56-63)
            this.message.magnification = BitConverter.ToDouble(data, 56);

            // The next 8 bytes are for the Orientation (64-71)
            this.message.orientation = BitConverter.ToDouble(data, 64);

            // The next 4 bytes are for the Direction of Movement Enable (72-75)
            this.message.move_enable = BitConverter.ToInt32(data, 72);

            // The next 8 bytes are for the Direction of Movement Angle (75-82)
            this.message.move_angle = BitConverter.ToDouble(data, 75);
        }

        // Converts the Data structure into an array of bytes
        public byte[] ToByte()
        {
            List<byte> result = new List<byte>();

            result.AddRange(BitConverter.GetBytes((int)this.header.msg_id));
            result.AddRange(BitConverter.GetBytes((int)this.message.sym_id));
            result.AddRange(Encoding.UTF8.GetBytes(this.message.SIDC));
            result.AddRange(BitConverter.GetBytes((int)this.message.mod_count));
            result.AddRange(BitConverter.GetBytes((int)this.message.point_count));
            result.AddRange(BitConverter.GetBytes((double)this.message.lat));
            result.AddRange(BitConverter.GetBytes((double)this.message.lon));
            result.AddRange(BitConverter.GetBytes((double)this.message.altitude));
            result.AddRange(BitConverter.GetBytes((double)this.message.magnification));
            result.AddRange(BitConverter.GetBytes((double)this.message.orientation));
            result.AddRange(BitConverter.GetBytes((int)this.message.move_enable));
            result.AddRange(BitConverter.GetBytes((double)this.message.move_angle));

            return result.ToArray();
        }

        public string ToCsv()
        {
            StringBuilder sb = new StringBuilder();
            sb.Append("Timestamp: " + this.Timestamp + ",");
            sb.Append("Message Header ID: " + this.header.msg_id + ",");
            sb.Append("Symbol ID: " + this.message.sym_id + ",");
            sb.Append("SIDC: " + this.message.SIDC + ",");
            sb.Append("Modifier Count: " + this.message.mod_count + ",");
            sb.Append("Point Count: " + this.message.point_count + ",");
            sb.Append("Latitude: " + this.message.lat + ",");
            sb.Append("Longitude: " + this.message.lon + ",");
            sb.Append("Altitude: " + this.message.altitude + ",");
            sb.Append("Magnification: " + this.message.magnification + ",");
            sb.Append("Orientation: " + this.message.orientation + ",");
            sb.Append("Movement Enable: " + this.message.move_enable + ",");
            sb.Append("Movement Angle: " + this.message.move_angle + ",");
            return sb.ToString();
        }

        public static void add2List_symbols(DataTable dataTable, List<SymbolsData> datalist)
        {
            for (int i = 0; i < dataTable.Rows.Count; i++)
            {
                SymbolsData symdata = new SymbolsData();
                symdata.Timestamp = dataTable.Rows[i][0].ToString();
                symdata.header.msg_id = Convert.ToInt32(dataTable.Rows[i][1]);
                symdata.message.sym_id = Convert.ToInt32(dataTable.Rows[i][2]);
                symdata.message.SIDC = dataTable.Rows[i][3].ToString() + char.MinValue;
                symdata.message.mod_count = Convert.ToInt32(dataTable.Rows[i][4]);
                symdata.message.point_count = Convert.ToInt32(dataTable.Rows[i][5]);
                symdata.message.lat = Convert.ToDouble(dataTable.Rows[i][6]);
                symdata.message.lon = Convert.ToDouble(dataTable.Rows[i][7]);
                symdata.message.altitude = Convert.ToDouble(dataTable.Rows[i][8]);
                symdata.message.magnification = Convert.ToDouble(dataTable.Rows[i][9]);
                symdata.message.orientation = Convert.ToDouble(dataTable.Rows[i][10]);
                symdata.message.move_enable = Convert.ToInt32(dataTable.Rows[i][11]);
                symdata.message.move_angle = Convert.ToDouble(dataTable.Rows[i][12]);
                datalist.Add(symdata);
            }
        }
    }
}