#include "Task3.h"
#include "MessageUtils.h"

State3 state3; // Initialize the state machine for Task 3

void initStreamADC() {
    state3 = INIT3;
}

void StreamADC() {
    switch (state3) {
        case INIT3:
            //Serial.println("Task 3 INIT");
            state3 = STATE3_2;
            break;
        case STATE3_1:
            state3 = STATE3_2;
            break;
        case STATE3_2:

            state3 = STATE3_1;
            break;
    }
}
