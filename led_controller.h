#ifndef LED_CONTROLLER_H
#define LED_CONTROLLER_H

#include <stdint.h>

typedef enum {
    LED_OFF,
    LED_ON
} LedState;

typedef struct {
    LedState green;
    LedState yellow;
    LedState red;
} LedStatus;

void update_leds(float temp, LedStatus *leds);

#endif // LED_CONTROLLER_H
