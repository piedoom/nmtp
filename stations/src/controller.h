#pragma once

#include "data/state.h"
#include <stdint.h>
#include <MIDI.h>

typedef midi::MidiInterface<HardwareSerial> MidiInterface;
class Controller {
    private: 
        /// Assign envelope reads to state object
        void set_envelope(State *state);
        State state;
        MidiInterface& mMidi;

    public:
        Controller(MidiInterface &inInterface) : mMidi(inInterface) { }
        float normalize(float num, float max = 1023);
        int8_t midify(float num, float max = 1023);
        Controller();
        State get_state();
        // update, send, and generally take care of all
        // functions needed to send midi data.
        void update();
        void begin();
};
