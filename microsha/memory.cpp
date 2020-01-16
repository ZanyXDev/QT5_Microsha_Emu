#include "memory.h"

Memory::Memory(QObject *parent) : QObject(parent)
{
    /// @todo need extract to other class
    vg75_c001_00_cmd = 0;

    screen_size_x_buf = 0;
    screen_size_y_buf = 0;

    ik57_e008_80_cmd = 0;
    vg75_c001_80_cmd = 0;

    cursor_x_buf = 0;
    cursor_y_buf = 0;

    tape_8002_as_output = 0;

    video_memory_base_buf = 0;
    video_memory_size_buf = 0;

    video_memory_base = 0;
    video_memory_size = 0;

    video_screen_size_x = 0;
    video_screen_size_y = 0;

    video_screen_cursor_x = 0;
    video_screen_cursor_y = 0;
}

int Memory::length()
{
    return m_buf.size();
}

quint8 Memory::readRaw(quint16 addr)
{
    if (addr > m_buf.size())
    {
        return 0x0;
    }
    return m_buf.at( addr );
}

quint8 Memory::read(quint16 addr)
{
    /// @todo need extract to other class
    if (addr == 0x8002)
    {
        /// @todo fix keyboard it is other object
        // return keyboard.modifiers;
    }
    if (addr == 0x8001)
    {
        /// @todo fix keyboard it is other object
        // keyboard_state = this.keyboard.state;
        quint8 ch = 0xff;
        quint8 kbd_scanline = m_buf[0x8000];
        for (int i = 0; i < 8; i++)
        {
            if ((1 << i) & kbd_scanline){
                /// @todo fix keyboard it is other object
                //ch &= keyboard_state[i];
            }
        }
        return ch;
    }

    if (addr == 0xC001)
    {
        return 0xff;
    }
    return m_buf.at( addr );
}

void Memory::zeroRam()
{
    if (m_buf.size() < MAX_RAM)
    {
        this->init();
    }

    for (int i=0; i<MAX_RAM;++i)
    {
        m_buf[i] = 0x0;
    }
}

void Memory::writeRaw(quint16 addr, quint8 byte)
{
    m_buf[addr] = byte;
}

void Memory::write(quint16 addr, quint8 byte)
{

    if (addr >= 0xF800)
    {
        return;
    }

    m_buf[addr] = byte;

    /// @todo need extract to other class
    quint16 peripheral_reg = addr & 0xefff;

    // RUS/LAT indicator
    if (peripheral_reg == 0x8003)
    {
        if (byte == last_written_byte)
        {
            return;
        }
        // The indicator status can is "byte & 0x01".
        last_written_byte = byte;
        return;
    }
    // The cursor control sequence.
    if (peripheral_reg == 0xc001 && byte == 0x80)
    {
        vg75_c001_80_cmd = 1;
        return;
    }

    if (peripheral_reg == 0xc000 && vg75_c001_80_cmd == 1)
    {
        vg75_c001_80_cmd += 1;
        cursor_x_buf = byte + 1;
        return;
    }

    if (peripheral_reg == 0xc000 && vg75_c001_80_cmd == 2)
    {
        cursor_y_buf = byte + 1;
        //screen.set_cursor(cursor_x_buf - 1, cursor_y_buf - 1);
        video_screen_cursor_x = cursor_x_buf;
        video_screen_cursor_y = cursor_y_buf;
        vg75_c001_80_cmd = 0;
        return;
    }
    // The screen format command sequence.
    if (peripheral_reg == 0xc001 && byte == 0)
    {
        vg75_c001_00_cmd = 1;
        return;
    }

    if (peripheral_reg == 0xc000 && vg75_c001_00_cmd == 1)
    {
        screen_size_x_buf = (byte & 0x7f) + 1;
        vg75_c001_00_cmd += 1;
        return;
    }

    if (peripheral_reg == 0xc000 && vg75_c001_00_cmd == 2)
    {
        screen_size_y_buf = (byte & 0x3f) + 1;
        vg75_c001_00_cmd = 0;
        return;
    }

    // The screen area parameters command sequence.

    if (peripheral_reg == 0xe008 && byte == 0x80)
    {
        ik57_e008_80_cmd = 1;
        tape_8002_as_output = 1;
        return;
    }

    if (peripheral_reg == 0xe004 && ik57_e008_80_cmd == 1)
    {
        video_memory_base_buf = byte;
        ik57_e008_80_cmd += 1;
        return;
    }

    if (peripheral_reg == 0xe004 && ik57_e008_80_cmd == 2)
    {
        video_memory_base_buf |= byte << 8;
        ik57_e008_80_cmd += 1;
        return;
    }

    if (peripheral_reg == 0xe005 && ik57_e008_80_cmd == 3)
    {
        video_memory_size_buf = byte;
        ik57_e008_80_cmd += 1;
        return;
    }

    if (peripheral_reg == 0xe005 && ik57_e008_80_cmd == 4)
    {
        video_memory_size_buf = ((video_memory_size_buf | (byte << 8)) & 0x3fff) + 1;
        ik57_e008_80_cmd = 0;
        return;
    }
    // Settings for video memory boundaries and the screen format
    // only take an effect after the DMA command 0xA4 (start the channel).
    if (peripheral_reg == 0xe008 && byte == 0xa4)
    {
        if (screen_size_x_buf && screen_size_y_buf)
        {
            // Save ("apply") the screen dimentions.
            video_screen_size_x = screen_size_x_buf;
            video_screen_size_y = screen_size_y_buf;
            // Save ("apply") the video area parameters.
            video_memory_base = video_memory_base_buf;
            video_memory_size = video_memory_size_buf;
            // Re-configure video.
            //screen.set_geometry(video_screen_size_x, video_screen_size_y,video_memory_base);
        }

        tape_8002_as_output = 0;
        return;
    }

    if (addr == 0x8002)
    {
        // Tape I/O isn't implemented yet.
        // if (this.tape_8002_as_output)
        //   this.tape_write_bit(byte & 0x01);
        return;
    }
}

void Memory::loadFile(QByteArray &data)
{
    quint16 i = 0;

    QByteArray::iterator data_iterator = data.begin();

    while( data_iterator != data.end() )
    {
        writeRaw(i, static_cast<quint8>( *data_iterator ));
        data_iterator++;
        i++;
    }
}

void Memory::init()
{
    m_buf.clear();
    for (int i=0; i<MAX_MEM;++i)
    {
        m_buf.insert(i,0x0);
    }
}
