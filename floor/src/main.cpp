#include "data/controller.h"
#include <Arduino.h>

#define MUX_SIGNAL PIN_E7
#define MUX_S0 PIN_D0
#define MUX_S1 PIN_D1
#define MUX_S2 PIN_D2
#define MUX_S3 PIN_D3

Controller controller = Controller(MUX_S0, MUX_S1, MUX_S2, MUX_S3, MUX_SIGNAL);

void setup()
{
    // new Mux();
}

void loop()
{
    controller.update();
}

