#pragma once
#include "envelope.h"
#include "tempo.h"
#include "timbre.h"

// immutable state struct
struct State {
    Envelope envelope;
    Tempo tempo;
    Timbre timbre;
};