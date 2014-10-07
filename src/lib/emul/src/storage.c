#include "../storage.h"
#include <stdio.h>
#include <stdlib.h>

FILE *storage;

void storage_init() {
    storage = fopen("storage.dat", "w+");
    if (storage == NULL) {
        perror("Unable to open storage file");
        exit(EXIT_FAILURE);
    }
}

char storage_read_byte(uint32_t addr) {
    fseek(storage, addr, SEEK_SET);
    return fgetc(storage);
}

void storage_write_byte(uint32_t addr, char byte) {
    fseek(storage, addr, SEEK_SET);
    fputc(byte, storage);
}
