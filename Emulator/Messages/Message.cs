using System;
using System.Collections.Generic;
using System.Text;

namespace EmuSample.Messages
{
    public enum LogType
    {
        FltPositions = 0,
        FltSymbols,
        FltRoute,
        PolygonArea
    }

    class Message
    {
        public string Timestamp = "";
        public int MsgID = 0;

        public void GetTimeStamp()
        {
            // functions 
        }

        public void GetMsgID()
        {
            // functions 
        }

        public virtual byte[] ToBytes()
        {
            // functions 
            List<byte> result = new List<byte>();
            return result.ToArray();
        }


        public virtual void GetMsg()
        {
            // functions 
        }
    }
}
