#pragma once

// envelope data
// all data is normalized between 0 - 1, and should be adjusted based on tempo
struct Envelope {
    int8_t attack_time;
    int8_t max_volume;
    int8_t decay_volume;
    int8_t release_time;
};
