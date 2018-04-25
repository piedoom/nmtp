#include "controller.h"
#include <Arduino.h>

#define TILE_COUNT 16

Controller::Controller(int b_arr[], int l_arr[]) {
    button_positions.positions = b_arr;
    light_positions.positions = l_arr;

    state = get_state();
};

void Controller::update() {
    /// get new comparative state
    State new_state = get_state();

    // compare current state to new_state
    // loop through all buttons to get actual state
    for (int i = 0; i < TILE_COUNT; i++) {
        bool new_button_state = new_state.buttons[i].immediate_state;
        bool current_button_state = state.buttons[i].immediate_state;

        // check differences

        // if nothing has changed, continue loop.
        if (new_button_state == current_button_state)
            continue;

        if (new_button_state != current_button_state) {
            // we just toggled the button on
            if (new_button_state)
                new_state.buttons[i].state = true;
                // TODO: change lights to on

            // we just toggled the button off
            if (!new_button_state)
                new_state.buttons[i].state = false;
                // TODO: change lights to off
        }
    }
    // TODO

    // set new_state as current state when done
    state = new_state;
};

State Controller::get_state() {
    // get floorboard state
    State new_state;

    // loop through all hardware to get immediate state
    for (int i = 0; i < TILE_COUNT; i++) {
        new_state.buttons[i].immediate_state = digitalRead(button_positions.positions[i]);
    }

    return new_state;
};