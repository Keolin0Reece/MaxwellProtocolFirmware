#ifndef TASK1_H
#define TASK1_H

#include <Arduino.h>

// State machine for Task 1
enum State1 { INIT1, STATE1_1, STATE1_2 };

// Function declaration for Task 1
void DOITask();
void initDOITask();

extern State1 state1;

#endif // TASK1_H
