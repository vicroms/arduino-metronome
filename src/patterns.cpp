#include "patterns.h"

// struct TimeSignaturePattern {
TimeSignaturePattern::TimeSignaturePattern() : m_index(0) { }

DisplayPattern TimeSignaturePattern::cur()
{
    if (m_index >= max_states())
    {
        m_index = 0;
    }

    return DisplayPattern{
        x()[m_index],
        y()[m_index],
        w()[m_index],
        h()[m_index],
    };
}

void TimeSignaturePattern::next()
{
    ++m_index;
    if (m_index >= max_states())
    {
        m_index = 0;
    }
}

void TimeSignaturePattern::reset() { m_index = 0; }
// } TimeSignaturePattern

// struct FourFourPattern : public TimeSignaturePattern {
size_t FourFourPattern::max_states() const { return 16; }

const char* FourFourPattern::name() const { return "4/4"; }

const int* FourFourPattern::x() const
{
    static constexpr int x[] = {0, 0, 4, 4, 0, 0, 4, 4, 0, 0, 4, 4, 0, 0, 4, 4};
    return x;
}

const int* FourFourPattern::y() const
{
    static constexpr int y[] = {0, 4, 4, 0, 0, 4, 4, 0, 0, 4, 4, 0, 0, 4, 4, 0};
    return y;
}

const int* FourFourPattern::w() const
{
    static constexpr int w[] = {4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4};
    return w;
}

const int* FourFourPattern::h() const
{
    static constexpr int h[] = {4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4};
    return h;
}

FourFourPattern* FourFourPattern::instance()
{
    static FourFourPattern p;
    return &p;
}
// } FourFourPattern

// struct ThreeFourPattern : public TimeSignaturePattern {
size_t ThreeFourPattern::max_states() const { return 12; }

const char* ThreeFourPattern::name() const { return "3/4"; }

const int* ThreeFourPattern::x() const
{
    static constexpr int x[] = {2, 0, 4, 2, 0, 4, 2, 0, 4, 2, 0, 4};
    return x;
}

const int* ThreeFourPattern::y() const
{
    static constexpr int y[] = {0, 4, 4, 0, 4, 4, 0, 4, 4, 0, 4, 4};
    return y;
}

const int* ThreeFourPattern::w() const
{
    static constexpr int w[] = {4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4};
    return w;
}

const int* ThreeFourPattern::h() const
{
    static constexpr int h[] = {4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4};
    return h;
}

ThreeFourPattern* ThreeFourPattern::instance()
{
    static ThreeFourPattern p;
    return &p;
}
// } ThreeFourPattern

// struct SixEightPattern : public TimeSignaturePattern {
size_t SixEightPattern::max_states() const { return 12; }

const char* SixEightPattern::name() const { return "6/8"; }

const int* SixEightPattern::x() const
{
    static constexpr int x[] = {0, 0, 4, 4, 0, 0, 0, 0, 4, 4, 0, 0};
    return x;
}

const int* SixEightPattern::y() const
{
    static constexpr int y[] = {4, 0, 4, 0, 4, 0, 4, 0, 4, 0, 4, 0};
    return y;
}

const int* SixEightPattern::w() const
{
    static constexpr int w[] = {4, 8, 4, 4, 8, 4, 4, 8, 4, 4, 8, 4};
    return w;
}

const int* SixEightPattern::h() const
{
    static constexpr int h[] = {4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4};
    return h;
}

SixEightPattern* SixEightPattern::instance()
{
    static SixEightPattern p;
    return &p;
}
// } SixEightPattern
