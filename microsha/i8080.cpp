#include "i8080.h"

i8080::i8080(QObject *parent) : QObject(parent)
{

}

void i8080::init()
{
    flags.carry_flag = 0;
    flags.sign_flag = 0;
    flags.zero_flag = 0;
    flags.half_carry_flag = 0;
    flags.parity_flag = 0;
    flags.unused1 =1;
    flags.unused3 =0;
    flags.unused5 =0;
    PC = 0xF800;
}

void i8080::execute()
{

}
