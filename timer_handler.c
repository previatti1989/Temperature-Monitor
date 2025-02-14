#include "timer_handler.h"
#include <stdio.h>
#include <windows.h>

HANDLE hTimer = NULL;
HANDLE hTimerQueue = NULL;

// Timer callback function
void CALLBACK TimerRoutine(PVOID lpParam, BOOLEAN TimerOrWaitFired) {
    *(volatile int*)lpParam = 1;  // Set flag when timer fires
}

// Setup the timer to trigger every 100ms
void setup_timer(volatile int *timer_triggered) {
    hTimerQueue = CreateTimerQueue();
    if (!CreateTimerQueueTimer(&hTimer, hTimerQueue, TimerRoutine, (PVOID)timer_triggered, 100, 100, WT_EXECUTEDEFAULT)) {
        printf("Failed to create timer.\n");
    }
}

// Cleanup timer resources
void cleanup_timer() {
    DeleteTimerQueue(hTimerQueue);
}