using EmuSample.ICDInit;
using System;
using System.Collections.Generic;

namespace EmuSample.Messages
{
    class SystemsStatusMsg : Message
    {
        public SystemsStatus current_index = new SystemsStatus();
        public SystemsStatusMsg(string filename)
        {
            Filename = filename;
            LoadData();
            State.Frequency = 1; // 1 Hz
        }

        public override void LoadData()
        {
            current_index.header.msg_id = (int)MessageID.SYSTEMS_STATUS_ID;
        }

        public override byte[] GetMsg()
        {
            return ToBytes();
        }

        public override byte[] ToBytes()
        {
            List<byte> result = new List<byte>();

            result.AddRange(BitConverter.GetBytes((int)current_index.header.msg_id));
            result.AddRange(BitConverter.GetBytes((int)current_index.message.system1));
            result.AddRange(BitConverter.GetBytes((int)current_index.message.status1));
            result.AddRange(BitConverter.GetBytes((int)current_index.message.system2));
            result.AddRange(BitConverter.GetBytes((int)current_index.message.status2));
            result.AddRange(BitConverter.GetBytes((int)current_index.message.system3));
            result.AddRange(BitConverter.GetBytes((int)current_index.message.status3));
            result.AddRange(BitConverter.GetBytes((int)current_index.message.system4));
            result.AddRange(BitConverter.GetBytes((int)current_index.message.status4));
            result.AddRange(BitConverter.GetBytes((int)current_index.message.system5));
            result.AddRange(BitConverter.GetBytes((int)current_index.message.status5));
            result.AddRange(BitConverter.GetBytes((int)current_index.message.system6));
            result.AddRange(BitConverter.GetBytes((int)current_index.message.status6));
            result.AddRange(BitConverter.GetBytes((int)current_index.message.system7));
            result.AddRange(BitConverter.GetBytes((int)current_index.message.status7));
            result.AddRange(BitConverter.GetBytes((int)current_index.message.system8));
            result.AddRange(BitConverter.GetBytes((int)current_index.message.status8));
            result.AddRange(BitConverter.GetBytes((int)current_index.message.system9));
            result.AddRange(BitConverter.GetBytes((int)current_index.message.status9));

            return result.ToArray();
        }
        public override string ToCsv()
        {
            Sb.Clear();
            Sb.Append("BOXA: " + current_index.message.status1 + ",");
            Sb.Append("DISPLAY1: " + current_index.message.status2 + ",");
            Sb.Append("DISPLAY2: " + current_index.message.status3 + ",");
            Sb.Append("BOXB1: " + current_index.message.status4 + ",");
            Sb.Append("BOXB2: " + current_index.message.status5 + ",");
            Sb.Append("SDX1: " + current_index.message.status6 + ",");
            Sb.Append("SDX2: " + current_index.message.status7 + ",");
            Sb.Append("SDX3: " + current_index.message.status8 + ",");
            Sb.Append("SATXXX: " + current_index.message.status9);
            return Sb.ToString();
        }   

        public override MsgData ToDisplay()
        {
            _NewMsg.Field1 = "BOXA: " + current_index.message.status1;
            _NewMsg.Field2 = "DISPLAY1: " + current_index.message.status2;
            _NewMsg.Field3 = "DISPLAY2: " + current_index.message.status3;
            _NewMsg.Field4 = "BOXB1: " + current_index.message.status4;
            _NewMsg.Field5 = "BOXB2: " + current_index.message.status5;
            _NewMsg.Field6 = "SDX1: " + current_index.message.status6;
            _NewMsg.Field7 = "SDX2: " + current_index.message.status7;
            _NewMsg.Field8 = "SDX3: " + current_index.message.status8;
            _NewMsg.Field9 = "SATXXX: " + current_index.message.status9;

            return _NewMsg;
        }
    }
}









