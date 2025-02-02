#ifndef TASK3_H
#define TASK3_H

#include <Arduino.h>

// State machine for Task 3
enum State3 { INIT3, STATE3_1, STATE3_2 };

// Function declaration for Task 1
void StreamADC();
void initStreamADC();
void floatToBytes(float value, byte* bytes);

extern State3 state3;

#endif // TASK3_H
