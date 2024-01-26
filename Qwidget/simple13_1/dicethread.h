#ifndef DICETHREAD_H
#define DICETHREAD_H

#include <QThread>

class DiceThread : public QThread
{
    Q_OBJECT
public:
    explicit DiceThread();
    void diceBegin();
    void dicePause();
    void stopThread();
signals:
    void newValued(int seq,int diceValue);
private:
    int m_seq =0;
    int m_diceValue;
    bool m_Paused = true;
    bool m_stop=false;

protected:
    void run() Q_DECL_OVERRIDE;

};

#endif // DICETHREAD_H
