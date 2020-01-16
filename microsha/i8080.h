#ifndef I8080_H
#define I8080_H

#include <QObject>
#include "memory.h"

typedef union {
    struct {
        quint8 l, h;
    } b;
    quint16 w;
} reg_pair;

/**
  * @todo change struct to Bitset?
  *
  * QBitArray bytesToBits(const QByteArray &bytes) const
  *  {
  *  QBitArray bits;
  *  bits.resize(bytes.size()*8);
  *  // Convert from QByteArray to QBitArray
  *     for(int i=0; i<bytes.count(); ++i)
  *     {
  *        for(int b=0; b<8; ++b)
  *        {
  *           bits.setBit(i*8+b, bytes.at(i)&(1<<(7-b)));
  *        }
  *     }
  *      return bits;
  *  }
  * QByteArray bitsToBytes(const QBitArray &bits) const
  * {
  *     QByteArray bytes;
  *     bytes.resize(bits.size()/8);
  *     // Convert from QBitArray to QByteArray
  *     for(int b=0; b<bits.count(); ++b)
  *     {
  *          bytes[b/8] = (bytes.at(b/8) | ((bits[b]?1:0)<<(b%8)));
  *      }
  *     return bytes;
  * }
  */
typedef struct {
    quint8 carry_flag; // C - Перенос
    quint8 unused1;
    quint8 parity_flag; // P- Четность
    quint8 unused3;
    quint8 half_carry_flag; // AC - Вспомогательный перенос
    quint8 unused5;
    quint8 zero_flag; // Z- Ноль
    quint8 sign_flag; // S- Знак
} flag_reg;


class i8080 : public QObject
{
    Q_OBJECT
public:
    explicit i8080(QObject *parent = nullptr);
    ~i8080();
    void setJump(quint16 adr);
    void setMemory(Memory *mem);
signals:
    quint8 executeDuration();

public slots:
    /**
     * @brief instruction() execute next instruction and
     * @return how cpu_ticks duration's
     */
    quint8 instruction();

private:
    enum{
        F_CARRY  = 0x01,
        F_UN1    = 0x02,
        F_PARITY = 0x04,
        F_UN3    = 0x08,
        F_HCARRY = 0x10,
        F_UN5    = 0x20,
        F_ZERO   = 0x40,
        F_NEG    = 0x80
    };
    /**
     * @brief регистр флагов. Непосредственно недоступен программисту,
     * но его в составе PSW можно сохранить в стеке, а потом извлечь
     * в другую регистровую пару, если нужно специально установить или
     * проверить нужные флаги.
     */
    flag_reg flags;

   /**
    * @brief af Пара регистров A + флаги образуют 16 разрядный регистр,
    * именуемый PSW, причём A занимает старший байт слова, а флаги — младший.
    */
    reg_pair AF;
    /**
     * @brief BC регистровая пара
     */
    reg_pair BC;
    /**
     * @brief DE часто используемая регистровая пара, поскольку имеется
     * команда обмена содержимым между парами HL и DE .
     */
    reg_pair DE;
    /**
     * @brief HL регистровая пара, состоящая из двух 8-разрядных регистров
     * ( H – старший регистр, L -- младший), используется для
     * косвенно-регистровой адресации 64 Кбайт памяти.
     */
    reg_pair HL;
    /**
     * @brief SP указатель стека автоматически инкрементируется на 2 при записи
     *  пары регистров в стек (отдельный 8-разрядный регистр в стек записать
     * нельзя, только парами) и декрементируется при извлечении из регистровой
     * пары из стека.
     */
    quint16 SP;
    /**
     * @brief PC счётчик команд, содержит адрес очередной исполняемой команды.
     */
    quint16 PC;

    quint16 IFF;
    quint16 last_pc;
    /**
     * @brief cpu_cycles количество машинных циклов затрачиваемых на команду
     */
    quint16 cpu_cycles;
    Memory *m_mem;
};

#endif // I8080_H
