#include "protocol.h"
#include <string.h>

// Helper function to write an integer to a buffer (little-endian)
static void writeIntToBuffer(uint8_t* buffer, int value) {
    buffer[0] = value & 0xFF;
    buffer[1] = (value >> 8) & 0xFF;
    buffer[2] = (value >> 16) & 0xFF;
    buffer[3] = (value >> 24) & 0xFF;
}

// Helper function to read an integer from a buffer (little-endian)
static int readIntFromBuffer(const uint8_t* buffer) {
    return (int)(buffer[0] | (buffer[1] << 8) | (buffer[2] << 16) | (buffer[3] << 24));
}

// Helper function to write a float to a buffer
static void writeFloatToBuffer(uint8_t* buffer, float value) {
    memcpy(buffer, &value, sizeof(float));
}

// Helper function to read a float from a buffer
static float readFloatFromBuffer(const uint8_t* buffer) {
    float value;
    memcpy(&value, buffer, sizeof(float));
    return value;
}

// Encode a ProtocolMessage_t into a byte buffer
int encodeMessage(const ProtocolMessage_t* message, uint8_t* buffer, uint16_t bufferLength) {
    if (!message || !buffer || bufferLength < 6) { // Minimum buffer size = 1 byte (ID) + 4 bytes (data) + 1 byte (length)
        return -1;
    }

    // Write the message ID
    buffer[0] = (uint8_t)message->messageID;

    // Write the message payload based on the message ID
    switch (message->messageID) {
        case MESSAGE_SET_PIN:
        case MESSAGE_GET_PIN:
            // Integer data (4 bytes)
            if (bufferLength < 5) return -1; // Ensure buffer is large enough
            writeIntToBuffer(&buffer[1], message->data.setPinData.pinValue);
            return 5; // 1 byte ID + 4 bytes data

        case MESSAGE_GET_ADC:
        case MESSAGE_STREAM_ADC:
            // Float data (4 bytes)
            if (bufferLength < 5) return -1; // Ensure buffer is large enough
            writeFloatToBuffer(&buffer[1], message->data.adcData.adcValue);
            return 5; // 1 byte ID + 4 bytes data

        default:
            // Unsupported message ID
            return -1;
    }
}

// Decode a byte buffer into a ProtocolMessage_t
int decodeMessage(const uint8_t* buffer, uint16_t bufferLength, ProtocolMessage_t* message) {
    if (!buffer || !message || bufferLength < 5) { // Minimum valid message = 1 byte ID + 4 bytes data
        return -1;
    }

    // Read the message ID
    message->messageID = (MessageID_t)buffer[0];

    // Decode the message payload based on the message ID
    switch (message->messageID) {
        case MESSAGE_SET_PIN:
        case MESSAGE_GET_PIN:
            // Integer data (4 bytes)
            if (bufferLength < 5) return -1; // Ensure buffer is large enough
            message->data.setPinData.pinValue = readIntFromBuffer(&buffer[1]);
            return 0;

        case MESSAGE_GET_ADC:
        case MESSAGE_STREAM_ADC:
            // Float data (4 bytes)
            if (bufferLength < 5) return -1; // Ensure buffer is large enough
            message->data.adcData.adcValue = readFloatFromBuffer(&buffer[1]);
            return 0;

        default:
            // Unsupported message ID
            return -1;
    }
}
