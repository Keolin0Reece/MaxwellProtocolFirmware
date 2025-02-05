#include "Task2.h"
#include "../utils/MessageUtils.h"

/************************** Global Variables **********************/
/** Current state of Task 2 state machine */
State2 state2;

/** Buffer for storing split bytes of analog reading */
byte bytes[2];

/************************** Function Definitions ******************/
/**
 * @brief Initializes the message sending task
 * 
 * Sets the initial state of the Task 2 state machine to INIT2.
 */
void initsendMessageTask() {
    state2 = INIT2;
}

/**
 * @brief Main state machine implementation for message sending task
 * 
 * The task reads analog value from pin A7, splits it into bytes,
 * and sends it as a message with ID 1.
 */
void sendMessageTask() {
    switch (state2) {
        case INIT2:
            // Initialize and transition to operational state
            state2 = STATE2_1;
            break;

        case STATE2_1:
            // Read analog value from A7
            int sensorVal = analogRead(A7);
            
            // Convert to bytes and send
            splitIntegerToBytes(sensorVal, bytes);
            sendMessage(1, bytes, 2);
            
            // Maintain current state
            state2 = STATE2_1;
            break;

        case STATE2_2:
            // Transition back to main state
            state2 = STATE2_1;
            break;
    }
}

/**
 * @brief Splits a 16-bit integer into two bytes
 * 
 * Converts a 16-bit integer into two 8-bit bytes using bitwise operations.
 * The bytes are stored in big-endian format (most significant byte first).
 * 
 * @param number The 16-bit integer to split
 * @param bytes Pointer to byte array (must be at least 2 bytes long)
 */
void splitIntegerToBytes(int number, byte* bytes) {
    bytes[0] = (number >> 8) & 0xFF;  // Extract most significant byte
    bytes[1] = number & 0xFF;         // Extract least significant byte
}