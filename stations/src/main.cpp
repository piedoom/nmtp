#include <Arduino.h>
#include "data/state.h"
#include "controller.h"
#include <MIDI.h>

Controller controller;

void setup() {

}

void loop() {
    // poll each hardware device and update the state
    controller.update();
    delay(100);

    // MIDI Controllers should discard incoming MIDI messages.
    while (usbMIDI.read()) {
    }
}

