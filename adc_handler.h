#ifndef ADC_HANDLER_H
#define ADC_HANDLER_H

#include <stdint.h>

// types of sensor
typedef enum {
    SENSOR_TEMP,
    SENSOR_PRESS,
    SENSOR_MAG
} SensorType;

void adc_init(SensorType sensor);
int16_t read_adc(SensorType sensor);

#endif // ADC_HANDLER_H
