#include "data/controller.h"
#include <Arduino.h>
#define TILE_COUNT 16

byte counter; 
byte CLOCK = 248; 
byte START = 250; 
byte CONTINUE = 251; 
byte STOP = 252;
int row = 0;
int pattern = 0;
// Position of buttons physically
/* usb  ||
 * _____||_____
 * |C3|D6|D1|C2|
 * |C0|D4|D7|E0|
 * |E1|D2|D5|??|
 * |C1|D3|D0|??|
 * -------------
 */

//C4, C5

int button_positions[TILE_COUNT] = //TODO: change so is correct
    { PIN_C3,  PIN_D6,  PIN_D1,  PIN_C2  
    , PIN_C0,  PIN_D4,  PIN_D7,  PIN_E0  
    , PIN_E1,  PIN_D2, PIN_D5, PIN_C4 
    , PIN_C1, PIN_D3, PIN_D0, PIN_C4 
    };

// Position of lights physically
/* usb  ||
 * _____||_____
 * |??|??|??|F0|
 * |??|??|??|F2|
 * |??|??|F3|F4|
 * |B4|B6|F5|F6|
 * -------------
 */

//Non working: F1, F7, E6, E7, B0, B1, B2, B3, B5

int light_positions[TILE_COUNT] = // TODO: change so is correct
    { PIN_F7,  PIN_F7, PIN_F7, PIN_F0  
    , PIN_F7,  PIN_F7, PIN_F7, PIN_F2  
    , PIN_F7,  PIN_F7, PIN_F3, PIN_F4 
    , PIN_B4,  PIN_B6, PIN_F5, PIN_F6 
    };

int notes[4][4] = {
    { 61, 66, 68, 73 },
    { 52, 54, 59, 64 },
    { 45, 49, 52, 59 },
    { 47, 51, 54, 59 }
};
 
Controller controller(button_positions, light_positions);

void toggle_row(int row, bool val) {
    digitalWrite(controller.light_positions.get_square(row, 1), val);
    digitalWrite(controller.light_positions.get_square(row, 2), val);
    digitalWrite(controller.light_positions.get_square(row, 3), val);
    digitalWrite(controller.light_positions.get_square(row, 4), val);
};

void all_off() {
    usbMIDI.sendNoteOff(notes[0][0], 127, 1);
    usbMIDI.sendNoteOff(notes[0][1], 127, 1);
    usbMIDI.sendNoteOff(notes[0][2], 127, 1);
    usbMIDI.sendNoteOff(notes[0][3], 127, 1);

    usbMIDI.sendNoteOff(notes[1][1], 127, 1);
    usbMIDI.sendNoteOff(notes[1][0], 127, 1);
    usbMIDI.sendNoteOff(notes[1][2], 127, 1);
    usbMIDI.sendNoteOff(notes[1][3], 127, 1);

    usbMIDI.sendNoteOff(notes[2][0], 127, 1);
    usbMIDI.sendNoteOff(notes[2][1], 127, 1);
    usbMIDI.sendNoteOff(notes[2][2], 127, 1);
    usbMIDI.sendNoteOff(notes[2][3], 127, 1);

    usbMIDI.sendNoteOff(notes[3][0], 127, 1);
    usbMIDI.sendNoteOff(notes[3][1], 127, 1);
    usbMIDI.sendNoteOff(notes[3][2], 127, 1);
    usbMIDI.sendNoteOff(notes[3][3], 127, 1);
}

