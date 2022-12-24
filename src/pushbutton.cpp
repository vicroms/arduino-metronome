#include "pushbutton.h"

#include <Arduino.h>
#include <Wire.h>

using namespace vicroms;

PushButton::PushButton(const int pin,
                       const unsigned long sample_interval,
                       OnPushButtonPress press_callback,
                       size_t long_press_count,
                       OnPushButtonLongPress long_press_callback)
    : m_pin(pin)
    , m_sample_interval(sample_interval)
    , m_press_callback(press_callback)
    , m_long_press_count(long_press_count)
    , m_long_press_callback(long_press_callback)
    , m_time_last_read(0)
    , m_read_count(0)
    , m_prev_state(HIGH)
{
}

const int PushButton::pin() const { return m_pin; }

void PushButton::poll(const unsigned long current_time)
{
    if (current_time - m_time_last_read >= m_sample_interval)
    {
        m_time_last_read = current_time;

        const auto current_state = digitalRead(m_pin);

        if (m_prev_state == HIGH && current_state == LOW)
        {
            key_press();
        }
        else if (m_prev_state == LOW && current_state == HIGH)
        {
            key_release();
        }
        else if (current_state == LOW)
        {
            m_read_count++;
        }

        m_prev_state = current_state;
    }
}

void PushButton::key_press() { m_read_count = 0; }

void PushButton::key_release()
{
    if (m_read_count >= m_long_press_count && m_long_press_callback)
    {
        m_long_press_callback();
    }
    else if (m_press_callback)
    {
        m_press_callback();
    }
}
