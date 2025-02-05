#include <Arduino.h>
#include <avr/sleep.h>
#include <avr/interrupt.h>
#include "tasks/Task1.h"
#include "tasks/Task2.h"
#include "tasks/Task3.h"
#include "serial/SerialHandler.h"
#include "protocol/Protocol.h"

// ========================== TASK MANAGEMENT ========================== //

// Structure defining a scheduled task
struct Task {
    void (*run)();       
    uint16_t period;     
    uint16_t elapsedTime;
};

// Define active tasks (Uncomment to enable specific tasks)
const uint8_t numTasks = 1;
Task tasks[numTasks] = {
    {DOITask, 250, 0}  // Task 1: Executes every 250ms
    //{sendMessageTask, 250, 0}  // Task 2: Executes every 250ms
    //{StreamADC, 250, 0}  // Task 3: Executes every 250ms
};

// ========================== GLOBAL VARIABLES ========================== //

unsigned long lastUpdateTime = 0; 
volatile bool timerTriggered = false;

// ========================== FUNCTION PROTOTYPES ========================== //

void configureTimer1();
void sleepModeSetup();

// ========================== SETUP FUNCTION ========================== //
void setup() {
    Serial.begin(19200); 

    // Initialize individual tasks (Ensure matching task definitions)
    initDOITask();
    initsendMessageTask();
    //initStreamADC();

    pinMode(3, OUTPUT);  

    lastUpdateTime = millis(); 

    configureTimer1(); 
    sleepModeSetup();  
}

// ========================== TIMER CONFIGURATION ========================== //
/**
 * Configures Timer1 to generate an interrupt every 250ms.
 */
void configureTimer1() {
    noInterrupts();      // Disable interrupts during setup
    TCCR1A = 0;         // Reset Timer1 control register A
    TCCR1B = 0;         // Reset Timer1 control register B
    TCNT1 = 0;          // Reset Timer1 counter

    // Set compare match value for 250ms (16MHz / 256 prescaler)
    OCR1A = 31250 / 4 - 1; 
    TCCR1B |= (1 << WGM12); // Configure Timer1 in CTC (Clear Timer on Compare Match) mode
    TCCR1B |= (1 << CS12);  // Set prescaler to 256
    TIMSK1 |= (1 << OCIE1A); // Enable Timer1 Compare Match A interrupt

    interrupts();  // Re-enable global interrupts
}

// ========================== TIMER INTERRUPT HANDLER ========================== //
ISR(TIMER1_COMPA_vect) {
    timerTriggered = true;
}

// ========================== TASK SCHEDULER ========================== //
/**
 * Executes tasks based on their scheduled timing.
 */
void runScheduledTasks() {
    unsigned long currentTime = millis();
    unsigned long deltaTime = currentTime - lastUpdateTime;

    for (uint8_t i = 0; i < numTasks; i++) {
        tasks[i].elapsedTime += deltaTime;

        if (tasks[i].elapsedTime >= tasks[i].period) {
            tasks[i].run();           // Execute the scheduled task
            tasks[i].elapsedTime = 0; // Reset elapsed time counter
        }
    }
    
    lastUpdateTime = currentTime;
}

// ========================== SLEEP MODE SETUP ========================== //
/**
 * Configures sleep mode to reduce power consumption between task executions.
 */
void sleepModeSetup() {
    set_sleep_mode(SLEEP_MODE_IDLE);
}

// ========================== MAIN LOOP ========================== //
void loop() {
    if (timerTriggered) {
        timerTriggered = false;
        runScheduledTasks(); 
    }

    // Continuously handle message sending in real-time
    sendMessageTask();

    // Handle serial data
    //handleSerialInput();

    // Enter low-power sleep mode until the next interrupt
    sleep_enable();
    sleep_cpu();
    sleep_disable();
}
