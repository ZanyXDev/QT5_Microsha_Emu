#include "runner.h"

Runner::Runner(QObject *parent)
    : QObject(parent)
    , m_ticks(0)
    , m_paused(false)
{    
    connect(&m_timer,&QTimer::timeout,this,&Runner::execute);
}

Runner::~Runner()
{

}

void Runner::setCPU(i8080 *cpu, int freq)
{
    if (m_cpu != nullptr  && freq > 0)
    {
        m_cpu = cpu;
        setFreq(freq);
    }
}

int Runner::freq() const
{
    return m_freq;
}

void Runner::setFreq(int freq)
{
    m_freq = freq;
    ticks_per_ms = m_freq / 100;
}

void Runner::execute()
{
    if ( !m_paused )
    {
        m_ElapsedTime++;
        if ( m_ticks < ticks_per_ms)
        {
            m_ticks += m_cpu->instruction();
        }else
        {
            m_ticks = 0;
        }
        /**
         * @note every 1/60sec send signal updateScreen
         */
        if (m_ElapsedTime > 1000 / 60 )
        {
            emit updateScreen();
            m_ElapsedTime = 0;
        }
    }
}

bool Runner::isPaused() const
{
    return m_paused;
}

void Runner::setJump(quint16 adr)
{
    /// @note hardcore setup address to 0xF800
    adr = 0xF800;
    if (m_cpu != nullptr )
    {
        m_cpu->setJump(adr);
    }
}

void Runner::setPaused()
{
    m_paused = true;
}

void Runner::setResume()
{
    m_paused = false;
}

