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
        // check that we are using a valid value
        if (x > GRID_SIZE || y > GRID_SIZE)
            return 0;
            // "Grid coordinate is out of bounds"

        // null check positions
        if (!positions)
            return 0;
            // throw "Positions have not been set yet.";

        // return the pin of choice.  This algo treats our 1,1 as 0,0, so lets first
        // fix that
        x -= 1; y -= 1;

        return positions[(GRID_SIZE * y) + x];
    }
};
