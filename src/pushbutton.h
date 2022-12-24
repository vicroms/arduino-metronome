#pragma once

#include <Wire.h>

namespace vicroms {
using OnPushButtonLongPress = void (*)();

struct PushButton {
  PushButton(const int pin, const unsigned long sample_interval, size_t max_count, OnPushButtonLongPress callback);

  const int pin() const;

  void update(const unsigned long current_time, const int current_state);

private:
  void key_press();
  void key_release();

  const int m_pin;
  const unsigned long m_sample_interval;
  const size_t m_max_count;
  unsigned long m_time_last_read;
  size_t m_read_count;
  int m_prev_state;
  OnPushButtonLongPress m_callback;
};
}