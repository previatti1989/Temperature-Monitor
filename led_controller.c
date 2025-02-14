#include "led_controller.h"
#include "system_config.h"

void update_leds(float value, SensorType sensor, LedStatus* leds) {
    switch (sensor) {
    case SENSOR_TEMP:
        leds->green = (value < TEMP_WARN_THRESHOLD) ? LED_ON : LED_OFF;
        leds->yellow = (value >= TEMP_WARN_THRESHOLD && value < TEMP_CRIT_THRESHOLD) ? LED_ON : LED_OFF;
        leds->red = (value >= TEMP_CRIT_THRESHOLD) ? LED_ON : LED_OFF;
        break;

    case SENSOR_PRESS:
        leds->green = (value < PRESS_WARN_THRESHOLD) ? LED_ON : LED_OFF;
        leds->yellow = (value >= PRESS_WARN_THRESHOLD && value < PRESS_CRIT_THRESHOLD) ? LED_ON : LED_OFF;
        leds->red = (value >= PRESS_CRIT_THRESHOLD) ? LED_ON : LED_OFF;
        break;

    case SENSOR_MAG:
        leds->green = (value < HEAD_WARN_THRESHOLD) ? LED_ON : LED_OFF;
        leds->yellow = (value >= HEAD_WARN_THRESHOLD && value < HEAD_CRIT_THRESHOLD) ? LED_ON : LED_OFF;
        leds->red = (value >= HEAD_CRIT_THRESHOLD) ? LED_ON : LED_OFF;
        break;
    }
}