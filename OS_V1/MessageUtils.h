#ifndef MESSAGEUTILS_H
#define MESSAGEUTILS_H

#include <Arduino.h>

// Function to calculate checksum
byte calculateChecksum(byte messageID, byte* data, byte dataLength);

// Function to send the message as a single byte array
void sendMessage(byte messageID, byte* data, byte dataLength);

#endif // MESSAGEUTILS_H
