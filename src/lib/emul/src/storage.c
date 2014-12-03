#include "../storage.h"
#include <stdio.h>
#include <stdlib.h>

FILE *eeprom;

char eeprom_init() {
    eeprom = fopen("eeprom.dat", "w+");
    if (eeprom == NULL) {
        perror("Unable to open eeprom file");
        exit(EXIT_FAILURE);
    }

    return 0;
}

char eeprom_read_byte(uint32_t addr) {
    fseek(eeprom, addr, SEEK_SET);
    return fgetc(eeprom);
}

void eeprom_write_byte(uint32_t addr, char byte) {
    fseek(eeprom, addr, SEEK_SET);
    fputc(byte, eeprom);
}
