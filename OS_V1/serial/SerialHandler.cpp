#include "SerialHandler.h"
#include "../utils/MessageUtils.h"
#include "../tasks/Task1.h"
#include "../tasks/Task2.h"
#include "../tasks/Task3.h"
#include <Arduino.h>

/************************** Definitions ****************************/
/** Maximum size of the input buffer for serial communication */
#define BUFFER_SIZE 256

/************************** Global Variables **********************/
/** Buffer to store incoming serial data */
byte inputBuffer[BUFFER_SIZE];
/** Current position in the input buffer */
uint8_t bufferIndex = 0;

/************************** Function Definitions ******************/
/**
 * @brief Handles incoming serial communication
 * 
 * This function reads incoming serial data byte by byte and stores it in a buffer
 * until a newline or carriage return character is received. Once a complete
 * message is received, it triggers state changes and processes the message.
 * 
 * Features:
 * - Implements buffer overflow protection
 * - Handles both '\n' and '\r' as message terminators
 * - Automatically resets buffer after message processing
 * 
 * @note The function should be called regularly in the main loop
 */
void handleSerialInput() {
    // Process all available serial data
    while (Serial.available() > 0) {
        // Read a single byte from serial port
        char incomingByte = Serial.read();

        // Check for message termination characters
        if (incomingByte == '\n' || incomingByte == '\r') {
            // Update state machine
            state1 = STATE1_2;
            
            // Reset buffer for next message
            bufferIndex = 0;
        } 
        else {
            // Handle normal character input
            if (bufferIndex < BUFFER_SIZE - 1) {
                // Add byte to buffer if space is available
                inputBuffer[bufferIndex++] = incomingByte;
            } 
            else {
                // Handle buffer overflow condition
                Serial.println("Input buffer overflow!");
                bufferIndex = 0;  // Reset buffer to prevent data corruption
            }
        }
    }
}