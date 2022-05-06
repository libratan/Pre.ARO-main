using EmuSample.ICDInit;
using System;
using System.Collections.Generic;
using System.Text;

namespace EmuSample.Messages
{
    // Message symbols_msg = new FltDataMsg()
    // symbols_msg.current_index = flightSymbols.datalist[s_indexcount] - is this convention bad? *
    // symbols_msg.ToBytes()

    class FltSymbolsMsg : Message
    {
        public Symbols current_index = new Symbols();

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

        public override void GetMsg()
        {
            // functions 
        }
    }
}
