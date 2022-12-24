#pragma once

#include <stddef.h>

// Rectangle representation for LED Matrix display.
struct DisplayPattern
{
    int x, y, w, h;
};

// Repeating pattern used on LED Matrix display.
// Patterns are represented using a structure-of-arrays:
//
// * x(): Rectangle x-coordinates
// * y(): Rectangle y-coordinates
// * w(): Rectangle widths
// * h(): Rectangle heights
//
// Use the cur() and next() methods to access and control the display patterns.
struct TimeSignaturePattern
{
    // Max number of states for this time signature.
    virtual size_t max_states() const = 0;

    // Time signature friendly name, e.g.: 4/4.
    virtual const char* name() const = 0;

    virtual const int* x() const = 0;
    virtual const int* y() const = 0;
    virtual const int* w() const = 0;
    virtual const int* h() const = 0;

    TimeSignaturePattern();

    // Get current display pattern.
    DisplayPattern cur();

    // Advance to the next display pattern.
    void next();

    // Reset display pattern.
    void reset();

private:
    size_t m_index;
};

struct FourFourPattern : public TimeSignaturePattern
{
    virtual size_t max_states() const override;
    virtual const char* name() const override;
    virtual const int* x() const override;
    virtual const int* y() const override;
    virtual const int* w() const override;
    virtual const int* h() const override;

    static FourFourPattern* instance();
};

struct ThreeFourPattern : public TimeSignaturePattern
{
    virtual size_t max_states() const override;
    virtual const char* name() const override;
    virtual const int* x() const override;
    virtual const int* y() const override;
    virtual const int* w() const override;
    virtual const int* h() const override;

    static ThreeFourPattern* instance();
};

struct SixEightPattern : public TimeSignaturePattern
{
    virtual size_t max_states() const override;
    virtual const char* name() const override;
    virtual const int* x() const override;
    virtual const int* y() const override;
    virtual const int* w() const override;
    virtual const int* h() const override;

    static SixEightPattern* instance();
};
