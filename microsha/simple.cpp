#include "simple.h"

Simple::Simple(QObject *parent) : QObject(parent)
{

}

void Simple::setA(int a)
{
    _a = a;
}

void Simple::setB(int b)
{
    _b = b;
}

int Simple::a()
{
    return _a;
}

int Simple::b()
{
    return _b;
}
