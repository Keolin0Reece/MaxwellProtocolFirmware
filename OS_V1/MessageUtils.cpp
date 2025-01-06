#include "MessageUtils.h"

// Function to calculate checksum: sum of Message ID and Data bytes, mod 255
byte calculateChecksum(byte messageID, byte* data, byte dataLength) {
    byte sum = messageID;  // Start with Message ID
    for (byte i = 0; i < dataLength; i++) {
        sum += data[i];  // Add each data byte
    }
    return sum % 255;  // Return checksum mod 255
}

// Function to send the message as a single byte array
void sendMessage(byte messageID, byte* data, byte dataLength) {
    byte messageLength = 3 + dataLength + 1;  // Total message length (Header + Data + Checksum)
    byte messageTypeID = 0;  // Fixed value for Message Type ID
    
    byte checksum = calculateChecksum(messageID, data, dataLength);  // Calculate checksum

    // Allocate a byte array to hold the entire message
    byte message[messageLength];

    // Fill the message array
    message[0] = messageID;        // Message ID
    message[1] = dataLength;       // Message Length
    message[2] = messageTypeID;    // Message Type ID

    // Add Data bytes
    for (byte i = 0; i < dataLength; i++) {
        message[3 + i] = data[i];  // Starting from index 3, add the data bytes
    }

    // Add Checksum at the end
    message[messageLength - 1] = checksum;

    // Send the entire message array at once
    Serial.write(message, messageLength);
    Serial.write('\n');   
}
