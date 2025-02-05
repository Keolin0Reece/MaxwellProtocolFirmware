#ifndef TASK2_H
#define TASK2_H

#include "../protocol/ProtocolMessage.h"
#include <Arduino.h>

/************************** Type Definitions ***********************/
/**
 * @brief States for the message sending task state machine
 */
enum State2 { 
    INIT2,      ///< Initialization state
    STATE2_1,   ///< Main operational state
    STATE2_2    ///< Transition state
};

/************************** Function Declarations ******************/
/**
 * @brief Main processing function for message sending task
 * 
 * Implements the state machine logic for reading analog values
 * and sending messages. Should be called regularly in the main program loop.
 */
void sendMessageTask();

/**
 * @brief Initialization function for message sending task
 * 
 * Sets up the initial state and any required configurations
 * for the message sending functionality.
 */
void initsendMessageTask();

/**
 * @brief Utility function to split 16-bit integer into bytes
 * 
 * @param number The 16-bit integer to split
 * @param bytes Pointer to byte array to store result (must be >= 2 bytes)
 */
void splitIntegerToBytes(int number, byte* bytes);

/************************** External Declarations *****************/
/** @brief Current state of the message sending task state machine */
extern State2 state2;

#endif // TASK2_H