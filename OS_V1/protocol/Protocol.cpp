#include "protocol.h"
#include <string.h>

// ========================== HELPER FUNCTIONS ========================== //

/**
 * @brief Writes an integer to a buffer in little-endian format.
 * @param buffer Destination buffer (must be at least 4 bytes).
 * @param value Integer value to write.
 */
static void writeIntToBuffer(uint8_t* buffer, int value) {
    buffer[0] = value & 0xFF;
    buffer[1] = (value >> 8) & 0xFF;
    buffer[2] = (value >> 16) & 0xFF;
    buffer[3] = (value >> 24) & 0xFF;
}

/**
 * @brief Reads an integer from a buffer in little-endian format.
 * @param buffer Source buffer (must be at least 4 bytes).
 * @return Extracted integer value.
 */
static int readIntFromBuffer(const uint8_t* buffer) {
    return (int)(buffer[0] | (buffer[1] << 8) | (buffer[2] << 16) | (buffer[3] << 24));
}

/**
 * @brief Writes a float value to a buffer.
 * @param buffer Destination buffer (must be at least 4 bytes).
 * @param value Float value to write.
 */
static void writeFloatToBuffer(uint8_t* buffer, float value) {
    memcpy(buffer, &value, sizeof(float));
}

/**
 * @brief Reads a float value from a buffer.
 * @param buffer Source buffer (must be at least 4 bytes).
 * @return Extracted float value.
 */
static float readFloatFromBuffer(const uint8_t* buffer) {
    float value;
    memcpy(&value, buffer, sizeof(float));
    return value;
}

// ========================== MESSAGE ENCODING ========================== //

/**
 * @brief Encodes a ProtocolMessage_t into a byte buffer.
 * @param message Pointer to the ProtocolMessage_t structure.
 * @param buffer Destination buffer.
 * @param bufferLength Length of the buffer.
 * @return Number of bytes written or -1 on failure.
 */
int encodeMessage(const ProtocolMessage_t* message, uint8_t* buffer, uint16_t bufferLength) {
    if (!message || !buffer || bufferLength < 6) {
        return -1; // Minimum valid message size
    }

    buffer[0] = (uint8_t)message->messageID;

    switch (message->messageID) {
        case MESSAGE_SET_PIN:
        case MESSAGE_GET_PIN:
            if (bufferLength < 5) return -1;
            writeIntToBuffer(&buffer[1], message->data.setPinData.pinValue);
            return 5;

        case MESSAGE_GET_ADC:
        case MESSAGE_STREAM_ADC:
            if (bufferLength < 5) return -1;
            writeFloatToBuffer(&buffer[1], message->data.adcData.adcValue);
            return 5;

        default:
            return -1;
    }
}

// ========================== MESSAGE DECODING ========================== //

/**
 * @brief Decodes a byte buffer into a ProtocolMessage_t.
 * @param buffer Source buffer.
 * @param bufferLength Length of the buffer.
 * @param message Pointer to ProtocolMessage_t structure.
 * @return 0 on success, -1 on failure.
 */
int decodeMessage(const uint8_t* buffer, uint16_t bufferLength, ProtocolMessage_t* message) {
    if (!buffer || !message || bufferLength < 5) {
        return -1;
    }

    message->messageID = (MessageID_t)buffer[0];

    switch (message->messageID) {
        case MESSAGE_SET_PIN:
        case MESSAGE_GET_PIN:
            if (bufferLength < 5) return -1;
            message->data.setPinData.pinValue = readIntFromBuffer(&buffer[1]);
            return 0;

        case MESSAGE_GET_ADC:
        case MESSAGE_STREAM_ADC:
            if (bufferLength < 5) return -1;
            message->data.adcData.adcValue = readFloatFromBuffer(&buffer[1]);
            return 0;

        default:
            return -1;
    }
}
