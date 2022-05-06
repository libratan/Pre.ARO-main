using EmuSample.Connections;
using Framework.Execute;
using System.Collections.Generic;
using EmuSample.DataLoggers;
using System.Collections.ObjectModel;
using EmuSample.ICDInit;

namespace EmuSample.Messages
{
    using MsgList = List<Message>;
    using ConnectList = List<Connection>;

    // can place this in a consts class
    public enum ExecutionState
    {
        STOPPED = 0,
        RUNNING = 1,
        PAUSED = 2
    };

    public sealed class MsgExecutor : ThreadWorker
    {
        private ExecutionState m_state;

        private MsgList m_recvMsgList;
        private ConnectList m_connList;
        private Logger m_datalogger;

        public ObservableCollection<MsgData> get_msgCarrier()
        {
            return m_datalogger.get_msg_data();
        }

        public MsgExecutor(string path)
        {
            m_recvMsgList = new MsgList();
            m_connList = new ConnectList();
            m_datalogger = new Logger(path);

            SleepTimeMs = 10;//msec

            Start();
        }

        ~MsgExecutor()
        {
            if (m_recvMsgList != null)
                m_recvMsgList.Clear();

            m_recvMsgList = null;

            if (m_connList != null)
                m_connList.Clear();

            m_connList = null;

            m_datalogger = null;

        }

        public ExecutionState State
        {
            get
            { return m_state; }
            private set
            { m_state = value; }
        }

        public void AssociateMessage(Message msg, Connection connection)
        {
            if (msg != null)
            {
                m_recvMsgList.Add(msg);
                m_connList.Add(connection);
            }
            else
            {
            }
        }
        public override void Start()
        {
            StateTransition(ExecutionState.RUNNING);

            base.Start();
        }

        public override void Stop()
        {
            foreach (Message msg in m_recvMsgList)
                msg.State.RunState = RunState.STOPPED;

            // StateTransition(ExecutionState.STOPPED);
            // base.Stop();
        }

        public override void Execute()
        {
            if (m_state == ExecutionState.RUNNING)
            {
                ProcessSendMessages();
            }
        }

        private void ProcessSendMessages()
        {
            if (m_recvMsgList != null)
            {
                Message msg;
                Connection conn;

                for (int i = 0; i < m_recvMsgList.Count; i++)
                {
                    msg = m_recvMsgList[i];
                    conn = m_connList[i];

                    if (msg.State.IsTimeToProcess() && msg.State.IsRunning())
                    {
                        m_datalogger.LogRestore();

                        conn.Send(msg.GetMsg());
                        msg.State.UpdateTime();

                        m_datalogger.Log(msg.ToCsv(), LogType.SENT);
                        m_datalogger.DisplayLog(msg.ToDisplay());

                        // store back updated state
                        m_recvMsgList[i] = msg;
                    }
                }
            }
        }

        private void StateTransition(ExecutionState newState)
        {
            State = newState;
        }
    }
}