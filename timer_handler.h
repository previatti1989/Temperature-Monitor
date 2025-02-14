#ifndef TIMER_HANDLER_H
#define TIMER_HANDLER_H

#include <windows.h>

// Function to setup the timer
void setup_timer(volatile int *timer_triggered);

// Function to cleanup the timer
void cleanup_timer();

#endif // TIMER_HANDLER_H