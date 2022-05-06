using EmuSample.ICDInit;
using LumenWorks.Framework.IO.Csv;
using System;
using System.Collections.Generic;
using System.Data;
using System.IO;

namespace EmuSample.DataTables
{
    // Uses ICD Flight Data declarations 
    // DataTables flightSymbols = new FltData_Symbols();
    // flightSymbols.csvRead();
    // flightSymbols.add2List();
    // access consolidated list using ' flightSymbols.datalist '

    class FltData_Symbols : DataSets
    {
        private string filename = "../../../Content/Files/ICD_Symbols.csv";
        private DataTable csvTable = new DataTable();

        public List<Symbols> datalist = new List<Symbols>();

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
                Symbols symdata = new Symbols();
                symdata.Timestamp = csvTable.Rows[i][0].ToString();
                symdata.header.msg_id = Convert.ToInt32(csvTable.Rows[i][1]);
                symdata.message.sym_id = Convert.ToInt32(csvTable.Rows[i][2]);
                symdata.message.SIDC = csvTable.Rows[i][3].ToString() + char.MinValue;
                symdata.message.mod_count = Convert.ToInt32(csvTable.Rows[i][4]);
                symdata.message.point_count = Convert.ToInt32(csvTable.Rows[i][5]);
                symdata.message.lat = Convert.ToDouble(csvTable.Rows[i][6]);
                symdata.message.lon = Convert.ToDouble(csvTable.Rows[i][7]);
                symdata.message.altitude = Convert.ToDouble(csvTable.Rows[i][8]);
                symdata.message.magnification = Convert.ToDouble(csvTable.Rows[i][9]);
                symdata.message.orientation = Convert.ToDouble(csvTable.Rows[i][10]);
                symdata.message.move_enable = Convert.ToInt32(csvTable.Rows[i][11]);
                symdata.message.move_angle = Convert.ToDouble(csvTable.Rows[i][12]);
                datalist.Add(symdata);
            }
        }
    }
}
