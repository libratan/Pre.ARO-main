using System;

namespace EmuSample.Messages
{
    public enum RunState
    {
        STOPPED = 0,
        RUNNING = 1,
        PAUSED = 2
    };
    public class MessageState
    {
        private DateTime m_lastUpdate;
        private TimeSpan m_freqInterval;      // interval in Timespan
        private double m_frequency;
        private RunState m_runState;

        public MessageState()
        {
            m_lastUpdate = DateTime.Now;
        }

        public MessageState(double frequency)
        {
            m_lastUpdate = DateTime.Now;
            m_frequency = frequency;
            m_freqInterval = TimeSpan.FromMilliseconds(1000 / m_frequency);
        }

        public DateTime LastUpdateTime
        {
            get
            {
                return m_lastUpdate;
            }
            private set
            {
                m_lastUpdate = value;
            }
        }

        public TimeSpan Interval
        {
            get
            {
                return m_freqInterval;
            }
            private set
            {
                m_freqInterval = value;
            }
        }

        public double Frequency
        {
            get
            {
                return m_frequency;
            }
            set
            {
                m_frequency = value;
                m_freqInterval = TimeSpan.FromMilliseconds(1000 / m_frequency);
            }
        }

        public RunState RunState 
        { 
            get => m_runState; 
            set => m_runState = value; 
        }

        public bool IsTimeNowGreaterThanPrevPlusInterval(DateTime lastUpdate, TimeSpan interval)
        {
            bool ret = false;
            DateTime nextTime = (lastUpdate + interval);

            if (DateTime.Now >= nextTime)
            {
                ret = true;
            }
            else
            {
                ret = false;
            }

            return ret;
        }

        public bool IsTimeToProcess()
        {
            return IsTimeNowGreaterThanPrevPlusInterval(m_lastUpdate, m_freqInterval);
        }

        public void UpdateTime()
        {
            DateTime invokedTime = DateTime.Now;

            LastUpdateTime = invokedTime;
        }
        public bool IsRunning()
        {
            return (RunState == RunState.RUNNING);
        }
    }
}