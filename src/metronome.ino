#include <Arduino.h>
// #include <Adafruit_GFX.h>
// #include "Adafruit_LEDBackpack.h"

// static Adafruit_BicolorMatrix& matrix() {
//   static auto matrix = Adafruit_BicolorMatrix();
//   return matrix;
// }
#include "patterns.h"
#include "pushbutton.h"
#include "potentiometer.h"

using namespace vicroms;

enum class TimeSignature : size_t {
  FourFour = 0,
  ThreeFour,
  SixEight,
  COUNT
};

struct MetronomeState {
  unsigned long previous_time;
  unsigned long press_start = 0;
  int interval;

  MetronomeState()
    : m_current_signature(0),
      m_beat_accent(4),
      m_current_beat(4),
      m_signature(TimeSignature::FourFour),
      m_pattern(FourFourPattern::instance()) {}

  void print_current_state() const 
  {
    Serial.print("Time signature: ");
    Serial.println(m_pattern->name());
    Serial.print("Current beat: ");
    Serial.println(m_current_beat);
    Serial.print("Interval: ");
    Serial.println(interval);
  }

  const DisplayPattern current_pattern() const {
    return m_pattern->cur();
  }

  void beat() {
    static constexpr int PIEZO_PIN = 8;

    // If is the first beat of the bar play an A note at 880hz (one octave higher)
    // else play an A note at 440 Hz
    if (m_current_beat == m_beat_accent - 1) {
      tone(PIEZO_PIN, 880, 20);
    }
    // else play an A at 440 hz
    else {
      tone(PIEZO_PIN, 440, 20);
    }

    if (++m_current_beat >= m_beat_accent) {
      m_current_beat = 0;
    }

    // also advance the display pattern
    m_pattern->next();
  }

  void next_signature() {
    static constexpr TimeSignature SIGNATURES[] = { TimeSignature::FourFour, TimeSignature::ThreeFour, TimeSignature::SixEight };
    m_current_signature++;
    if (m_current_signature >= static_cast<size_t>(TimeSignature::COUNT)) {
      m_current_signature = 0;
    }
    Serial.print("Current signature: ");
    Serial.println(m_current_signature);
    set_signature(SIGNATURES[m_current_signature]);
  }

private:
  void set_signature(TimeSignature s) {
    m_signature = s;
    switch (s) {
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
      case TimeSignature::FourFour:  // falls through
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


static MetronomeState metronome;
static Potentiometer pot;


void mode_changed() {
  metronome.next_signature();
}

static PushButton signature_button(2, 25 /*ms*/, 80, &mode_changed);


void setup() {
  Serial.begin(9600);

  // auto& mtx = matrix();
  // mtx.begin(0x70);     // pass in the address
  // mtx.setRotation(3);  // rotate so pins are at 0th row

  pinMode(signature_button.pin(), INPUT);
}


void loop() {
  // read potentiometer status and delay for stability
  pot.update(analogRead(A0));
  delay(1);  

  // map the pot average to an interval (bpm = 1000 / interval * 60).
  // bpm can be set between 45bpm (1500 ms interval) and 300bpm (200ms interval).
  // Must be mapped in reverse to encode non linear tempo mapping.
  metronome.interval = map(pot.average(), 0, 3200, 1500, 200);

  //check whether the button has been pressed to change time sig
  auto current_state = digitalRead(signature_button.pin());
  signature_button.update(millis(), current_state);


  // mode_switch.state = digitalRead(mode_switch.PIN);
  // if (mode_switch.state == HIGH) {
  //   metronome.next_signature();
  //   delay(500);

    // clear the display
    // auto& m = matrix();
    // m.clear();
    // m.writeDisplay();

    // delay to allow button time to unpress
  // }

  // update matrix with new pattern
  // auto& mtx = matrix();
  auto dp = metronome.current_pattern();
  // mtx.fillRect(dp.x, dp.y, dp.w, dp.h, dp.z);

  // is it time for the next beat
  unsigned long currentTime = millis();
  if (currentTime - metronome.previous_time > metronome.interval) {
    metronome.previous_time = currentTime;
    metronome.beat();
    metronome.print_current_state();
    // mtx.writeDisplay();
  }
}
