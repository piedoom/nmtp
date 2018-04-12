#include <math.h>

/// Contains the pin layout and connections for a multiplexer,
class Mux {
    private:
        /// The pins used to shift the incoming value.  
        int s0;
        int s1;
        int s2;
        int s3;

        void set_pins(bool a, bool b, bool c, bool d);

        /// The pin that actually reads a value.  For example,
        /// SIG
        int signal_pin;
        
    public: 
        /// Return all  values
        int read(int channel);
        void read_all(bool *values);
        Mux();
        Mux(int _s0, int _s1, int _s2, int _s3, int _signal_pin);
};
