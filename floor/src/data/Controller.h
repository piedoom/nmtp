#pragma once
#include "data/state.h"
#include "data/floor.h"
#define GRID_SIZE 4


class Controller {
    private:
        State state;
        Floor light_positions;
        Floor button_positions;

    public:
        State get_state();
        Controller(int* b_arr, int* l_arr);
        void update();
};