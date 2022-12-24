#pragma once

#include <stdint.h>

namespace vicroms
{

    namespace Colors
    {
        // generates a 16-bit encoded RGB color, RGB values range from 0 to 255.
        static constexpr uint16_t from_rgb(uint8_t r, uint8_t g, uint8_t b)
        {
            return ((uint16_t)(r & 0xF8) << 8) | ((uint16_t)(g & 0xFC) << 3) | (b >> 3);
        }

        static constexpr uint16_t Red() { return from_rgb(255, 0, 0); }
        static constexpr uint16_t Green() { return from_rgb(0, 255, 0); }
        static constexpr uint16_t Blue() { return from_rgb(0, 0, 255); }
        static constexpr uint16_t Yellow() { return Red() + Green(); }
        static constexpr uint16_t Magenta() { return Red() + Blue(); }
        static constexpr uint16_t Cyan() { return Green() + Blue(); }
        static constexpr uint16_t Orange() { return from_rgb(255, 127, 0); }
        static constexpr uint16_t LimeGreen() { return from_rgb(0, 255, 127); }
    }
}
