using EmuSample.ICDInit;
using LumenWorks.Framework.IO.Csv;
using System;
using System.Collections.Generic;
using System.Data;
using System.IO;

namespace EmuSample.DataTables
{
    // Uses ICD Flight Data declarations 
    // FltData_Positions flightPositions = new FltData_Positions();
    // flightPositions.csvRead();
    // flightPositions.add2List();
    // access consolidated list using ' flightPositions.datalist '

    class FltData_Positions : DataSets
    {
        private string filename = "../../../Content/Files/ICD_Positions.csv";
        private DataTable csvTable = new DataTable();

        public List<Positions> datalist = new List<Positions>();

        public void csvRead()
        {
            using (var csvReader = new CsvReader(new StreamReader(File.OpenRead(@filename)), true))
            {
                csvTable.Load(csvReader);
            }
        }

        public void add2List()
        {
            for (int i = 0; i < csvTable.Rows.Count; i++)
            {
                Positions fltdata = new Positions();
                fltdata.Timestamp = csvTable.Rows[i][0].ToString();
                fltdata.header.msg_id = Convert.ToInt32(csvTable.Rows[i][1]);
                fltdata.message.veh_index = Convert.ToInt32(csvTable.Rows[i][2]);
                fltdata.message.position_valid = Convert.ToBoolean(csvTable.Rows[i][3]);
                fltdata.message.lat = Convert.ToSingle(csvTable.Rows[i][4]);
                fltdata.message.lon = Convert.ToSingle(csvTable.Rows[i][5]);
                fltdata.message.heading_valid = Convert.ToBoolean(csvTable.Rows[i][6]);
                fltdata.message.heading = Convert.ToSingle(csvTable.Rows[i][7]);
                fltdata.message.attitude_valid = Convert.ToBoolean(csvTable.Rows[i][8]);
                fltdata.message.pitch = Convert.ToSingle(csvTable.Rows[i][9]);
                fltdata.message.roll = Convert.ToSingle(csvTable.Rows[i][10]);
                fltdata.message.mag_yaw = Convert.ToSingle(csvTable.Rows[i][11]);
                fltdata.message.altitude_valid = Convert.ToBoolean(csvTable.Rows[i][12]);
                fltdata.message.altitude = Convert.ToInt32(csvTable.Rows[i][13]);
                fltdata.message.velocity_valid = Convert.ToBoolean(csvTable.Rows[i][14]);
                fltdata.message.velocity = Convert.ToSingle(csvTable.Rows[i][15]);
                datalist.Add(fltdata);
            }
        }
    }
}
