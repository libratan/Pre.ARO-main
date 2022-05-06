using System;
using System.Threading;

namespace Framework.Execute
{
    public abstract class ThreadWorker: IDisposable
    {
        private   Thread            m_worker;
        private   UInt32            m_sleepMs;
        protected volatile bool     m_workerAbort;
        protected volatile bool     m_disposed;        

        public ThreadWorker(bool autoStart = false, UInt32 sleepMs = 0)
        {
            m_worker        = null;
            m_workerAbort   = false;
            m_disposed      = false;
            m_sleepMs       = sleepMs;

            // create thread
            m_worker = new Thread(new ThreadStart(this.DoWork));
            m_worker.IsBackground = true;

            if (autoStart)
            {
                Start();
            }
        }

        ~ThreadWorker()
        {
            // Do not re-create Dispose clean-up code here.
            // Calling Dispose(false) is optimal in terms of
            // readability and maintainability.
            Dispose(false);
        }

        public UInt32 SleepTimeMs
        {
            get
            {
                return m_sleepMs;
            }
            set
            {
                m_sleepMs = value;
            }
        }

        public void Dispose()
        {
            Dispose(true);
            // This object will be cleaned up by the Dispose method.
            // Therefore, you should call GC.SupressFinalize to
            // take this object off the finalization queue
            // and prevent finalization code for this object
            // from executing a second time.
            GC.SuppressFinalize(this);
        }

        private void Dispose(bool disposing)
        {
            // Check to see if Dispose has already been called.
            if (!this.m_disposed)
            {
                // If disposing equals true, dispose all managed
                // and unmanaged resources.
                if (disposing)
                {
                    // Dispose resources
                    DisposeResources();
                }

                // Call the appropriate methods to clean up
                // unmanaged resources here.
                // If disposing is false,
                // only the following code is executed.
                m_worker = null;
                
                // Note disposing has been done.
                m_disposed = true;
            }
        }

        // for child classes to override to handle their resources disposal
        protected virtual void DisposeResources()
        {
        }

        private void DoWork()
        {
            while (!m_workerAbort)
            {
                Execute();

                if (m_sleepMs > 0)
                {
                    Thread.Sleep(Convert.ToInt32(m_sleepMs));
                }
            }
        }

        public virtual void Start()
        {
            if (m_worker != null)
            {
                m_worker.Start();
            }
        }

        public virtual void Stop()
        {
            if (m_worker != null)
            {
                m_workerAbort = true;
            }
        }

        // for child classes to override to execute
        public abstract void Execute();

    }
}
