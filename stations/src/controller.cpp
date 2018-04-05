#include <Arduino.h>
#include "controller.h"
#include <math.h>

#define PIN_ENVELOPE_1 0
#define PIN_ENVELOPE_2 1
#define PIN_ENVELOPE_3 2
#define PIN_ENVELOPE_4 3
#define CONTROLLER_CHANNEL 0
#define MIDI_CHANNEL 1

//MIDI_CREATE_DEFAULT_INSTANCE();

void Controller::begin() {
    mMidi.begin();
    state = {};
}

void Controller::set_envelope(State *state) {
    // assign the state data
    state->envelope.attack_time =  midify(analogRead(PIN_ENVELOPE_1));
    state->envelope.max_volume =   midify(analogRead(PIN_ENVELOPE_2));
    state->envelope.decay_volume = midify(analogRead(PIN_ENVELOPE_3));
    state->envelope.release_time = midify(analogRead(PIN_ENVELOPE_4));
}

float Controller::normalize(float num, float max) {
    return num / max;
}

int8_t Controller::midify(float num, float max) {
    float normalized_value = normalize(num, max) * 127;
    return (int)round(normalized_value);
}

State Controller::get_state() {
    State state = {};
    set_envelope(&state);
    // TODO: Set timbre
    // TODO: Set tempo
    return state;
}

void Controller::update() {
    
    // get current position of hardware
    State new_state = get_state();
    
    // send data based on if value has changed
    if (new_state.envelope.attack_time != state.envelope.attack_time) {
        mMidi.sendControlChange(CONTROLLER_CHANNEL, new_state.envelope.attack_time, MIDI_CHANNEL);
    }

    if (new_state.envelope.decay_volume != state.envelope.decay_volume) {
        mMidi.sendControlChange(CONTROLLER_CHANNEL, new_state.envelope.decay_volume, MIDI_CHANNEL);
    }

    if (new_state.envelope.max_volume != state.envelope.max_volume) {
        mMidi.sendControlChange(CONTROLLER_CHANNEL, new_state.envelope.max_volume, MIDI_CHANNEL);
    }

    if (new_state.envelope.release_time != state.envelope.release_time) {
        mMidi.sendControlChange(CONTROLLER_CHANNEL, new_state.envelope.release_time, MIDI_CHANNEL);
    }

    //MIDI.sendControlChange(CONTROLLER_CHANNEL, new_state.envelope.release_time, MIDI_CHANNEL);

    // set the state
    state = new_state;
}