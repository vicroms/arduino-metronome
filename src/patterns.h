#pragma once

#include <stddef.h>

struct DisplayPattern {
  int x, y, z, w, h;
};

struct TimeSignaturePattern {
  virtual size_t max_states() const = 0;
  virtual const char* name() const = 0;
  virtual const int* x() const = 0;
  virtual const int* y() const = 0;
  virtual const int* z() const = 0;
  virtual const int* w() const = 0;
  virtual const int* h() const = 0;

  TimeSignaturePattern();

  DisplayPattern cur();
  void next();
  void reset();

private:
  size_t m_index;
};

struct FourFourPattern : public TimeSignaturePattern {
  virtual size_t max_states() const override;
  virtual const char* name() const override;
  virtual const int* x() const override;
  virtual const int* y() const override;
  virtual const int* z() const override;
  virtual const int* w() const override;
  virtual const int* h() const override;

  static FourFourPattern* instance();
};

struct ThreeFourPattern : public TimeSignaturePattern {
  virtual size_t max_states() const override {
    return 12;
  }

  virtual const char* name() const override {
    return "3/4";
  }

  virtual const int* x() const override {
    static constexpr int x[] = { 2, 0, 4, 2, 0, 4, 2, 0, 4, 2, 0, 4 };
    return x;
  }

  virtual const int* y() const override {
    static constexpr int y[] = { 0, 4, 4, 0, 4, 4, 0, 4, 4, 0, 4, 4 };
    return y;
  }

  virtual const int* z() const override {
    static constexpr int z[] = { 2, 2, 2, 3, 3, 3, 1, 1, 1, 0, 0, 0 };
    return z;
  }

  virtual const int* w() const override {
    static constexpr int w[] = { 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4 };
    return w;
  }

  virtual const int* h() const override {
    static constexpr int h[] = { 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4 };
    return h;
  }

  static ThreeFourPattern* instance() {
    static ThreeFourPattern p;
    return &p;
  }
};

struct SixEightPattern : public TimeSignaturePattern {
  virtual size_t max_states() const override {
    return 12;
  }

  virtual const char* name() const override {
    return "6/8";
  }

  virtual const int* x() const override {
    static constexpr int x[] = { 0, 0, 4, 4, 0, 0, 0, 0, 4, 4, 0, 0 };
    return x;
  }

  virtual const int* y() const override {
    static constexpr int y[] = { 4, 0, 4, 0, 4, 0, 4, 0, 4, 0, 4, 0 };
    return y;
  }

  virtual const int* z() const override {
    static constexpr int z[] = { 1, 1, 1, 3, 3, 3, 2, 2, 2, 0, 0, 0 };
    return z;
  }

  virtual const int* w() const override {
    static constexpr int w[] = { 4, 8, 4, 4, 8, 4, 4, 8, 4, 4, 8, 4 };
    return w;
  }

  virtual const int* h() const override {
    static constexpr int h[] = { 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4 };
    return h;
  }

  static SixEightPattern* instance() {
    static SixEightPattern p;
    return &p;
  }
};
