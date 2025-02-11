#ifndef ADC_HANDLER_H
#define ADC_HANDLER_H

#include <stdint.h>

int16_t read_adc(uint8_t revision);
float convert_adc_to_temp(int16_t adc_value, uint8_t revision);

#endif // ADC_HANDLER_H
