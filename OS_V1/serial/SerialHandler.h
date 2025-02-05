#ifndef SERIAL_HANDLER_H
#define SERIAL_HANDLER_H

/**
 * @brief Processes incoming serial communication data
 * 
 * This function should be called regularly in the main program loop to:
 * - Read incoming serial data
 * - Buffer the received bytes
 * - Process complete messages when termination characters are received
 * - Handle buffer overflow conditions
 * 
 * @note Maximum buffer size is defined in the implementation file
 * @see SerialHandler.cpp for implementation details
 */
void handleSerialInput();

#endif // SERIAL_HANDLER_H