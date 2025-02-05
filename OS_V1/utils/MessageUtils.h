#ifndef MESSAGEUTILS_H
#define MESSAGEUTILS_H

#include <Arduino.h>
#include "../protocol/ProtocolMessage.h"

// Function to calculate checksum
byte calculateChecksum(byte messageID, byte* data, byte dataLength);

// Function to send the message as a single byte array
void sendMessage(byte messageID, byte* data, byte length);

ProtocolMessage decodeMessage(byte* message);

#endif // MESSAGEUTILS_H
