#include "data/controller.h"
#include <Arduino.h>
#define TILE_COUNT 16

// Position of buttons physically
/* usb  ||
 * _____||_____
 * |01|02|03|04|
 * |05|06|07|08|
 * |09|10|11|12|
 * |13|14|15|16|
 * -------------
 */

int button_positions[TILE_COUNT] = //TODO: change so is correct
    { 1,  2,  3,  4  
    , 5,  6,  7,  8  
    , 9,  10, 11, 12 
    , 13, 14, 15, 16 
    };

int light_positions[TILE_COUNT] = // TODO: change so is correct
    { 1,  2,  3,  4  
    , 5,  6,  7,  8  
    , 9,  10, 11, 12 
    , 13, 14, 15, 16 
    };

Controller controller(button_positions, light_positions);

// callback when midi data received 
// https://github.com/2kohm/Teensy-USB-MIDI-CLOCK
void real_time_system(uint8_t realtimebyte) {
    // TODO: update controller tempo
    // possibly send midi notes here?
}

void setup()
{
    usbMIDI.setHandleRealTimeSystem(real_time_system);
}


void loop()
{
    controller.update();
}

