#pragma once
#define TEMPO_AVERAGE 3
#define TEMPO_DEFAULT 100.0
#define MS_IN_SECOND 60000.0

struct Tempo {
    /// array of ms between button presses.  Currently only saves
    /// 3 presses, but can be changed.
    int presses[];

    /// get tempo
    float get_tempo() {
        /// assert that `presses` contains at least 3 elements.  If it doesn't,
        /// return the default tempo
        if (sizeof(presses) < 3) 
            return TEMPO_DEFAULT;

        /// else, calculate the average of the last three presses
        int sum = 0;
        for (int i = 1; i < TEMPO_AVERAGE; i++) {
            sum += presses[i];
        }
        float average_ms = sum / TEMPO_AVERAGE;

        /// convert average_ms into a tempo
        return MS_IN_SECOND / average_ms;
    }
};
