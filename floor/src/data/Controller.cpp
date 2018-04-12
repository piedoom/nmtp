#include "controller.h"
#include <Arduino.h>

Controller::Controller(int _s0, int _s1, int _s2, int _s3, int _signal) {
    floor_mux = Mux(_s0, _s1, _s2, _s3, _signal);
    state = {};
};

void Controller::update() {
    /// get new comparative state
    State new_state = get_state();

    for (int i = 0; i < 16; i++ ) {
        Serial.print(new_state.floor.squares[i]);
    }
    Serial.println();
    //Serial.println(new_state.floor.squares[2]);
};

State Controller::get_state() {
    // loop through all hardware to get state
    // get floorboard state
    State new_state;
    floor_mux.read_all(new_state.floor.squares);

    return new_state;
};