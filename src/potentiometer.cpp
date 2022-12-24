#include "potentiometer.h"

#include <Arduino.h>
#include <string.h>

using namespace vicroms;

static constexpr size_t MAX_READINGS = 10;

Potentiometer::Potentiometer(const int pin, const unsigned long sample_interval)
    : m_pin(pin), m_sample_interval(sample_interval), m_last_read_time(0), m_total(0), m_avg(0), m_read_index(0)
{
    memset(m_readings, 0, sizeof(double) * MAX_READINGS);
}

int Potentiometer::average() { return m_avg; }

void Potentiometer::poll(const unsigned long current_time)
{
    // Update only if enough time has passed since the last read,
    // use longer intervals for more stability on reads.
    if (current_time - m_last_read_time > m_sample_interval)
    {
        m_last_read_time = current_time;
        update(analogRead(m_pin));
    }
}

void Potentiometer::update(const int new_value)
{
    // use a rolling average of readings to avoid false value changes
    // due to electrical fluctuations
    m_total = m_total - m_readings[m_read_index];
    m_readings[m_read_index] = new_value;
    m_total = m_total + m_readings[m_read_index++];
    if (m_read_index >= MAX_READINGS)
    {
        m_read_index = 0;
    }
    m_avg = m_total / MAX_READINGS;
}
