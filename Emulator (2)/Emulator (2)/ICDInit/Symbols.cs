using System;

namespace EmuSample.ICDInit
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

    public class Symbols
    {
        public string Timestamp;
        public header header;
        public S_data message;

        // Default constructor
        public Symbols()
        {
            this.Timestamp = "";
            this.header.msg_id = 0;
            this.message.sym_id = 0;
            this.message.SIDC = "";
            this.message.mod_count = 0;
            this.message.point_count = 0;
            this.message.lat = 0.0d;
            this.message.lon = 0.0f;
            this.message.altitude = 0.0f;
            this.message.magnification = 0.0f;
            this.message.orientation = 0.0f;
            this.message.move_enable = 0;
            this.message.move_angle = 0.0f;
        }

        // Converts the bytes into an object of type Data
        public Symbols(byte[] data)
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
    }
}
