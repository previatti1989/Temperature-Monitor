#include "led_controller.h"

// Update LED states based on temp
void update_leds(float temp, LedStatus *leds) {
    if (temp < 5.0 || temp >= 105.0) {
        leds->green = LED_OFF;
        leds->yellow = LED_OFF;
        leds->red = LED_ON;
    } else if (temp >= 85.0) {
        leds->green = LED_OFF;
        leds->yellow = LED_ON;
        leds->red = LED_OFF;
    } else {
        leds->green = LED_ON;
        leds->yellow = LED_OFF;
        leds->red = LED_OFF;
    }
}
