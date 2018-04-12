#include <math.h>

/// Contains the pin layout and connections for a multiplexer,
class Mux {
    private:
        /// The pins used to shift the incoming value.  
        int s0;
        int s1;
        int s2;
        int s3;

        /// The pin that actually reads a value.  For example,
        /// SIG
        int signal_pin;
        
    public: 
        /// Return all  values
        bool* readAll(int pin); 
};
