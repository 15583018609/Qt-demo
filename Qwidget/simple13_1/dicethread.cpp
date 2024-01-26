#include "dicethread.h"
#include <QTime>
DiceThread::DiceThread()
{

}

void DiceThread::diceBegin()
{
    m_Paused = false;
}

void DiceThread::dicePause()
{
    m_Paused = true;
}

void DiceThread::stopThread()
{
    m_stop = true;
}

void DiceThread::run()
{
    m_stop = false;
    m_seq = 0;
    qsrand(QTime::currentTime().second());
    while(!m_stop){
        if(!m_Paused){
            m_diceValue = qrand()%6+1;
            m_seq++;
            emit newValued(m_seq,m_diceValue);
        }
        msleep(500);
    }
    quit();
}
