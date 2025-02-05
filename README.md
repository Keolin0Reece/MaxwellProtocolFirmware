# Arduino Protocol Implementation Project

## Overview
This project implements a custom communication protocol for Arduino, featuring digital I/O control, analog reading, and message streaming capabilities. The implementation includes a state machine-based approach for handling different tasks and a robust serial communication interface.

## Project Structure
```
├── protocol/
│   ├── protocol.h
│   └── protocol.cpp
├── tasks/
│   ├── Task1.h         # Digital Output Interface
│   ├── Task1.cpp
│   ├── Task2.h         # Message Sending & Analog Reading
│   └── Task2.cpp
├── utils/
│   ├── MessageUtils.cpp
│   └── MessageUtils.h
├── serial/
│   ├── SerialHandler.h     # Serial Communication Interface
│   └── SerialHandler.cpp
└── OS_V1.ino
```

## Protocol Specification

### Message Format
Each message consists of:
- `MessageID` (1 byte) - Message identifier
- `MessageLength` (1 byte) - Length of the message
- `MessageTypeID` (1 byte) - Message type
- `Data` (pointer to byte array) - Data payload
- `Checksum` (1 byte) - Integrity check
- `IsValidChecksum` (boolean) - Flag indicating checksum validity

### Message Types
1. `MESSAGE_SET_PIN`: Set digital pin state
2. `MESSAGE_GET_PIN`: Read digital pin state
3. `MESSAGE_GET_ADC`: Read analog value
4. `MESSAGE_STREAM_ADC`: Stream analog readings

### Data Encoding
- Integer values: Little-endian format (4 bytes)
- Float values: IEEE 754 format (4 bytes)

## Implementation Details

### Task 1: Digital Output Interface
- State Machine States:
  - `INIT1`: Initialization state
  - `STATE1_1`: Idle state
  - `STATE1_2`: Digital output operation state
- Uses direct port manipulation for efficient pin toggling (PD3)

### Task 2: Message Sending & Analog Reading
- State Machine States:
  - `INIT2`: Initialization state
  - `STATE2_1`: Main operational state (reading & sending)
  - `STATE2_2`: Transition state
- Reads analog values from A7
- Implements 16-bit integer to byte conversion

### Serial Handler
- Buffer Size: 256 bytes
- Handles message framing using newline/carriage return
- Implements buffer overflow protection
- Triggers state transitions upon message reception

## Protocol Implementation

### Encoding Functions
```cpp
int encodeMessage(const ProtocolMessage_t* message, uint8_t* buffer, uint16_t bufferLength)
```
- Encodes structured messages into byte buffers
- Implements message-specific encoding based on message ID
- Returns number of bytes written or -1 on failure

### Decoding Functions
```cpp
int decodeMessage(const uint8_t* buffer, uint16_t bufferLength, ProtocolMessage_t* message)
```
- Decodes byte buffers into structured messages
- Validates message format and length
- Returns 0 on success, -1 on failure

### Helper Functions
- `writeIntToBuffer`: Writes integers in little-endian format
- `readIntFromBuffer`: Reads little-endian integers
- `writeFloatToBuffer`: Writes IEEE 754 float values
- `readFloatFromBuffer`: Reads IEEE 754 float values

## Technical Notes
- Minimum message size: 5 bytes (1 byte ID + 4 bytes data)
- Buffer overflow protection implemented in serial handler
- Direct port manipulation used for efficient digital I/O
- Big-endian byte order used for analog value transmission

## Development Status
This is an internal documentation project. The implementation includes:
- Complete protocol specification
- Message encoding/decoding
- Serial communication handling
- State machine-based task management
- Analog/Digital I/O handling

## Implementation Considerations
- Serial buffer size can be adjusted through `BUFFER_SIZE` define
- State machines can be extended for additional functionality
- Protocol can be expanded for new message types
- Error handling implemented throughout the codebase
