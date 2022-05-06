using EmuSample.Initialisation;
using LumenWorks.Framework.IO.Csv;
using System;
using System.Data;
using System.IO;

namespace EmuSample.DataTables
{
    interface DataSets
    {
        void csvRead();
        void add2List();
    }
}
