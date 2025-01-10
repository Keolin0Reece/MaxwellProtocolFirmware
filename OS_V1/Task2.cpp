#include "Task2.h"
#include "MessageUtils.h"

State2 state2; // Initialize the state machine for Task 2
byte bytes[2];

void initsendMessageTask() {
    state2 = INIT2;
}

void sendMessageTask() {
    switch (state2) {
        case INIT2:
            state2 = STATE2_1;
            break;

        case STATE2_1:
            // Send the message
            //sendMessage((byte) 1,"102");
            int sensorVal = analogRead(A7);
            splitIntegerToBytes(sensorVal, bytes);
            sendMessage(1, bytes, 2);
            // Transition to the next state
            state2 = STATE2_1;
            break;

        case STATE2_2:
            state2 = STATE2_1;
            break;
    }
}

void splitIntegerToBytes(int number, byte* bytes) {
  bytes[0] = (number >> 8) & 0xFF; // Most significant byte
  bytes[1] = number & 0xFF;        // Least significant byte
}


