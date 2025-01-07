#include "Task2.h"
#include "MessageUtils.h"

State2 state2; // Initialize the state machine for Task 2

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

            // Transition to the next state
            state2 = STATE2_2;
            break;

        case STATE2_2:
            // Perform any additional operations if needed (optional)
            // Then return to STATE2_1 to send the message again
            state2 = STATE2_1;
            break;
    }
}


