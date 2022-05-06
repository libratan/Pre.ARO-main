using EmuSample.ICDInit;
using LumenWorks.Framework.IO.Csv;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.IO;
using System.Text;

namespace EmuSample.Messages
{
    public enum DataType
    {
        FltPositions = 0,
        FltSymbols,
        FltRoute,
        PolygonArea
    }

    public class Message
    {
        public int MsgID = 0;
        public MsgData _NewMsg = new MsgData();

        private int m_msgIndex = 0;
        private MessageState m_state = new MessageState();
        private string m_filename = "";
        private DataTable csvTable = new DataTable();
        private StringBuilder sb = new StringBuilder();

        public Message()
        {
        }

        public MessageState State
        {
            get => m_state;
            set => m_state = value;
        }

        public int MsgIndex
        {
            get
            {
                return m_msgIndex;
            }
        }

        public string Filename 
        { 
            get => m_filename; 
            set => m_filename = value; 
        }
        public DataTable CsvTable
        { 
            get => csvTable; 
            set => csvTable = value; 
        }
        public StringBuilder Sb 
        { 
            get => sb; 
            set => sb = value; 
        }
        public Action<object, PropertyChangedEventArgs> PropertyChanged { get; internal set; }

        public void GetMsgID()
        {
            // functions 
        }

        public virtual byte[] ToBytes()
        {
            // functions 
            List<byte> result = new List<byte>();
            return result.ToArray();
        }


        public virtual byte[] GetMsg()
        {
            NextMsg();
            return ToBytes();
        }

        public virtual void NextMsg()
        {
            m_msgIndex++;
        }

        public virtual void ResetMsg()
        {
            m_msgIndex = 0;
        }

        public virtual void LoadData()
        {
            using (var csvReader = new CsvReader(new StreamReader(File.OpenRead(@m_filename)), true))
            {
                csvTable.Load(csvReader);
            }
        }

        public virtual string ToCsv()
        {
            return sb.ToString();
        }

        public virtual MsgData ToDisplay()
        {
            return _NewMsg;
        }
    }
}
