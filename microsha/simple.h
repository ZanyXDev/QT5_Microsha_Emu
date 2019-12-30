#ifndef SIMPLE_H
#define SIMPLE_H

#include <QObject>

class Simple : public QObject
{
    Q_OBJECT

public:
    explicit Simple(QObject *parent = nullptr);
    void setA(int a);
    void setB(int b);
    int a();
    int b();

signals:

public slots:

private:
    int _a,_b;

};

#endif // SIMPLE_H



