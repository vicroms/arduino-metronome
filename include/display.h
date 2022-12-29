#pragma once

#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>

namespace vicroms
{
    static Adafruit_NeoMatrix& display()
    {
        static constexpr int DISPLAY_WIDTH = 8;
        static constexpr int DISPLAY_HEIGHT = 8;
        static constexpr uint8_t DISPLAY_PIN = 6;
        static constexpr uint8_t DISPLAY_MATRIX_LAYOUT =
            NEO_MATRIX_TOP + NEO_MATRIX_RIGHT + NEO_MATRIX_COLUMNS + NEO_MATRIX_PROGRESSIVE;
        static constexpr uint16_t DISPLAY_MATRIX_PIXEL_TYPE = NEO_GRB + NEO_KHZ800;

        static Adafruit_NeoMatrix instance(
            DISPLAY_WIDTH, DISPLAY_HEIGHT, DISPLAY_PIN, DISPLAY_MATRIX_LAYOUT, DISPLAY_MATRIX_PIXEL_TYPE);
        return instance;
    }
}
