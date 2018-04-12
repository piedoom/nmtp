#include "mux.h"
#include <Arduino.h>

int Mux::read(int channel) {
    int controlPin[] = {s0, s1, s2, s3}; 
    int muxChannel[16][4] = { 
        {0,0,0,0}, //channel 0 
        {1,0,0,0}, //channel 1 
        {0,1,0,0}, //channel 2 
        {1,1,0,0}, //channel 3 
        {0,0,1,0}, //channel 4 
        {1,0,1,0}, //channel 5 
        {0,1,1,0}, //channel 6 
        {1,1,1,0}, //channel 7 
        {0,0,0,1}, //channel 8 
        {1,0,0,1}, //channel 9 
        {0,1,0,1}, //channel 10 
        {1,1,0,1}, //channel 11 
        {0,0,1,1}, //channel 12 
        {1,0,1,1}, //channel 13 
        {0,1,1,1}, //channel 14 
        {1,1,1,1} //channel 15 
    }; 

    //loop through the 4 sig 
    for(int i = 0; i < 4; i ++){ 
        digitalWrite(controlPin[i], muxChannel[channel][i]); 
    } 

    //read the value at the SIG pin 
    int val = digitalRead(signal_pin); 

    //return the value 
    return val; 
}

void Mux::read_all(bool *values) {
    set_pins(0,0,0,0);
    values[0] = digitalRead(signal_pin);

    set_pins(1,0,0,0);
    values[1] = digitalRead(signal_pin);

    set_pins(0,1,0,0);
    values[2] = digitalRead(signal_pin);

    set_pins(1,1,0,0);
    values[3] = digitalRead(signal_pin);

    set_pins(0,0,1,0);
    values[4] = digitalRead(signal_pin);

    set_pins(1,0,1,0);
    values[5] = digitalRead(signal_pin);

    set_pins(0,1,1,0);
    values[6] = digitalRead(signal_pin);

    set_pins(1,1,1,0);
    values[7] = digitalRead(signal_pin);

    set_pins(0,0,0,1);
    values[8] = digitalRead(signal_pin);

    set_pins(1,0,0,1);
    values[9] = digitalRead(signal_pin);

    set_pins(0,1,0,1);
    values[10] = digitalRead(signal_pin);

    set_pins(1,1,1,0);
    values[11] = digitalRead(signal_pin);

    set_pins(0,0,1,1);
    values[12] = digitalRead(signal_pin);

    set_pins(1,0,1,1);
    values[13] = digitalRead(signal_pin);

    set_pins(0,1,1,1);
    values[14] = digitalRead(signal_pin);

    set_pins(1,1,1,1);
    values[15] = digitalRead(signal_pin);
};

void Mux::set_pins(bool a, bool b, bool c, bool d) {
    digitalWrite(s0, a);
    digitalWrite(s1, b);
    digitalWrite(s2, c);
    digitalWrite(s3, d);
}

Mux::Mux(int _s0, int _s1, int _s2, int _s3, int _signal_pin) {
    s0 = _s0;
    s1 = _s1;
    s2 = _s2;
    s3 = _s3;

    pinMode(s0, OUTPUT);
    pinMode(s1, OUTPUT);
    pinMode(s2, OUTPUT);
    pinMode(s3, OUTPUT);

    signal_pin = _signal_pin;
};

Mux::Mux() { };





