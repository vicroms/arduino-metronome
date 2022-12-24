#pragma once

#include <Wire.h>

namespace vicroms
{
    using OnPushButtonPress = void (*)();
    using OnPushButtonLongPress = void (*)();

    struct PushButton
    {
        // Starts polling for push button presses on a specific pin (digital).
        // A longer sample interval helps to deal with electrical bounce from the push button.
        // 
        // Two operation modes can be provided by setting a simple press and a longer press
        // listener. 
        //
        // The long_press_count parameter controls how many intervals have to pass to be considered
        // a long press, for example: given a sample_interval of 25ms and a count of 40, a long
        // press is detected after continually pressing for 1 second.
        PushButton(const int pin,
                   const unsigned long sample_interval,
                   OnPushButtonPress press_callback,
                   size_t long_press_count = SIZE_MAX,
                   OnPushButtonLongPress long_press_callback = nullptr);

        const int pin() const;

        void poll(const unsigned long current_time);

    private:
        void key_press();
        void key_release();

        const int m_pin;
        const unsigned long m_sample_interval;
        OnPushButtonPress m_press_callback;
        const size_t m_long_press_count;
        OnPushButtonLongPress m_long_press_callback;

        // used for key press detection
        unsigned long m_time_last_read;
        size_t m_read_count;
        int m_prev_state;
    };
}