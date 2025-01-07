#include "SerialHandler.h"
#include "MessageUtils.h"
#include "Task1.h"
#include "Task2.h"
#include "Task3.h"
#include <Arduino.h>

#define BUFFER_SIZE 256 // Define a buffer size

byte inputBuffer[BUFFER_SIZE]; // Buffer to hold the incoming string
uint8_t bufferIndex = 0;       // Index to track the current position in the buffer

void handleSerialInput() {
    while (Serial.available() > 0) {
        char incomingByte = Serial.read(); // Read a single byte

        // Check for newline or carriage return as the end of the string
        if (incomingByte == '\n' || incomingByte == '\r') {
            bufferIndex = 0; // Reset the buffer index for the next string
            switch(inputBuffer[0]){
              case 0x01:
                state1 = STATE1_2;
                break;
              case 0x02:

                break;
              case 0x03:

                break;
            }
        } else {
            // Add the byte to the buffer if there's space
            if (bufferIndex < BUFFER_SIZE - 1) {
                inputBuffer[bufferIndex++] = incomingByte;
            } else {
                Serial.println("Input buffer overflow!");
                bufferIndex = 0; // Reset the buffer index to prevent corruption
            }
        }
    }
}
