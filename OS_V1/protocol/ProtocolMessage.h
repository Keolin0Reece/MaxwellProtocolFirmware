#ifndef PROTOCOL_MESSAGE_H
#define PROTOCOL_MESSAGE_H

#include <Arduino.h>

// ========================== PROTOCOL MESSAGE STRUCTURE ========================== //
struct ProtocolMessage {
    byte MessageID;        // Message identifier
    byte MessageLength;    // Length of the message
    byte MessageTypeID;    // Message type
    byte* Data;            // Pointer to the data payload
    byte Checksum;         // Checksum for integrity verification
    bool IsValidChecksum;  // Checksum validity flag

    /**
     * @brief Constructor initializes values to defaults.
     */
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