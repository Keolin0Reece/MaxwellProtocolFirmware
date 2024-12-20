#include "Task3.h"

State3 state3; // Initialize the state machine for Task 3

void initTask3() {
    state3 = INIT3;
}

void task3() {
    switch (state3) {
        case INIT3:
            Serial.println("Task 3 INIT");
            state3 = STATE3_1;
            break;
        case STATE3_1:
            Serial.println("Task 3 State 1");
            state3 = STATE3_2;
            break;
        case STATE3_2:
            Serial.println("Task 3 State 2");
            state3 = STATE3_1;
            break;
    }
}
