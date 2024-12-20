#include <Arduino.h>
#include <avr/sleep.h>
#include <avr/interrupt.h>
#include <C:\Users\impul\Documents\ArduinoOS\OS_V1\Task1.h>

// Task structure
struct Task {
    void (*run)(); // Function pointer to the task function
    uint16_t period; // Period in milliseconds
    uint16_t elapsedTime; // Time since the task was last run
};

// Task array
const uint8_t numTasks = 1;
Task tasks[numTasks] = {
    {task1, 250, 0} // Task 1 runs every 1000 ms
    //{task2, 250, 0},  // Task 2 runs every 500 ms
    //{task3, 250, 0}  // Task 3 runs every 2000 ms
};

// Time tracking
unsigned long lastUpdateTime = 0;
volatile bool timerTriggered = false; // Flag for timer interrupt

void setup() {
    Serial.begin(9600);

    // Initialize state machines
    initTask1();
    //initTask2();
    //initTask3();

    lastUpdateTime = millis();

    // Configure sleep mode
    set_sleep_mode(SLEEP_MODE_IDLE); // Use idle mode to keep timers running

    // Configure Timer1 for 250ms interrupt
    noInterrupts();
    TCCR1A = 0; // Clear Timer1 control register A
    TCCR1B = 0; // Clear Timer1 control register B
    TCNT1 = 0;  // Reset Timer1 counter
    OCR1A = 31250 / 4 - 1; // Set compare match value for 250ms (16MHz/256 prescaler)
    TCCR1B |= (1 << WGM12); // Configure Timer1 for CTC mode
    TCCR1B |= (1 << CS12);  // Set 256 prescaler
    TIMSK1 |= (1 << OCIE1A); // Enable Timer1 compare interrupt
    interrupts();
}

ISR(TIMER1_COMPA_vect) {
    timerTriggered = true; // Set the flag when the timer triggers
}

void loop() {
    if (timerTriggered) {
        timerTriggered = false; // Reset the flag

        unsigned long currentTime = millis();
        unsigned long deltaTime = currentTime - lastUpdateTime;

        for (uint8_t i = 0; i < numTasks; i++) {
            tasks[i].elapsedTime += deltaTime;

            if (tasks[i].elapsedTime >= tasks[i].period) {
                tasks[i].run();
                tasks[i].elapsedTime = 0;
            }
        }

        lastUpdateTime = currentTime;
    }

    // Sleep until the next interrupt
    sleep_enable();
    sleep_cpu();
    sleep_disable();
}
