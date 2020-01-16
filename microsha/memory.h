#ifndef MEMORY_H
#define MEMORY_H

#include <QObject>
#include <QVector>

#define MAX_MEM 0x10000
#define MAX_RAM 0x8000


class Memory : public QObject
{
    Q_OBJECT
public:
    explicit Memory(QObject *parent = nullptr);
    int length();
    quint8 readRaw(quint16 addr);
    quint8 read(quint16 addr);

signals:

public slots:
    void zeroRam();
    void writeRaw(quint16 addr, quint8 byte);
    void write(quint16 addr, quint8 byte);
    void loadFile(QByteArray &data);
private:
    int last_written_byte;
    QVector<quint8> m_buf;

    quint8 vg75_c001_80_cmd;
    quint8 vg75_c001_00_cmd;
    quint8 cursor_x_buf;
    quint8 cursor_y_buf;
    quint8 video_screen_cursor_x;
    quint8 video_screen_cursor_y;
    quint8 screen_size_x_buf;
    quint8 screen_size_y_buf;
    quint8 ik57_e008_80_cmd;
    quint8 tape_8002_as_output;
    quint8 video_memory_base_buf;
    quint16 video_memory_size_buf;
    quint16 video_memory_base;
    quint16 video_memory_size;
    quint8 video_screen_size_x;
    quint8 video_screen_size_y;

    void init();
};

#endif // MEMORY_H
