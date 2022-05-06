using System;
using System.Collections.Generic;
using System.Text;

namespace EmuSample.Messages
{
    class PolygonAreaMsg : Message
    {
        // private string msg = "";

        public override byte[] ToBytes()
        {
            // functions 
            List<byte> result = new List<byte>();
            return result.ToArray();
        }

        public override void GetMsg()
        {
            // functions 
        }
    }
}
