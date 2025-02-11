#include <stdio.h>
#include <math.h>
#ifdef _MSC_VER
#include <windows.h> // For `Sleep()` (MSVC)
#else
#include <unistd.h>  // For `usleep()` (GCC)
#endif
//#include <time.h>    // For timing
#include "adc_handler.h"
#include "eeprom_handler.h"
#include "led_controller.h"
#include "system_config.h"

int main() {
    LedStatus leds = {LED_OFF, LED_OFF, LED_OFF};
    printf("Temperature Monitoring System - Dual Sensor Mode\n");
    char* serial = get_serial_number();
    if (serial == NULL) {
        serial = "UNKNOWN";
    }
    printf("Serial Number: %s\n", serial);
    //printf("DEBUG: Entering loop\n");
    int counter = 0;
    while (counter < COUNTER_LIMIT) {
        counter++;
        //printf("Entering loop: Counter = %d\n", counter);
        // Read ADC values from both sensors
        int16_t adc_value_A = read_adc(REV_A);
        int16_t adc_value_B = read_adc(REV_B);

        // Convert to temp
        float temp_A = convert_adc_to_temp(adc_value_A, REV_A);
        float temp_B = convert_adc_to_temp(adc_value_B, REV_B);

        // Decide which sensor to display
        float displayed_temp;
        uint8_t selected_sensor;

        if (fabs(temp_B - round(temp_B)) > 0.01f) {  // If temp_B has a decimal part
            displayed_temp = temp_B;
            selected_sensor = REV_B;
        }
        else {
            displayed_temp = temp_A;
            selected_sensor = REV_A;
        }

        if (selected_sensor != REV_A && selected_sensor != REV_B) {
            printf("ERROR: Invalid selected_sensor value: %d\n", selected_sensor);
            selected_sensor = REV_A;  // Default to REV_A
        }

        // Update LED states based on selected sensor temp
        update_leds(displayed_temp, &leds);

        //printf("DEBUG: Checking selected_sensor: %d\n", selected_sensor);
        //printf("DEBUG: Checking displayed_temp: %.1f\n", displayed_temp);
        //printf("DEBUG: Checking LED states -> G: %d, Y: %d, R: %d\n", leds.green, leds.yellow, leds.red);
        //printf("DEBUG: Before printing sensor data...\n");

        // Force strings to be stored in static memory
        static const char* sensor_str;
        static const char* led_green_str;
        static const char* led_yellow_str;
        static const char* led_red_str;

        // Assign valid values
        sensor_str = (selected_sensor == REV_A) ? "Rev-A" : "Rev-B";
        led_green_str = (leds.green == LED_ON) ? "ON" : "OFF";
        led_yellow_str = (leds.yellow == LED_ON) ? "ON" : "OFF";
        led_red_str = (leds.red == LED_ON) ? "ON" : "OFF";

        // Validate all pointers before using them
        if (sensor_str == NULL || led_green_str == NULL || led_yellow_str == NULL || led_red_str == NULL) {
            printf("ERROR: NULL detected in string variables!\n");
        }

        // Try printing the sensor data
        int printf_result = printf("Sensor: %s | Temp: %.1f deg | LEDs -> G: %s | Y: %s | R: %s\n",
            sensor_str, displayed_temp, led_green_str, led_yellow_str, led_red_str);

        if (fabs(displayed_temp - MAX_TEMP) < 0.001f) {
            printf("Max temperature reached (%.1f°C). Stopping simulation after %d iterations.\n", MAX_TEMP, counter);
            break;
        }
        if (counter >= COUNTER_LIMIT) {
            //printf("DEBUG: Exiting loop at counter = %d\n", counter);
            break;
        }
        #ifdef _MSC_VER
            Sleep(SAMPLING_INTERVAL_US / 1000);  // Sleep for 100 milliseconds in MSVC
        #else
            usleep(SAMPLING_INTERVAL_US);  // Sleep for 100ms in GCC
        #endif
    }

    printf("Simulation complete. Stopped after %d iterations.\n", counter);
    return 0;
}
