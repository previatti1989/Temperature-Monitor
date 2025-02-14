#include "eeprom_handler.h"
#include "system_config.h"

// Simulated EEPROM storage
static uint8_t eeprom_storage[3] = { TEMP_REV_A, PRESS_REV_A, MAG_REV_A };

uint8_t get_revision(EEPROMKey key) {
    return eeprom_storage[key];  // Read stored revision
}

void set_revision(EEPROMKey key, uint8_t new_revision) {
    eeprom_storage[key] = new_revision;  // Update revision in EEPROM
}

// Write any value to EEPROM
void write_eeprom(EEPROMKey key, uint16_t value) {
    if (key < sizeof(eeprom_storage) / sizeof(eeprom_storage[0])) {
        eeprom_storage[key] = value;  // Store value in EEPROM
    }
}

// Read any value from EEPROM
uint16_t read_eeprom(EEPROMKey key) {
    if (key < sizeof(eeprom_storage) / sizeof(eeprom_storage[0])) {
        return eeprom_storage[key];  // Return stored value
    }
    return 0;  // Default return if key is out of range
}