// callback when midi data received 
// https://github.com/2kohm/Teensy-USB-MIDI-CLOCK
void real_time_system(uint8_t realtimebyte) {
    // TODO: update controller tempo
    // possibly send midi notes here?

    if(realtimebyte == 248) { 
        counter++; 
        if(counter % 24 == 0) {
            // do every quarter
            switch(row) {
                case 0:   
                    digitalWrite(PIN_B4, 1);

                    digitalWrite(PIN_F0, 0);
                    digitalWrite(PIN_F2, 0);
                    digitalWrite(PIN_F4, 0);
                    digitalWrite(PIN_F6, 0);

                    all_off();

                    if (digitalRead(controller.button_positions.positions[0])) {
                        usbMIDI.sendNoteOn(notes[pattern][0], 127, 1);
                    }
                    if (digitalRead(controller.button_positions.positions[4])) {
                        usbMIDI.sendNoteOn(notes[pattern][1], 127, 1);
                    }
                    if (digitalRead(controller.button_positions.positions[8])) {
                        usbMIDI.sendNoteOn(notes[pattern][2], 127, 1);
                    }
                    if (digitalRead(controller.button_positions.positions[12])) {
                        usbMIDI.sendNoteOn(notes[pattern][3], 127, 1);
                    }

                    row++;
                    break;
                case 1:
                    digitalWrite(PIN_B4, 0);

                    digitalWrite(PIN_B6, 1);

                    all_off();

                    if (digitalRead(controller.button_positions.positions[1])) {
                        usbMIDI.sendNoteOn(notes[pattern][0], 127, 1);
                    }
                    if (digitalRead(controller.button_positions.positions[5])) {
                        usbMIDI.sendNoteOn(notes[pattern][1], 127, 1);
                    }
                    if (digitalRead(controller.button_positions.positions[9])) {
                        usbMIDI.sendNoteOn(notes[pattern][2], 127, 1);
                    }
                    if (digitalRead(controller.button_positions.positions[13])) {
                        usbMIDI.sendNoteOn(notes[pattern][3], 127, 1);
                    }

                    row++;
                    break;
                case 2:
                    digitalWrite(PIN_B6, 0);

                    digitalWrite(PIN_F3, 1);
                    digitalWrite(PIN_F5, 1);

                    all_off();

                    if (digitalRead(controller.button_positions.positions[2])) {
                        usbMIDI.sendNoteOn(notes[pattern][0], 127, 1);
                    }
                    if (digitalRead(controller.button_positions.positions[6])) {
                        usbMIDI.sendNoteOn(notes[pattern][1], 127, 1);
                    }
                    if (digitalRead(controller.button_positions.positions[10])) {
                        usbMIDI.sendNoteOn(notes[pattern][2], 127, 1);
                    }
                    if (digitalRead(controller.button_positions.positions[14])) {
                        usbMIDI.sendNoteOn(notes[pattern][3], 127, 1);
                    }

                    row++;
                    break;
                case 3:
                    digitalWrite(PIN_F3, 0);
                    digitalWrite(PIN_F5, 0);

                    digitalWrite(PIN_F0, 1);
                    digitalWrite(PIN_F2, 1);
                    digitalWrite(PIN_F4, 1);
                    digitalWrite(PIN_F6, 1);

                    all_off();

                    if (digitalRead(controller.button_positions.positions[3])) {
                        usbMIDI.sendNoteOn(notes[pattern][0], 127, 1);
                    }
                    if (digitalRead(controller.button_positions.positions[7])) {
                        usbMIDI.sendNoteOn(notes[pattern][1], 127, 1);
                    }
                    if (digitalRead(controller.button_positions.positions[11])) {
                        usbMIDI.sendNoteOn(notes[pattern][2], 127, 1);
                    }
                    if (digitalRead(controller.button_positions.positions[15])) {
                        usbMIDI.sendNoteOn(notes[pattern][3], 127, 1);
                    }

                    row = 0;
                    break;
            }
        }
        // every 4 measures
        if (counter % 384 == 0) {
            if (pattern == 3) {
                pattern = 0;
            } else {
                pattern++;
            }
        }
    }

    if(realtimebyte == START || realtimebyte == CONTINUE) { 
        counter = 0; 
    }

    if(realtimebyte == STOP) { 
        counter = 0; 
        // WHEN DAW STOPS
    }
}

void setup()
{
    Serial.begin(9600);
    usbMIDI.setHandleRealTimeSystem(real_time_system);
}

void loop()
{ 
    usbMIDI.read();
    controller.update();
}
