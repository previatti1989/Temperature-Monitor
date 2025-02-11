#include "eeprom_handler.h"

// Simulated EEPROM Storage
//static uint8_t eeprom_hardware_revision = REV_A;  // Change to REV_B for testing
static char eeprom_serial_number[] = SERIAL;

// Get stored serial number
char* get_serial_number() {
    if (eeprom_serial_number[0] == '\0') {
        return "UNKNOWN";  // Prevent NULL return
    }
    return eeprom_serial_number;
}
