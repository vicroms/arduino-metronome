#include "patterns.h"

// struct TimeSignaturePattern {
TimeSignaturePattern::TimeSignaturePattern()
  : m_index(0) {}

DisplayPattern TimeSignaturePattern::cur() {
  if (m_index >= max_states()) {
    m_index = 0;
  }

  return DisplayPattern{
    x()[m_index],
    y()[m_index],
    z()[m_index],
    w()[m_index],
    h()[m_index]
  };
}

void TimeSignaturePattern::next() {
  ++m_index;
  if (m_index >= max_states()) {
    m_index = 0;
  }
}

void TimeSignaturePattern::reset() {
  m_index = 0;
}
// } TimeSignaturePattern

// struct FourFourPattern : public TimeSignaturePattern {
size_t FourFourPattern::max_states() const {
  return 16;
}

const char* FourFourPattern::name() const {
  return "4/4";
}

const int* FourFourPattern::x() const {
  static constexpr int x[] = { 0, 0, 4, 4, 0, 0, 4, 4, 0, 0, 4, 4, 0, 0, 4, 4 };
  return x;
}

const int* FourFourPattern::y() const {
  static constexpr int y[] = { 0, 4, 4, 0, 0, 4, 4, 0, 0, 4, 4, 0, 0, 4, 4, 0 };
  return y;
}

const int* FourFourPattern::z() const {
  static constexpr int z[] = { 2, 2, 2, 2, 3, 3, 3, 3, 1, 1, 1, 1, 0, 0, 0, 0 };
  return z;
}

const int* FourFourPattern::w() const {
  static constexpr int w[] = { 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4 };
  return w;
}

const int* FourFourPattern::h() const {
  static constexpr int h[] = { 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4 };
  return h;
}

FourFourPattern* FourFourPattern::instance() {
  static FourFourPattern p;
  return &p;
}
// } FourFourPattern