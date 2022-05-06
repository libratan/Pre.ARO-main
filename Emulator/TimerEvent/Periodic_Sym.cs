using EmuSample.DataLoggers;
using EmuSample.ICDInit;
using EmuSample.Messages;
using System;
using System.Collections.Generic;
using System.Globalization;
using System.Timers;
using System.Windows;

namespace EmuSample.TimerEvent
{
    class Periodic_Sym : TimerSet
    {
        private FltSymbolsMsg dataitem = new FltSymbolsMsg();
        private Symbols_Log datalog = new Symbols_Log("../../../Content/Files/Msg2DMM.csv");

        public List<Symbols> datalist = new List<Symbols>();

        public Periodic_Sym()
        {
            timer = new Timer();
            timer.AutoReset = true;
            timer.Elapsed += timerSend;
        }
        ~Periodic_Sym()
        {
            timer.Dispose();
        }

        public override void stopSend()
        {
            timer.Stop();
        }

        public override void initTimer()
        {
            // Datetime Converter for Period 
            IndexCount = 0;
            string timestamp_1 = datalist[0].Timestamp;
            string timestamp_2 = datalist[1].Timestamp;
            string pattern = "MM/dd/yyyy HH:mm:ss.fff";

            try
            {
                DateTime.TryParseExact(timestamp_1, pattern, null, DateTimeStyles.None, out parsedDate1);
                DateTime.TryParseExact(timestamp_2, pattern, null, DateTimeStyles.None, out parsedDate2);
            }
            catch (Exception e)
            {
                MessageBox.Show(e.Message);
            }

            // Use Time Difference for Period (ms)
            timer.Interval = parsedDate2.Subtract(parsedDate1).TotalMilliseconds;
            timer.Start();
        }

        public override void timerSend(object sender, ElapsedEventArgs e)
        {
            dataitem.current_index = datalist[IndexCount];
            datalog.current_index = datalist[IndexCount];

            if (IndexCount < (datalist.Count - 1))
            {
                // Send to DMM 
                cm.SendArray(dataitem);

                // Log Info 
                datalog.Log(datalog.ToCsv(), DataLoggers.LogType.SENT);

                // Move to next row 
                IndexCount++;
            }
            else
            {
                IndexCount = 0; // re-initialise count - currently used for looping
            }
        }
    }
}
