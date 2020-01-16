#ifndef RUNNER_H
#define RUNNER_H

#include <QObject>
#include <QTimer>
#include "i8080.h"

class Runner : public QObject
{
    Q_OBJECT
public:
    explicit Runner(QObject *parent = nullptr);
    ~Runner();
    void setCPU(i8080 *cpu = nullptr,int freq = 0);
    void setJump(quint16 adr);
    int freq() const;
    bool isPaused() const;

signals:
    void updateScreen();

public slots:
    void execute();
    void setPaused();
    void setResume();

private :
    int m_freq;
    int m_ticks;
    bool m_paused;
    double ticks_per_ms;
    quint32 m_ElapsedTime;

    i8080 * m_cpu;
    QTimer m_timer;

    void setFreq(int freq);
};

#endif // RUNNER_H
