#pragma once
#include "data/button.h"

/// Immutable struct holds all data, useful for comparison
struct State {
    public:
        Button buttons[16] {};
        bool light_states[16] {0};
};