// holds data for buttons as they need to toggle, etc.
struct Button {
    // immediate on/off state without reguarding toggles, etc.
    bool immediate_state;
    
    // state after calculating the last known value
    bool state;
}