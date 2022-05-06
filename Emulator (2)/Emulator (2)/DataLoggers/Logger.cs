using EmuSample.ICDInit;
using System;
using System.Collections.ObjectModel;
using System.IO;
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
        private AllMessages NewMsg = new AllMessages();

        private ObservableCollection<MsgData> msg_data = new ObservableCollection<MsgData>();

        public Logger(string path)
        {
            stringWriter = new StreamWriter(path, true);
        }

        ~Logger()
        {
            stringWriter.Close();
        }

        public ObservableCollection<AllMessages> get_msgCarrier() // get-set 
        {
            return msg_carrier;
        }

        public ObservableCollection<MsgData> get_msg_data() // get-set (for UI) 
        {
            return msg_data;
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
            NewMsg.Type = type.ToString();
            NewMsg.DateTime = DateTime.Now.ToString("MM/dd/yyyy HH:mm:ss:fff");
            NewMsg.Text = msg;
            Log(NewMsg);
        }

        public void DisplayLog(MsgData _NewMsg) // display msgdata to UI
        {
            Application.Current.Dispatcher.Invoke(delegate
            {
                msg_data.Add(_NewMsg);
            });
        }

        public void LogRestore() // new object message, pass to Log to save-as-csv
        {
            msg_carrier.Clear();

            if (msg_data != null)
            {
                Application.Current.Dispatcher.Invoke(delegate
                {
                    msg_data.Clear();
                });
            }
        }

        public virtual string ToCsv()
        {
            return null;
        }
    }
}
