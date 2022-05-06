using EmuSample.Initialisation;
using EmuSample.UDP;
using System;
using System.Collections.Generic;
using System.Globalization;
using System.Timers;
using System.Windows;

namespace EmuSample.Functions
{
    public class Periodic
    {
        private int f_IndexCount;
        private int s_IndexCount;
        private static Timer f_Timer;
        private static Timer s_Timer;
        private DateTime parsedDate1 = new DateTime();
        private DateTime parsedDate2 = new DateTime();
        private UDPSocket cm = new UDPSocket();
        private DataLogger DL = new DataLogger("../../../Content/Files/Msg2DMM.csv");

        public List<FlightData> flightdata = new List<FlightData>();
        public List<SymbolsData> symboldata = new List<SymbolsData>();

        public Periodic()
        {
            f_Timer = new Timer();
            f_Timer.AutoReset = true;
            f_Timer.Elapsed += f_timerSend;

            s_Timer = new Timer();
            s_Timer.AutoReset = true;
            s_Timer.Elapsed += s_timerSend;
        }

        ~Periodic()
        {
            f_Timer.Dispose();
            s_Timer.Dispose();
        }

        public void connectDMM(string address, int port)
        {
            cm.ClientMulti(address, port);
        }

        public void stopSend()
        {
            f_Timer.Stop();
            s_Timer.Stop();
            DL.get_msgCarrier().Clear();
        }

        /*private ObservableCollection<AllData> ownship_data = new ObservableCollection<AllData>();
        public ObservableCollection<AllData> get_ownship() // get_msgCarrier get-set 
        {
            return ownship_data;
        }
        public void set_ownship(ObservableCollection<AllData> allData) // msg-carrier get-set
        {
            ownship_data = allData;
        }*/

        public void f_InitTimer() // timer for DMM sending interval 
        {
            // Datetime Converter for Period 
            f_IndexCount = 0;
            string timestamp_1 = flightdata[0].Timestamp;
            string timestamp_2 = flightdata[1].Timestamp;
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
            f_Timer.Interval = parsedDate2.Subtract(parsedDate1).TotalMilliseconds;
            f_Timer.Start();
        }

        private void f_timerSend(object sender, ElapsedEventArgs e) // timer action for DMM sending interval 
        {
            if (f_IndexCount < flightdata.Count)
            {
                // Send to DMM 
                cm.SendArray(flightdata[f_IndexCount]);

                // Update Periodic Display 
                // flightdata[IndexCount].PeriodicView(); - not working yet * 
                /* AllData NewMsg = new AllData() { DataType = "Timestamp", Value = flightdata[f_IndexCount].Timestamp.ToString() };
                ownship_data.Add(NewMsg); */

                // Log Info 
                DL.Log(flightdata[f_IndexCount].ToCsv(), LogType.SENT); // append as string, pass to datalogger 

                // Move to next row 
                f_IndexCount++;
            }
            else
            {
                f_IndexCount = 0; // re-initialise count - currently used for looping
            }
        }

        public void s_InitTimer() // timer for DMM sending interval 
        {
            // Datetime Converter for Period 
            s_IndexCount = 0;
            string timestamp_1 = symboldata[0].Timestamp;
            string timestamp_2 = symboldata[1].Timestamp;
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
            s_Timer.Interval = parsedDate2.Subtract(parsedDate1).TotalMilliseconds;
            s_Timer.Start();
        }

        private void s_timerSend(object sender, ElapsedEventArgs e) // timer action for DMM sending interval 
        {
            if (s_IndexCount < symboldata.Count)
            {
                // Send to DMM 
                cm.SendArray(symboldata[s_IndexCount]);

                // Update Periodic Display 
                // flightdata[IndexCount].PeriodicView(); - not working yet * 

                // Log Info 
                DL.Log(symboldata[s_IndexCount].ToCsv(), LogType.SENT); // append as string, pass to datalogger 

                // Move to next row 
                s_IndexCount++;
            }
            else
            {
                s_IndexCount = 0; // re-initialise count - currently used for looping
            }
        }
    }
}
