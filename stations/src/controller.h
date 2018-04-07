#pragma once

#include "data/state.h"
#include <stdint.h>

class Controller {
    private: 
        /// Assign envelope reads to state object
        void set_envelope(State *state);
        /// assign tempo
        void set_tempo(State *state);
        /// if tempo button is currently pressed
        bool tempo_pressed = false;
        unsigned long tempo_last_pressed_time = 0;
        State state;

    public:
        Controller();
        float normalize(float num, float max = 1023);
        int8_t midify(float num, float max = 1023);
        State set_state();
        // update, send, and generally take care of all
        // functions needed to send midi data.
        void update();
};
