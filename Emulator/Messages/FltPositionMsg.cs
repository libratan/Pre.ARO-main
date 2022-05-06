using System;
using System.Collections.Generic;
using EmuSample.ICDInit;

namespace EmuSample.Messages
{
    // Message positions_msg = new FltPositionMsg()
    // positions_msg.current_index = flightPositions.datalist[f_indexcount] - is this convention bad? *
    // positions_msg.ToBytes()

    class FltPositionMsg : Message
    {
        public Positions current_index = new Positions();

        public override byte[] ToBytes()
        {
            List<byte> result = new List<byte>();

            result.AddRange(BitConverter.GetBytes((int)current_index.header.msg_id));
            result.AddRange(BitConverter.GetBytes((int)current_index.message.veh_index));
            result.AddRange(BitConverter.GetBytes((bool)current_index.message.position_valid));
            result.AddRange(BitConverter.GetBytes((float)current_index.message.lat));
            result.AddRange(BitConverter.GetBytes((float)current_index.message.lon));
            result.AddRange(BitConverter.GetBytes((bool)current_index.message.heading_valid));
            result.AddRange(BitConverter.GetBytes((float)current_index.message.heading));
            result.AddRange(BitConverter.GetBytes((bool)current_index.message.attitude_valid));
            result.AddRange(BitConverter.GetBytes((float)current_index.message.pitch));
            result.AddRange(BitConverter.GetBytes((float)current_index.message.roll));
            result.AddRange(BitConverter.GetBytes((float)current_index.message.mag_yaw));
            result.AddRange(BitConverter.GetBytes((bool)current_index.message.altitude_valid));
            result.AddRange(BitConverter.GetBytes((int)current_index.message.altitude));
            result.AddRange(BitConverter.GetBytes((bool)current_index.message.velocity_valid));
            result.AddRange(BitConverter.GetBytes((float)current_index.message.velocity));

            return result.ToArray();
        }

        public override void GetMsg()
        {
            // functions 
        }
    }
}
