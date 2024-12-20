#include "Task1.h"

State1 state1; // Initialize the state machine for Task 1

void initTask1() {
    state1 = INIT1;
}

void task1() {
    const int pin = 2; // Pin to read input
    pinMode(pin, INPUT);
    static bool lastState = LOW;

    switch (state1) {
        case INIT1:
            Serial.println("Task 1 INIT");
            state1 = STATE1_1;
            break;
        case STATE1_1: {
            bool currentState = digitalRead(pin);
            if (currentState != lastState) {
                lastState = currentState;
                Serial.print("Task 1 Pin State: ");
                Serial.println(currentState ? "HIGH" : "LOW");
            }
            state1 = STATE1_2;
            break;
        }
        case STATE1_2:
            //Serial.println("Task 1 State 2: Sending status");
            //Serial.println(lastState ? "on" : "off");
            state1 = STATE1_1;
            break;
    }
}
