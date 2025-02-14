#include "adc_handler.h"
#include "system_config.h"
#include "eeprom_handler.h"
#include <stdio.h>
#include <math.h>


static uint8_t revision = 0; // revisions from EEPROM
static SensorType active_sensor; // active sensor type
static float next_temp = MIN_TEMP;
static float next_press = MIN_PRESS;
static float next_head = MIN_HEAD;
static int step_counter;

// Initialze ADC by selecting sensor type
void adc_init(SensorType sensor) {
    if (sensor == SENSOR_TEMP) {
        revision = get_revision(EEPROM_TEMP_REVISION);  // Load Temperature Revision
    }
    else if (sensor == SENSOR_PRESS) {
        revision = get_revision(EEPROM_PRESS_REVISION);  // Load Pressure Revision
    }
    else if (sensor == SENSOR_MAG) {
        revision = get_revision(EEPROM_MAG_REVISION);  // Load Magnetometer Revision
    }
}

int16_t read_adc(SensorType sensor) {
    switch (sensor) {
    case SENSOR_TEMP:
        if (get_revision(EEPROM_TEMP_REVISION) == TEMP_REV_A) {
            float rounded_temp = roundf(next_temp);
            next_temp += 1.0f;
            if (next_temp > MAX_TEMP) next_temp = MAX_TEMP;
            return (int16_t)rounded_temp;
        }
        else { // TEMP_REV_B
            next_temp = MIN_TEMP + (step_counter * STEP_TEMP);
            step_counter++;
            if (next_temp > MAX_TEMP - STEP_TEMP) next_temp = MAX_TEMP;
            return (int16_t)roundf(next_temp * ADC_TEMP_FACTOR);
        }

    case SENSOR_PRESS:
        if (get_revision(EEPROM_PRESS_REVISION) == PRESS_REV_A) {
            next_press += STEP_PRESS;
            if (next_press > MAX_PRESS) next_press = MAX_PRESS;
            return (int16_t)next_press;
        }
        else { // PRESS_REV_B (PSI Mode)
            next_press += STEP_PRESS;
            if (next_press > MAX_PRESS) next_press = MAX_PRESS;
            return (int16_t)(next_press * ADC_PRESS_FACTOR); // Convert hPa to PSI
        }

    case SENSOR_MAG:
        if (get_revision(EEPROM_MAG_REVISION) == MAG_REV_A) {
            next_head += STEP_HEAD;
            if (next_head > MAX_HEAD) next_head = MIN_HEAD;
            return (int16_t)next_head;
        }
        else { // MAG_REV_B (Calibrated Mode)
            next_head += STEP_HEAD;
            if (next_head > MAX_HEAD) next_head = MIN_HEAD;
            return (int16_t)(next_head * ADC_HEAD_FACTOR); // Apply calibration factor
        }
    }
    return 0;
}
