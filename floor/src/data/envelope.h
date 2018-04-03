#pragma once

// envelope data
// all data is normalized between 0 - 1, and should be adjusted based on tempo
struct Envelope {
    float attack_time;
    float max_volume;
    float decay_volume;
    float release_time;
};
