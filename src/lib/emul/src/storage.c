#include "../storage.h"
#include <stdio.h>
#include <stdlib.h>

FILE *eeprom;

char eeprom_init() {
    eeprom = fopen("eeprom.dat", "r+b");
    if (eeprom == NULL) {
        eeprom = fopen("eeprom.dat", "w+b");
    }
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

FILE *storage;

char storage_init(){
    storage = fopen("storage.img", "r+b");
    if(storage == NULL){
        storage = fopen("storage.img", "w+b");
    }
    if(storage == NULL){
        perror("Unable to open storage file");
        exit(EXIT_FAILURE);
    }

    return 0;
}

uint32_t storage_read(uint8_t *buff, uint32_t sector, uint32_t count){
    if (fseek(storage, 512 * sector, SEEK_SET)) return 0;
    return fread(buff, count, 1, storage);
}

uint32_t storage_write(const uint8_t *buff, uint32_t sector, uint32_t count){
    if (fseek(storage, 512 * sector, SEEK_SET)) return 0;
    return fwrite(buff, count, 1, storage);

    //Необходимость следующей строки под вопросом
    fflush(storage);
}