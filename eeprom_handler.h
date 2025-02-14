#ifndef EEPROM_HANDLER_H
#define EEPROM_HANDLER_H

#include <stdint.h>

// Define EEPROM storage keys
typedef enum {
    EEPROM_TEMP_REVISION,
    EEPROM_PRESS_REVISION,
    EEPROM_MAG_REVISION
} EEPROMKey;

uint8_t get_revision(EEPROMKey key);
void set_revision(EEPROMKey key, uint8_t new_revision);
void write_eeprom(EEPROMKey key, uint16_t value);
uint16_t read_eeprom(EEPROMKey key);

#endif // EEPROM_HANDLER_H
