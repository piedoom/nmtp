#include <Arduino.h>
#include "controller.h"
#include <math.h>

#define PIN_ENVELOPE_1 PIN_F0
#define PIN_ENVELOPE_2 PIN_F1
#define PIN_ENVELOPE_3 PIN_F4
#define PIN_ENVELOPE_4 PIN_F5

#define PIN_TEMPO PIN_D6

#define MIDI_CHANNEL 1

#define CC_ATTACK 73
#define CC_SUSTAIN 70
#define CC_DECAY 71
#define CC_RELEASE 69

#define CC_TEMPO 20

Controller::Controller() {
    state = {};
}

void Controller::set_envelope(State *_state) {
    // assign the state data
    _state->envelope.attack_time =  midify(analogRead(PIN_ENVELOPE_1));
    _state->envelope.max_volume =   midify(analogRead(PIN_ENVELOPE_2));
    _state->envelope.decay_volume = midify(analogRead(PIN_ENVELOPE_3));
    _state->envelope.release_time = midify(analogRead(PIN_ENVELOPE_4));
}

void Controller::set_tempo(State *_state) {
    _state->tempo.pin = (bool)digitalRead(PIN_TEMPO);

    /// If the user presses the button for the first time
    if (_state->tempo.pin && !tempo_pressed) {
        /// set time since last pressed
        unsigned long millis_between = millis() - tempo_last_pressed_time;
        /// reset counter time
        tempo_last_pressed_time = millis();
        /// Only toggle once per push, not every time the 
        /// loop goes through
        tempo_pressed = true;
        _state->tempo.set_tempo(millis_between);
    /// reset the pressed state if the button isn't being pressed
    } else if (!_state->tempo.pin) {
        // if the button isn't pressed, update the state accordingly
        tempo_pressed = false;
    }
}

float Controller::normalize(float num, float max) {
    return num / max;
}

int8_t Controller::midify(float num, float max) {
    float normalized_value = normalize(num, max) * 127;
    return (int)round(normalized_value);
}

State Controller::set_state() {
    State new_state = {};
    set_envelope(&new_state);
    // TODO: Set timbre
    // TODO: Set tempo
    set_tempo(&new_state);
    return new_state;
}

void Controller::update() {
    
    // get current position of hardware
    State new_state = set_state();
    
    // send data based on if value has changed.
    if (new_state.envelope.attack_time != state.envelope.attack_time) {
        usbMIDI.sendControlChange(CC_ATTACK, new_state.envelope.attack_time, MIDI_CHANNEL);
    }

    if (new_state.envelope.decay_volume != state.envelope.decay_volume) {
        usbMIDI.sendControlChange(CC_DECAY, new_state.envelope.decay_volume, MIDI_CHANNEL);
    }

    if (new_state.envelope.max_volume != state.envelope.max_volume) {
        usbMIDI.sendControlChange(CC_SUSTAIN, new_state.envelope.max_volume, MIDI_CHANNEL);
    }

    if (new_state.envelope.release_time != state.envelope.release_time) {
        usbMIDI.sendControlChange(CC_RELEASE, new_state.envelope.release_time, MIDI_CHANNEL);
    }

    

    // if tempo has changed, send a CC
    // since it's a C array, we need to compare elements via a loop
    bool tempo_changed = false;
    for (int i = 0; i < sizeof(state.tempo.presses); i++) {
        if (new_state.tempo.presses[i] != state.tempo.presses[i])
            tempo_changed = true;        
    }
    if (tempo_changed == true) {
        usbMIDI.sendControlChange(CC_TEMPO, new_state.tempo.normalized_tempo(), MIDI_CHANNEL);
        Serial.print("tempo cc: ");
        Serial.println(new_state.tempo.normalized_tempo());
    }

    // update the held state with our new state
    state = new_state;

}