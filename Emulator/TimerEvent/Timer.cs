using EmuSample.Connections;
using System;
using System.Timers;

namespace EmuSample.TimerEvent
{
    abstract class TimerSet
    {
        public int IndexCount;
        public static Timer timer;
        public DateTime parsedDate1 = new DateTime();
        public DateTime parsedDate2 = new DateTime();
        public UDPSocket cm = new UDPSocket();

        public abstract void initTimer();
        public abstract void timerSend(object sender, ElapsedEventArgs e);
        public abstract void stopSend();
    }
}
