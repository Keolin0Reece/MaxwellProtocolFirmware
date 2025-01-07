#include "Task1.h"
  #include "MessageUtils.h"

State1 state1; // Initialize the state machine for Task 1
const int pin = 3; // Pin to read input
char* state = "0";

void initDOITask() {
    state1 = INIT1;
    DDRD |= (1 << DDD3);  // Set bit 3 of DDRD to 1 (output)
}

void DOITask() {
    switch (state1) {
        case INIT1:
            //Serial.println("Task 1 INIT");
            state1 = STATE1_1;
            break;
        case STATE1_1: {
            state1 = STATE1_1;
            break;
        }
        case STATE1_2:
            PORTD ^= (1 << PD3);  // XOR PD3 with 1 (this will toggle the pin)
            bool currentState = digitalRead(pin);
            state = currentState ? "1" : "0";
            sendMessage(1, state);
            state1 = STATE1_1;
            break;
    }
}
