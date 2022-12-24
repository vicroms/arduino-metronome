#include "pushbutton.h"

#include <Arduino.h>

using namespace vicroms;

PushButton::PushButton(const int pin, const unsigned long sample_interval, size_t max_count, OnPushButtonLongPress callback)
  : m_pin(pin),
    m_sample_interval(sample_interval),
    m_max_count(max_count),
    m_time_last_read(0),
    m_read_count(0),
    m_prev_state(HIGH),
    m_callback(callback) {}

const int PushButton::pin() const {
  return m_pin;
}

void PushButton::update(const unsigned long current_time, const int current_state) {
  if (current_time - m_time_last_read >= m_sample_interval) {
    m_time_last_read = current_time;

    if (m_prev_state == HIGH && current_state == LOW) {
      key_press();
    } else if (m_prev_state == LOW && current_state == HIGH) {
      key_release();
    } else if (current_state == LOW) {
      m_read_count++;
    }

    m_prev_state = current_state;
  }
}

void PushButton::key_press() {
  m_read_count = 0;
}

void PushButton::key_release() {
  if (m_read_count >= m_max_count) {
    m_callback();
  }
}
