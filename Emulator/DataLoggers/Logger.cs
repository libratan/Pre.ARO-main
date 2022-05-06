using EmuSample.Initialisation;
using System;
using System.Collections.ObjectModel;
using System.IO;
using System.Text;
using System.Windows;

namespace EmuSample.DataLoggers
{
    public enum LogType
    {
        SENT = 0,
        RECEIVED
    }

    class Logger
    {
        public TextWriter stringWriter;
        private ObservableCollection<AllMessages> msg_carrier = new ObservableCollection<AllMessages>();

        public ObservableCollection<AllMessages> get_msgCarrier() // get_msgCarrier get-set 
        {
            return msg_carrier;
        }

        private void Log(AllMessages msg) // save to MessageLogs csv 
        {
            msg_carrier.Add(msg);

            try
            {
                stringWriter.WriteLine(msg.DateTime.ToString() + "," + msg.Type.ToString() + "," + msg.Text.ToString());
                stringWriter.Flush(); // Forces the writer to write to file immediately
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }

        public void Log(string msg, LogType type) // new object message, pass to Log to save-as-csv
        {
            AllMessages NewMsg = new AllMessages() { Type = type.ToString(), DateTime = DateTime.Now.ToString("MM/dd/yyyy HH:mm:ss:fff"), Text = msg };
            Log(NewMsg);
        }

        public virtual string ToCsv()
        {
            StringBuilder sb = new StringBuilder();
            return sb.ToString();
        }
    }
}
