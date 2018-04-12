#include "Mux.h"
#include <Arduino.h>

bool* Mux::readAll(int pin) {
    bool values[16];
    for (int i = 0; i < 3; i++) {
        digitalWrite(s0, bitRead(i, 0));
        digitalWrite(s1, bitRead(i, 1));
        digitalWrite(s2, bitRead(i, 2));
        digitalWrite(s3, bitRead(i, 3));

        values[i] = digitalRead(signal_pin);
    }

    return values;
};
