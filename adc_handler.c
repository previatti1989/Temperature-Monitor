#include "adc_handler.h"
#include "system_config.h"
#include "eeprom_handler.h"
#include <stdio.h>
#include <math.h>

// Simulated ADC read function for both sensors
int16_t read_adc(uint8_t revision) {
    static float next_temp = MIN_TEMP;  // Start at -5°C
    static int step_counter = 0;  // Controls temperature steps

    // **Rev-A reads whole numbers first**
    if (revision == REV_A) {
        float rounded_temp = roundf(next_temp);
        return (int16_t)rounded_temp;  // Return as integer for Rev-A
    }

    // **Rev-B reads decimal steps AFTER Rev-A**
    next_temp = MIN_TEMP + (step_counter * STEP_B);  // Calculate new temp
    step_counter++;  // Move to next step

    if (next_temp > MAX_TEMP - STEP_B) next_temp = MAX_TEMP;

    return (int16_t)roundf(next_temp * ADC_SCALE_FACTOR);  // Scale for Rev-B
}

// Convert ADC value to temperature based on revision
float convert_adc_to_temp(int16_t adc_value, uint8_t revision) {
    return (revision == REV_A) ? (float)adc_value : adc_value / ADC_SCALE_FACTOR;
}
