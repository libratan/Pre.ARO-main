using System;

namespace EmuSample.ICDInit
{
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

    public class Positions
    {
        public string Timestamp;
        public header header;
        public data message;

        // Default constructor
        public Positions()
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
        public Positions(byte[] data)
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
    }
}
