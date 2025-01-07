#include "Task3.h"
#include "MessageUtils.h"

State3 state3; // Initialize the state machine for Task 3
char buffer[10]; // Buffer to hold the string representation of the float

void initStreamADC() {
    state3 = INIT3;
}

void StreamADC() {
    switch (state3) {
        case INIT3:
            //Serial.println("Task 3 INIT");
            state3 = STATE3_2;
            break;
        case STATE3_1:
            state3 = STATE3_2;
            break;
        case STATE3_2:
            int adcValue = analogRead(A7); // Read from ADC pin A7
            
            float voltage = (adcValue / 1023.0) * 5.0; // Assuming 10-bit ADC with 5V reference
            
            // Convert the float to a string (single-precision IEEE 754 format)
            dtostrf(voltage, 6, 2, buffer);  // Converts float to string in 'buffer'

            // Send the entire buffer as a single message (each byte in the buffer represents a character)
            sendMessage(3, (byte*)buffer);  // Send the entire buffer with its length

            state3 = STATE3_1;
            break;
    }
}
