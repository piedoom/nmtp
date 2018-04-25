#include "floor.h"
#include "data/button.h"

/// Immutable struct holds all data, useful for comparison
struct State {
    Button buttons[16] {};
    bool light_states[16] {0};
};