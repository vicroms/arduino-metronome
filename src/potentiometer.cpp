#include "potentiometer.h"

#include <string.h>
#include <math.h>

using namespace vicroms;

static constexpr size_t MAX_READINGS = 10;

Potentiometer::Potentiometer()
  : m_total(0), m_avg(0), m_read_index(0) {
  memset(m_readings, 0, sizeof(double) * MAX_READINGS);
}

int Potentiometer::average() {
  return m_avg;
}

void Potentiometer::update(const int new_value) {
  m_total = m_total - m_readings[m_read_index];
  m_readings[m_read_index] = new_value;
  m_total = m_total + m_readings[m_read_index++];
  if (m_read_index >= MAX_READINGS) {
    m_read_index = 0;
  }
  m_avg = sqrt(m_total / MAX_READINGS) * 100;
}
