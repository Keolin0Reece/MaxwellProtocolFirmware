#ifndef TASK1_H
#define TASK1_H

#include <Arduino.h>
#include "../protocol/ProtocolMessage.h"

/************************** Type Definitions ***********************/
/**
 * @brief States for the DOI task state machine
 * 
 */
enum State1 { 
    INIT1,      
    STATE1_1,   
    STATE1_2    
};

/************************** Function Declarations ******************/
/**
 * @brief Main processing function for the DOI task
 * 
 * Implements the state machine logic for digital output control.
 * Should be called regularly in the main program loop.
 */
void DOITask();

/**
 * @brief Initialization function for the DOI task
 * 
 * Sets up the initial state and any required configurations
 * for the Digital Output Interface task.
 */
void initDOITask();

/************************** External Declarations *****************/
/** @brief Current state of the DOI task state machine */
extern State1 state1;

/** @brief Protocol message structure for communication */
extern ProtocolMessage proMess;

#endif // TASK1_H