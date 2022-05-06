using EmuSample.ICDInit;
using System;
using System.Collections.Generic;
using System.Globalization;
using System.Text;

namespace EmuSample.Messages
{
    [Serializable]
    class FltSymbolsMsg : Message
    {
        public Symbols current_index = new Symbols();
        public List<Symbols> datalist = new List<Symbols>();
        public FltSymbolsMsg(string filename)
        {
            Filename = filename;
            LoadData();
            State.Frequency = initFreq();
        }

        public override byte[] ToBytes()
        {
            List<byte> result = new List<byte>();

            result.AddRange(BitConverter.GetBytes((int)current_index.header.msg_id));
            result.AddRange(BitConverter.GetBytes((int)current_index.message.sym_id));
            result.AddRange(Encoding.UTF8.GetBytes(current_index.message.SIDC));
            result.AddRange(BitConverter.GetBytes((int)current_index.message.mod_count));
            result.AddRange(BitConverter.GetBytes((int)current_index.message.point_count));
            result.AddRange(BitConverter.GetBytes((double)current_index.message.lat));
            result.AddRange(BitConverter.GetBytes((double)current_index.message.lon));
            result.AddRange(BitConverter.GetBytes((double)current_index.message.altitude));
            result.AddRange(BitConverter.GetBytes((double)current_index.message.magnification));
            result.AddRange(BitConverter.GetBytes((double)current_index.message.orientation));
            result.AddRange(BitConverter.GetBytes((int)current_index.message.move_enable));
            result.AddRange(BitConverter.GetBytes((double)current_index.message.move_angle));

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
            if (base.MsgIndex < (datalist.Count - 1))
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
                Symbols symdata = new Symbols();
                symdata.Timestamp = CsvTable.Rows[i][0].ToString();
                symdata.header.msg_id = Convert.ToInt32(CsvTable.Rows[i][1]);
                symdata.message.sym_id = Convert.ToInt32(CsvTable.Rows[i][2]);
                symdata.message.SIDC = CsvTable.Rows[i][3].ToString() + char.MinValue;
                symdata.message.mod_count = Convert.ToInt32(CsvTable.Rows[i][4]);
                symdata.message.point_count = Convert.ToInt32(CsvTable.Rows[i][5]);
                symdata.message.lat = Convert.ToDouble(CsvTable.Rows[i][6]);
                symdata.message.lon = Convert.ToDouble(CsvTable.Rows[i][7]);
                symdata.message.altitude = Convert.ToDouble(CsvTable.Rows[i][8]);
                symdata.message.magnification = Convert.ToDouble(CsvTable.Rows[i][9]);
                symdata.message.orientation = Convert.ToDouble(CsvTable.Rows[i][10]);
                symdata.message.move_enable = Convert.ToInt32(CsvTable.Rows[i][11]);
                symdata.message.move_angle = Convert.ToDouble(CsvTable.Rows[i][12]);
                datalist.Add(symdata);
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
            Sb.Append("Symbol ID: " + current_index.message.sym_id + ",");
            Sb.Append("SIDC: " + current_index.message.SIDC + ",");
            Sb.Append("Modifier Count: " + current_index.message.mod_count + ",");
            Sb.Append("Point Count: " + current_index.message.point_count + ",");
            Sb.Append("Latitude: " + current_index.message.lat + ",");
            Sb.Append("Longitude: " + current_index.message.lon + ",");
            Sb.Append("Altitude: " + current_index.message.altitude + ",");
            Sb.Append("Magnification: " + current_index.message.magnification + ",");
            Sb.Append("Orientation: " + current_index.message.orientation + ",");
            Sb.Append("Movement Enable: " + current_index.message.move_enable + ",");
            Sb.Append("Movement Angle: " + current_index.message.move_angle + ",");
            return Sb.ToString();
        }

        public override MsgData ToDisplay()
        {
            _NewMsg.Field1 = "Timestamp: " + current_index.Timestamp;
            _NewMsg.Field2 = "Message Header ID: " + current_index.header.msg_id.ToString();
            _NewMsg.Field3 = "Symbol ID: " + current_index.message.sym_id.ToString();
            _NewMsg.Field4 = "SIDC: " + current_index.message.SIDC.ToString();
            _NewMsg.Field5 = "Modifier Count: " + current_index.message.mod_count.ToString();
            _NewMsg.Field6 = "Point Count: " + current_index.message.point_count.ToString();
            _NewMsg.Field7 = "Latitude: " + current_index.message.lat.ToString();
            _NewMsg.Field8 = "Longitude: " + current_index.message.lon.ToString();
            _NewMsg.Field9 = "Altitude: " + current_index.message.altitude.ToString();
            _NewMsg.Field10 = "Magnification: " + current_index.message.magnification.ToString();
            _NewMsg.Field11 = "Orientation: " + current_index.message.orientation.ToString();
            _NewMsg.Field12 = "Movement Enable: " + current_index.message.move_enable.ToString();
            _NewMsg.Field13 = "Movement Angle: " + current_index.message.move_angle.ToString();

            return _NewMsg;
        }
    }
}
