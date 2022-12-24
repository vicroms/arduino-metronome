#pragma once

#include <stddef.h>

namespace vicroms {
struct Potentiometer {
  Potentiometer();
  int average();
  void update(const int new_value);

private:
  int m_total;
  int m_avg;
  size_t m_read_index;
  double m_readings[10];
};
}