#ifndef SYSTEM_CONFIG_H
#define SYSTEM_CONFIG_H

#define SYSTEM_VERSION "1.0.0"

// Temperature Sensor Revisions
#define TEMP_REV_A  0  // Integer-based temperature readings
#define TEMP_REV_B  1  // Scaled temperature readings

// Pressure Sensor Revisions (Example: Different Measurement Units)
#define PRESS_REV_A  0  // Pressure in hPa
#define PRESS_REV_B  1  // Pressure in PSI

// Magnetometer Revisions (Example: Different Calibration Methods)
#define MAG_REV_A  0  // Raw Magnetometer Data
#define MAG_REV_B  1  // Calibrated Magnetometer Data

#define MAX_TEMP 50.0f
#define MAX_PRESS 1100.0f
#define MAX_HEAD 360.0f

#define MIN_TEMP -10.0f 
#define MIN_PRESS 900.0f
#define MIN_HEAD 0.0f


#define STEP_TEMP 0.1f
#define STEP_PRESS 0.25f
#define STEP_HEAD 5.0f

#define ADC_TEMP_FACTOR 10.0f 
#define ADC_PRESS_FACTOR 0.0145038f
#define ADC_HEAD_FACTOR 1.05f


#define TEMP_WARN_THRESHOLD 30.0f
#define TEMP_CRIT_THRESHOLD 40.0f
#define PRESS_WARN_THRESHOLD 960.0f
#define PRESS_CRIT_THRESHOLD 980.0f
#define HEAD_WARN_THRESHOLD 10.0f
#define HEAD_CRIT_THRESHOLD 30.0f


#define SAMPLING_INTERVAL_US 100 // 100 us sampling period
#define COUNTER_LIMIT 20 // max allowed iterations

#endif // SYSTEM_CONFIG_H
