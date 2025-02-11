#ifndef SYSTEM_CONFIG_H
#define SYSTEM_CONFIG_H

#define SYSTEM_VERSION "1.0.0"

#define MAX_TEMP 120.0f  // Maximum temperature
#define MIN_TEMP -5.0f   // Minimum temperature
#define STEP_B 0.2f      // Rev-B increments by 0.2°C
#define ADC_SCALE_FACTOR 10.0f  // Scaling factor for Rev-B ADC conversion
#define SAMPLING_INTERVAL_US 100 // 100 us sampling period
#define COUNTER_LIMIT 5000 // max allowed iterations

#endif // SYSTEM_CONFIG_H
