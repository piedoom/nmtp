#include "mux/mux.h"
#include "data/state.h"

class Controller {
    private:
        Mux floor_mux;
        State state;
    public:
        State get_state();
        Controller(int _s0, int _s1, int _s2, int _s3, int _signal);
        void update();
};