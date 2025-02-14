#ifndef LED_CONTROLLER_H
#define LED_CONTROLLER_H

#include <stdint.h>
#include "adc_handler.h"

typedef enum {
    LED_OFF,
    LED_ON
} LedState;

typedef struct {
    LedState green;
    LedState yellow;
    LedState red;
} LedStatus;

void update_leds(float value, SensorType sensor, LedStatus *leds);

#endif // LED_CONTROLLER_H
