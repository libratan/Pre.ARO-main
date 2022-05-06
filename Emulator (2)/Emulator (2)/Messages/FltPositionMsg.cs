using EmuSample.ICDInit;
using System;
using System.Collections.Generic;
using System.Globalization;

namespace EmuSample.Messages
{
    [Serializable]
    class FltPositionMsg : Message
    {
        public List<Positions> datalist = new List<Positions>();
        public Positions current_index = new Positions();
        public FltPositionMsg(string filename)
        {
            Filename = filename;
            LoadData();
            State.Frequency = initFreq();
        }

        public override byte[] ToBytes()
        {
            List<byte> result = new List<byte>();

            result.AddRange(BitConverter.GetBytes((int)current_index.header.msg_id));
            result.AddRange(BitConverter.GetBytes((int)current_index.message.veh_index));
            result.AddRange(BitConverter.GetBytes((bool)current_index.message.position_valid));
            result.AddRange(BitConverter.GetBytes((double)current_index.message.lat));
            result.AddRange(BitConverter.GetBytes((double)current_index.message.lon));
            result.AddRange(BitConverter.GetBytes((bool)current_index.message.heading_valid));
            result.AddRange(BitConverter.GetBytes((double)current_index.message.heading));
            result.AddRange(BitConverter.GetBytes((bool)current_index.message.attitude_valid));
            result.AddRange(BitConverter.GetBytes((double)current_index.message.pitch));
            result.AddRange(BitConverter.GetBytes((double)current_index.message.roll));
            result.AddRange(BitConverter.GetBytes((double)current_index.message.mag_yaw));
            result.AddRange(BitConverter.GetBytes((bool)current_index.message.altitude_valid));
            result.AddRange(BitConverter.GetBytes((int)current_index.message.altitude));
            result.AddRange(BitConverter.GetBytes((bool)current_index.message.velocity_valid));
            result.AddRange(BitConverter.GetBytes((double)current_index.message.velocity));

            return result.ToArray();
        }

        public override byte[] GetMsg()
        {
            current_index = datalist[MsgIndex];
            NextMsg();

            return ToBytes();
        }

        public override void NextMsg()
        {
            if(base.MsgIndex < (datalist.Count-1))
            {
                base.NextMsg();
            }
            else
            {
                base.ResetMsg();
            }
        }

        public override void LoadData()
        {
            base.LoadData();
            
            for (int i = 0; i < CsvTable.Rows.Count; i++)
            {
                Positions fltdata = new Positions();
                fltdata.Timestamp = CsvTable.Rows[i][0].ToString();
                fltdata.header.msg_id = Convert.ToInt32(CsvTable.Rows[i][1]);
                fltdata.message.veh_index = Convert.ToInt32(CsvTable.Rows[i][2]);
                fltdata.message.position_valid = Convert.ToBoolean(CsvTable.Rows[i][3]);
                fltdata.message.lat = Convert.ToDouble(CsvTable.Rows[i][4]);
                fltdata.message.lon = Convert.ToDouble(CsvTable.Rows[i][5]);
                fltdata.message.heading_valid = Convert.ToBoolean(CsvTable.Rows[i][6]);
                fltdata.message.heading = Convert.ToDouble(CsvTable.Rows[i][7]);
                fltdata.message.attitude_valid = Convert.ToBoolean(CsvTable.Rows[i][8]);
                fltdata.message.pitch = Convert.ToDouble(CsvTable.Rows[i][9]);
                fltdata.message.roll = Convert.ToDouble(CsvTable.Rows[i][10]);
                fltdata.message.mag_yaw = Convert.ToDouble(CsvTable.Rows[i][11]);
                fltdata.message.altitude_valid = Convert.ToBoolean(CsvTable.Rows[i][12]);
                fltdata.message.altitude = Convert.ToInt32(CsvTable.Rows[i][13]);
                fltdata.message.velocity_valid = Convert.ToBoolean(CsvTable.Rows[i][14]);
                fltdata.message.velocity = Convert.ToDouble(CsvTable.Rows[i][15]);
                datalist.Add(fltdata);
            }

        }

        public double initFreq()
        {
            string timestamp_1 = datalist[0].Timestamp;
            string timestamp_2 = datalist[1].Timestamp;
            string pattern = "MM/dd/yyyy HH:mm:ss.fff";
            DateTime parsedDate1;
            DateTime parsedDate2;

            DateTime.TryParseExact(timestamp_1, pattern, null, DateTimeStyles.None, out parsedDate1);
            DateTime.TryParseExact(timestamp_2, pattern, null, DateTimeStyles.None, out parsedDate2);

            // Use Time Difference for Period (ms)
            return (1000/parsedDate2.Subtract(parsedDate1).TotalMilliseconds);
        }

        public override string ToCsv()
        {
            Sb.Clear();
            Sb.Append("Timestamp: " + current_index.Timestamp + ",");
            Sb.Append("Message Header ID: " + current_index.header.msg_id + ",");
            Sb.Append("Vehicle Index: " + current_index.message.veh_index + ",");
            Sb.Append("Position Validity: " + current_index.message.position_valid + ",");
            Sb.Append("Latitude: " + current_index.message.lat + ",");
            Sb.Append("Longitude: " + current_index.message.lon + ",");
            Sb.Append("Heading Validity: " + current_index.message.heading_valid + ",");
            Sb.Append("Heading: " + current_index.message.heading + ",");
            Sb.Append("Attitude Validity: " + current_index.message.attitude_valid + ",");
            Sb.Append("Pitch: " + current_index.message.pitch + ",");
            Sb.Append("Roll: " + current_index.message.roll + ",");
            Sb.Append("Magenetic Yaw: " + current_index.message.mag_yaw + ",");
            Sb.Append("Altitude Validity: " + current_index.message.altitude_valid + ",");
            Sb.Append("Altitude: " + current_index.message.altitude + ",");
            Sb.Append("Velocity Validity: " + current_index.message.velocity_valid + ",");
            Sb.Append("Velocity: " + current_index.message.velocity);
            return Sb.ToString();
        }

        public override MsgData ToDisplay()
        {
            _NewMsg.Field1 = "Timestamp: " + current_index.Timestamp;
            _NewMsg.Field2 = "Message Header ID: " + current_index.header.msg_id.ToString();
            _NewMsg.Field3 = "Vehicle Index: " + current_index.message.veh_index.ToString();
            _NewMsg.Field4 = "Position Validity: " + current_index.message.position_valid.ToString();
            _NewMsg.Field5 = "Latitude: " + current_index.message.lat.ToString();
            _NewMsg.Field6 = "Longitude: " + current_index.message.lon.ToString();
            _NewMsg.Field7 = "Heading Validity: "+ current_index.message.heading_valid.ToString();
            _NewMsg.Field8 = "Heading: " + current_index.message.heading.ToString();
            _NewMsg.Field9 = "Attitude Validity: " + current_index.message.attitude_valid.ToString();
            _NewMsg.Field10 = "Pitch: " + current_index.message.pitch.ToString();
            _NewMsg.Field11 = "Roll: " + current_index.message.roll.ToString();
            _NewMsg.Field12 = "Magenetic Yaw: " + current_index.message.mag_yaw.ToString();
            _NewMsg.Field13 = "Altitude Validity: " + current_index.message.altitude_valid.ToString();
            _NewMsg.Field14 = "Altitude: " + current_index.message.altitude.ToString();
            _NewMsg.Field15 = "Velocity Validity: " + current_index.message.velocity_valid.ToString();
            _NewMsg.Field16 = "Velocity: " + current_index.message.velocity.ToString();

            return _NewMsg;
        }
    }
}
