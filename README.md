# Metronome

This is the source code for an Arduino UNO based metronome. Use VS
Code and the PlatformIO IDE extension for a better coding/building experience.

## Software prerequisites

* Arduino IDE (for build tools)
* VS Code + PlatformIO IDE extension
* Adafruit NeoMatrix library (and its dependencies)
* Adafruit GFX library

## Hardware components

* Arduino UNO
* WS2812 8x8 LED Matrix
* Piezo buzzer
* Push button
* 10k Ω potentiometer
* 2.2k Ω resistance
* Breadboard
* Jumper wires

## Wiring

* LED Matrix
  * DIN: Arduino digital pin 6
  * VCC: Arduino 5V
* Buzzer
  * VCC: Arduino digital pin 8
* Push button
  * Arduino digital pin 2
* Potentiometer
  * Arduino analog pin 0
