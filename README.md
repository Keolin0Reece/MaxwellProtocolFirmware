# Arduino Protocol Implementation Project

## Overview
This project implements a custom communication protocol for Arduino, featuring digital I/O control, analog reading, and message streaming capabilities. The implementation includes a state machine-based approach for handling different tasks and a robust serial communication interface.

## Project Structure
```
├── protocol/
│   ├── protocol.h
│   ├── ProtocolMessage.h    # Class defining a message as an array of bytes
│   └── protocol.cpp    # Not used
├── tasks/
│   ├── Task1.h         # Digital Output Interface
│   ├── Task1.cpp
│   ├── Task2.h         # Message Sending & Analog Reading
│   └── Task2.cpp
├── utils/
│   ├── MessageUtils.cpp    # Handles the encoding and decoding of the messages
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
void sendMessage(byte messageID, byte* data, byte length)
```
- Encodes structured messages into byte buffers
- Implements message-specific encoding based on message ID
- Sends the encoded message to the serial bus

### Decoding Functions
```cpp
ProtocolMessage decodeMessage(byte* message)
```
- Decodes byte buffers into structured messages
- Validates message format and length
- Returns the class ProtocolMessage that has all the information decoded from the byte array

## Technical Notes
- Minimum message size: 4 bytes (1 byte ID + 1 byte MessageLength + 1 byte MessageTypeID + 0 byte data + 1 byte CheckSum)
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
