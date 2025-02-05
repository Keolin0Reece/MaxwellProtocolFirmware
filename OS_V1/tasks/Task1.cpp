#include "Task1.h"
#include "../utils/MessageUtils.h"

/************************** Global Variables **********************/
/** Current state of Task 1 state machine */
State1 state1;

/** String representation of current pin state */
char* state = "0";

/** Message structure for protocol communication */
ProtocolMessage proMess;

/************************** Function Definitions ******************/
/**
 * @brief Initializes the Digital Output Interface task
 * 
 * Sets the initial state of the Task 1 state machine to INIT1.
 */
void initDOITask() {
    state1 = INIT1;
}

/**
 * @brief Main state machine implementation for Digital Output Interface
 * 
 * Handles the following states:
 * - INIT1: Initialization state, transitions to STATE1_1
 * - STATE1_1: Idle state
 * - STATE1_2: Toggle state for digital output on PD3
 * 
 * @note Direct port manipulation is used for efficient pin toggling
 */
void DOITask() {
    switch (state1) {
        case INIT1:
            // Initialize and transition to first operational state
            //Serial.println("Task 1 INIT");
            state1 = STATE1_1;
            break;

        case STATE1_1: {
            // Maintain current state
            state1 = STATE1_1;
            break;
        }

        case STATE1_2:
            // Toggle digital output
            PORTD ^= (1 << PD3);

            // Return to idle state
            state1 = STATE1_1;
            break;
    }
}