using EmuSample.Initialisation;
using System;
using System.Collections.ObjectModel;
using System.IO;
using System.Windows;

namespace EmuSample.Functions
{
    public class DataLogger
    {
        private TextWriter stringWriter;
        private ObservableCollection<AllMessages> msg_carrier = new ObservableCollection<AllMessages>();

        public ObservableCollection<AllMessages> get_msgCarrier() // get_msgCarrier get-set 
        {
            return msg_carrier;
        }

        public void set_msgCarrier(ObservableCollection<AllMessages> allMessages) // msg-carrier get-set
        {
            msg_carrier = allMessages;
        }

        public DataLogger(string path) // constructor with filepath set 
        {
            stringWriter = new StreamWriter(path, true);
        }

        ~DataLogger()
        {
            stringWriter.Close();
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

    }
}
