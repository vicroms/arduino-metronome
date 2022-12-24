#include <Arduino.h>

#include "colors.h"
#include "display.h"
#include "patterns.h"
#include "potentiometer.h"
#include "pushbutton.h"

using namespace vicroms;

static constexpr int PUSH_BUTTON_PIN = 2;

enum class TimeSignature : size_t
{
    FourFour = 0,
    ThreeFour,
    SixEight,
    COUNT
};

struct MetronomeState
{
    unsigned long previous_time;
    unsigned long interval;

    MetronomeState()
        : m_current_signature(0)
        , m_beat_accent(4)
        , m_current_beat(4)
        , m_signature(TimeSignature::FourFour)
        , m_pattern(FourFourPattern::instance())
    {
    }

    void print_current_state() const
    {
        Serial.print("Time signature: ");
        Serial.println(m_pattern->name());
        Serial.print("Current beat: ");
        Serial.println(m_current_beat);
        Serial.print("Interval: ");
        Serial.println(interval);

        const auto bpm = static_cast<double>(1000.0 / interval * 60.0);
        Serial.print("BPM: ");
        Serial.println(bpm, 2);
    }

    void beat()
    {
        static constexpr int PIEZO_PIN = 8;

        const auto p = m_pattern->cur();
        auto& matrix = display();
        matrix.fillScreen(0);
        // If is the first beat of the bar play an A note at 880hz (one octave higher)
        if (m_current_beat == m_beat_accent - 1)
        {
            tone(PIEZO_PIN, 880, 20);
            matrix.fillRect(p.x, p.y, p.w, p.h, Colors::Magenta());
        }
        // else play an A at 440 hz
        else
        {
            tone(PIEZO_PIN, 440, 20);
            matrix.fillRect(p.x, p.y, p.w, p.h, Colors::Cyan());
        }
        matrix.show();

        if (++m_current_beat >= m_beat_accent)
        {
            m_current_beat = 0;
        }

        // also advance the display pattern
        m_pattern->next();
    }

    void next_signature()
    {
        static constexpr TimeSignature SIGNATURES[] = {
            TimeSignature::FourFour, TimeSignature::ThreeFour, TimeSignature::SixEight};
        m_current_signature++;
        if (m_current_signature >= static_cast<size_t>(TimeSignature::COUNT))
        {
            m_current_signature = 0;
        }
        Serial.print("Current signature: ");
        Serial.println(m_current_signature);
        set_signature(SIGNATURES[m_current_signature]);
    }

private:
    void set_signature(TimeSignature s)
    {
        m_signature = s;
        switch (s)
        {
            case TimeSignature::ThreeFour:
                m_current_beat = 3;
                m_beat_accent = 3;
                m_pattern = ThreeFourPattern::instance();
                break;
            case TimeSignature::SixEight:
                m_current_beat = 6;
                m_beat_accent = 6;
                m_pattern = SixEightPattern::instance();
                break;
            case TimeSignature::FourFour: // falls through
            default:
                m_current_beat = 4;
                m_beat_accent = 4;
                m_pattern = FourFourPattern::instance();
        }
        m_pattern->reset();
    }

    size_t m_current_signature;
    int m_beat_accent;
    int m_current_beat;
    TimeSignature m_signature;
    TimeSignaturePattern* m_pattern;
};

// register callback
void mode_changed();

static MetronomeState metronome;
static Potentiometer pot(A0, 10 /*ms*/);
static PushButton signature_button(
    PUSH_BUTTON_PIN, 25 /*ms*/, nullptr /* do nothing on short press*/, 40 /* long press ticks */, &mode_changed);

void mode_changed() { metronome.next_signature(); }

void setup()
{
    Serial.begin(9600);

    pinMode(signature_button.pin(), INPUT);

    auto& matrix = display();
    matrix.begin();
    matrix.setBrightness(10);
}

void loop()
{
    signature_button.poll(millis());

    pot.poll(millis());
    // we want a non-linear curve on the potentiometer readings for finer control at high BPMs
    const auto adjusted_reading = sqrt(pot.average()) * 100;

    // map the pot average to an interval (bpm = 1000 / interval * 60).
    // bpm can be set between 45bpm (1500 ms interval) and 300bpm (200ms interval).
    // Must be mapped in reverse to encode non linear tempo mapping.
    metronome.interval = map(adjusted_reading, 0, 3200, 1500, 200);

    // check whether the button has been pressed to change time sig

    // is it time for the next beat
    unsigned long currentTime = millis();
    if (currentTime - metronome.previous_time > metronome.interval)
    {
        metronome.previous_time = currentTime;
        metronome.beat();
        metronome.print_current_state();
    }
}
