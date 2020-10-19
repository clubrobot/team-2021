#include "ShiftRegister.h"
#include <Arduino.h>

void ShiftRegister::attach(uint8_t latchpin, uint8_t clockpin, uint8_t datapin)
{
    m_LATCH = latchpin;
    m_CLOCK = clockpin;
    m_DATA = datapin;

    pinMode(m_LATCH, OUTPUT);
    pinMode(m_CLOCK, OUTPUT);
    pinMode(m_DATA, OUTPUT);

    digitalWrite(m_LATCH, 0);
    digitalWrite(m_CLOCK, 0);
    digitalWrite(m_DATA, 0);

    m_register = 0;

    // Clear on init
    clear();
}

void ShiftRegister::SetHigh(int pos)
{
    if (pos < m_size && pos >= 0)
    {
        m_register |= (1 << pos);
        shift();
    }
}

void ShiftRegister::SetLow(int pos)
{
    if (pos < m_size && pos >= 0)
    {
        m_register &= ~(1 << pos);
        shift();
    }
}

void ShiftRegister::shift()
{
    if (m_size > 0)
    {
        digitalWrite(m_LATCH, LOW);
        for (int i = 0; i < m_size; i++)
        {
            digitalWrite(m_DATA, !!(m_register & (1 << i)));
            step();
        }
        digitalWrite(m_LATCH, HIGH);
    }
}

void ShiftRegister::clear()
{
    if (m_size > 0)
    {
        digitalWrite(m_LATCH, LOW);
        for (int i = 0; i < m_size; i++)
        {
            digitalWrite(m_DATA, !!(m_register & (1 << ((m_size - 1) - i))));
            step();
        }
        digitalWrite(m_LATCH, HIGH);
    }
}

void ShiftRegister::step()
{
    delayMicroseconds(45);
    digitalWrite(m_CLOCK, HIGH);
    delayMicroseconds(45);
    digitalWrite(m_CLOCK, LOW);
}

void ShiftRegister::write(int pos, int state)
{
    if (state == 1)
        this->SetHigh(pos);
    else
        this->SetLow(pos);
}