using EmuSample.Initialisation;
using LumenWorks.Framework.IO.Csv;
using System.Collections.Generic;
using System.Data;
using System.IO;

namespace EmuSample.Functions
{
    public static class BasicFunctions
    {
        public static void csvRead(DataTable dataTable, string filename)
        {
            using (var csvReader = new CsvReader(new StreamReader(File.OpenRead(@filename)), true))
            {
                dataTable.Load(csvReader);
            }
        }

        public static void add2List(DataTable dataTable, List<SearchParameters> datalist, List<string> combolist)
        {
            for (int i = 0; i < dataTable.Rows.Count; i++)
            {
                datalist.Add(new SearchParameters // dataset list
                {
                    Title = dataTable.Rows[i][0].ToString(),
                    Priority = dataTable.Rows[i][1].ToString(),
                    Information = dataTable.Rows[i][2].ToString()
                });

                combolist.Add(dataTable.Rows[i][0].ToString()); // combobox options
            }
        }
    }
}
