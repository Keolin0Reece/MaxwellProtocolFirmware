#ifndef PROTOCOL_MESSAGE_H
#define PROTOCOL_MESSAGE_H

#include <Arduino.h>

struct ProtocolMessage {
    byte MessageID;          // Equivalent to byte in C#
    byte MessageLength;      // Equivalent to int in C#
    byte MessageTypeID;      // Equivalent to int in C#
    byte* Data;              // Pointer to an array of bytes
    byte Checksum;           // Equivalent to byte in C#
    bool IsValidChecksum;       // Boolean flag for checksum validity

    // Constructor to initialize values
    ProtocolMessage() 
        : MessageID(0), 
          MessageLength(0), 
          MessageTypeID(0), 
          Data(nullptr), 
          Checksum(0), 
          IsValidChecksum(false) 
    {}
};

#endif // PROTOCOL_MESSAGE_H
