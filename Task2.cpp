#include "Task2.h"

State2 state2; // Initialize the state machine for Task 2

void initTask2() {
    state2 = INIT2;
}

void task2() {
    switch (state2) {
        case INIT2:
            Serial.println("Task 2 INIT");
            state2 = STATE2_1;
            break;
        case STATE2_1:
            Serial.println("Task 2 State 1");
            state2 = STATE2_2;
            break;
        case STATE2_2:
            Serial.println("Task 2 State 2");
            state2 = STATE2_1;
            break;
    }
}
