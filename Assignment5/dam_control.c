/*
Compile: make dam_control
Run: ./dam_control
make dam_control && ./dam_control
*/

#include "base.h"

enum dam_mode_e {
    DM_IDLE,
    DM_PUMP_ONE,
    DM_PUMP_TWO,
    DM_PUMP_EMERGENCY,
};

typedef enum dam_mode_e DamMode;

DamMode dam_control(double water_level) {
    // TODO
    return DM_IDLE;
}

void dam_control_test(void) {
    // TODO
    
}

int main(void) {
    dam_control_test();
    return 0;
}
