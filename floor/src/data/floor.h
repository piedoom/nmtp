#pragma once
#define GRID_SIZE 4

/// data struct representing the buttons or lights on the floor
/// Should and does not keep track of buttons states, only positions.
struct Floor {
    /// physical position of tiles
    int* positions;

    /// get specific tiles, etc.
    /* usb ||
    * _____||_____
    * |01|02|03|04|
    * |05|06|07|08|
    * |09|10|11|12|
    * |13|14|15|16|
    * -------------
    */ 
    bool get_square(int x, int y) {
        // return the pin of choice.  from 0,0
        return positions[(GRID_SIZE * y) + x];
    }
};
