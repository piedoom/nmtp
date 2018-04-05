#include <Arduino.h>
#include "data/state.h"
#include "controller.h"
#include <MIDI.h>


State state = {};

MidiInterface MIDI(Serial1);
Controller controller(MIDI);

void setup() {
    // initialize data   
    controller.begin();
}

void loop() {
    // poll each hardware device and update the state
    controller.update();
    delay(100);
}

