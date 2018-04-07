#pragma once
#define TEMPO_AVERAGE 3
#define TEMPO_DEFAULT 100.0
#define MS_IN_SECOND 60000.0

#define MIN_TEMPO 60
#define MAX_TEMPO 160

#include "data/state.h"

struct Tempo {
    /// array of ms between button presses.  Currently only saves
    /// 3 presses, but can be changed.
    int presses[3] = {1000,1000,1000};

    /// holds the current state of the pin
    bool pin = false;

    /// get tempo
    float get_tempo() {
        /// assert that `presses` contains at least the elements it needs.  If it doesn't,
        /// return the default tempo
        int history_size = sizeof(presses);
        if (history_size < TEMPO_AVERAGE) 
            return TEMPO_DEFAULT;

        /// else, calculate the average of the last three presses
        int sum = 0;
        for (int i = 1; i < history_size; i++) {
            sum += presses[i];
        }
        float average_ms = sum / history_size;

        /// convert average_ms into a tempo
        return MS_IN_SECOND / average_ms;
    }

    /// Because it's not easy to send arbitrary data, let's just normalize our tempo into
    /// a 0 - 127 value.  This will need to be taken into consideration when setting minimum
    /// and maximum values in our DAW
    int normalized_tempo() {
        int tempo = (int)get_tempo();

        // clamp values
        if (tempo < MIN_TEMPO) 
            tempo = MIN_TEMPO;
        else if (tempo > MAX_TEMPO)
            tempo = MAX_TEMPO;

        // get in range of 0 - 1
        float scaledValue = (tempo - MIN_TEMPO) / (MAX_TEMPO - MIN_TEMPO);

        // convert for MIDI data (0-127)
        return (int)(scaledValue * 127);
    }

    void set_tempo(unsigned long millis_between) {
        // we don't want the times to average if it's been a few seconds since the last
        // press.  We will reset our presses if that's the case.

        // If it's been 3 seconds since we've pushed the button, reset
        if (millis_between > 3000) {
            presses[0] = presses[1] = presses[2] = TEMPO_DEFAULT;

        // else, just append the value to the end of our makeshift queue
        } else {
            // shift values
            presses[0] = presses[1];
            presses[1] = presses[2];
            // assign new value
            presses[2] = millis_between;
        }

    }
};
