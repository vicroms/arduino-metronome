#pragma once

#include <stddef.h>

namespace vicroms
{
    struct Potentiometer
    {
        // Starts polling for potentiometer reading changes on a specific pin (analog).
        // A longer sample interval helps to deal with slight variations.
        Potentiometer(const int pin, const unsigned long sample_interval);

        // Gets average value reading on potentiometer (ranges from 0 to 1023)
        int value();

        // Updates potentiometer state
        void poll(const unsigned long current_time);

    private:
        void update(const int new_value);

        const int m_pin;
        const unsigned long m_sample_interval;
        unsigned long m_last_read_time;
        int m_total;
        int m_avg;
        size_t m_read_index;
        double m_readings[10];
    };
}