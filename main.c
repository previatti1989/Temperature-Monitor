#include <stdio.h>
#include <math.h>
#include <windows.h>
#include "adc_handler.h"
#include "eeprom_handler.h"
#include "led_controller.h"
#include "system_config.h"
#include "timer_handler.h"

int main() {
    // Read sensor revisions from EEPROM at startup
    uint8_t temp_revision = get_revision(EEPROM_TEMP_REVISION);
    uint8_t press_revision = get_revision(EEPROM_PRESS_REVISION);
    uint8_t mag_revision = get_revision(EEPROM_MAG_REVISION);

    printf("=== Sensor Monitoring System ===\n");
    printf("Using Temperature Revision: %s\n", (temp_revision == TEMP_REV_A) ? "TEMP_REV_A" : "TEMP_REV_B");
    printf("Using Pressure Revision: %s\n", (press_revision == PRESS_REV_A) ? "PRESS_REV_A" : "PRESS_REV_B");
    printf("Using Magnetometer Revision: %s\n", (mag_revision == MAG_REV_A) ? "MAG_REV_A" : "MAG_REV_B");

    // Initialize ADC for all sensors
    adc_init(SENSOR_TEMP);
    adc_init(SENSOR_PRESS);
    adc_init(SENSOR_MAG);

    volatile int timer_triggered = 0;
    setup_timer(&timer_triggered);

    // Initialize LED status for all sensors
    LedStatus leds_temp = { LED_OFF, LED_OFF, LED_OFF };
    LedStatus leds_pressure = { LED_OFF, LED_OFF, LED_OFF };
    LedStatus leds_heading = { LED_OFF, LED_OFF, LED_OFF };    

    int counter = 0;
    while (counter < COUNTER_LIMIT) {
        while (!timer_triggered) { Sleep(1); }  // Wait until the timer triggers
        timer_triggered = 0;  // Reset flag
        counter++;

        // Read ADC values from all sensors
        int16_t adc_temp = read_adc(SENSOR_TEMP);
        int16_t adc_pressure = read_adc(SENSOR_PRESS);
        int16_t adc_heading = read_adc(SENSOR_MAG);

        // Convert ADC values to real-world values
        float temp = (float)adc_temp;
        float pressure = (float)adc_pressure;
        float heading = (float)adc_heading;

        // Update LED states
        update_leds(temp, SENSOR_TEMP, &leds_temp);
        update_leds(pressure, SENSOR_PRESS, &leds_pressure);
        update_leds(heading, SENSOR_MAG, &leds_heading);

        // Print sensor data
        printf("Temperature: %.1f°C | LEDs -> G: %s | Y: %s | R: %s\n",
            temp,
            leds_temp.green == LED_ON ? "ON" : "OFF",
            leds_temp.yellow == LED_ON ? "ON" : "OFF",
            leds_temp.red == LED_ON ? "ON" : "OFF");

        printf("Pressure: %.2f hPa | LEDs -> G: %s | Y: %s | R: %s\n",
            pressure,
            leds_pressure.green == LED_ON ? "ON" : "OFF",
            leds_pressure.yellow == LED_ON ? "ON" : "OFF",
            leds_pressure.red == LED_ON ? "ON" : "OFF");

        printf("Heading: %.1f° | LEDs -> G: %s | Y: %s | R: %s\n",
            heading,
            leds_heading.green == LED_ON ? "ON" : "OFF",
            leds_heading.yellow == LED_ON ? "ON" : "OFF",
            leds_heading.red == LED_ON ? "ON" : "OFF");
    }
    cleanup_timer();

    printf("\n=== Sensor Monitoring Complete ===\n");
    return 0;
}
