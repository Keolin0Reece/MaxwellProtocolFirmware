#ifndef TASK2_H
#define TASK2_H
#include "ProtocolMessage.h"

#include <Arduino.h>

// State machine for Task 1
enum State2 { INIT2, STATE2_1, STATE2_2 };

// Function declaration for Task 1
void sendMessageTask();
void initsendMessageTask();
void splitIntegerToBytes(int number, byte* bytes);

extern State2 state2;

#endif // TASK2_H
