#include "MessageUtils.h"
#include "ProtocolMessage.h"

// Function to calculate checksum: sum of Message ID and Data bytes, mod 255
byte calculateChecksum(byte messageID, byte* data, byte dataLength) {
    byte sum = messageID;  // Start with Message ID
    for (byte i = 0; i < dataLength; i++) {
        sum += data[i];  // Add each data byte
    }
    return sum % 255;  // Return checksum mod 255
}

// Function to send the message as a single byte array
void sendMessage(byte messageID, byte* data, byte length) {
    byte dataLength = length;

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

ProtocolMessage decodeMessage(byte* message) {
  byte dataLength = 0;
  while (message[dataLength] != '\0') {
        dataLength++; 
    }
  byte messageID = message[0];
  byte messageLength = message[1];
  byte messageTypeID = message[2];

  byte* data = new byte[messageLength];
  memcpy(data, message + 3, messageLength);

  byte checkSum = message[dataLength - 1];
  bool isValid = checkSum == calculateChecksum(messageID, data, dataLength);
  
  ProtocolMessage protocolM;
  protocolM.MessageID = messageID;
  protocolM.MessageLength = messageLength;     // Length of the data array
  protocolM.MessageTypeID = messageTypeID;     // Example Type ID
  protocolM.Data = data;
  protocolM.Checksum = checkSum;
  protocolM.IsValidChecksum = isValid;

}