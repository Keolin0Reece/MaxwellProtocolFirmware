#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <stdint.h>

// Message IDs
typedef enum {
    MESSAGE_SET_PIN = 1,      // Sets the value of a pin
    MESSAGE_GET_ADC = 2,      // Requests the ADC value
    MESSAGE_STREAM_ADC = 3,   // Streams ADC values continuously
    MESSAGE_GET_PIN = 4       // Gets the current value of a pin
} MessageID_t;

// Data structures for messages
typedef struct {
    int pinValue; // Data for MESSAGE_SET_PIN and MESSAGE_GET_PIN
} SetPinMessage_t;

typedef struct {
    float adcValue; // Data for MESSAGE_GET_ADC and MESSAGE_STREAM_ADC
} ADCMessage_t;

// Generic message structure
typedef struct {
    MessageID_t messageID; // Message ID
    union {
        SetPinMessage_t setPinData;
        ADCMessage_t adcData;
    } data; // Message data
} ProtocolMessage_t;

// Function prototypes
/**
 * @brief Encodes a ProtocolMessage_t into a byte buffer.
 * 
 * @param message The ProtocolMessage_t to encode.
 * @param buffer The buffer to hold the encoded message.
 * @param bufferLength The length of the buffer.
 * @return int The number of bytes written to the buffer, or -1 on failure.
 */
int encodeMessage(const ProtocolMessage_t* message, uint8_t* buffer, uint16_t bufferLength);

/**
 * @brief Decodes a byte buffer into a ProtocolMessage_t.
 * 
 * @param buffer The buffer containing the encoded message.
 * @param bufferLength The length of the buffer.
 * @param message The ProtocolMessage_t to hold the decoded message.
 * @return int 0 on success, -1 on failure.
 */
int decodeMessage(const uint8_t* buffer, uint16_t bufferLength, ProtocolMessage_t* message);

#endif // PROTOCOL_H
