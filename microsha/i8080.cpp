#include "i8080.h"

i8080::i8080(QObject *parent) : QObject(parent)
{
    flags.carry_flag = 0;
    flags.sign_flag = 0;
    flags.zero_flag = 0;
    flags.half_carry_flag = 0;
    flags.parity_flag = 0;
    flags.unused1 =1;
    flags.unused3 =0;
    flags.unused5 =0;
    PC = 0;
    m_mem = nullptr;
}

i8080::~i8080()
{

}

quint8 i8080::instruction()
{
    return 0;
}

void i8080::setJump(quint16 adr)
{

}

void i8080::setMemory(Memory *mem)
{
    if (mem !=nullptr)
    {
        m_mem = mem;
    }
}


