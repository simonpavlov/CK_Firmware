#include "../storage.h"
#include <stdio.h>
#include <stdlib.h>

FILE *storage;

char storage_init() {
    storage = fopen("storage.dat", "w+");
    if (storage == NULL) {
        perror("Unable to open storage file");
        exit(EXIT_FAILURE);
    }

    return 0;
}

char storage_read_byte(uint32_t addr) {
    fseek(storage, addr, SEEK_SET);
    return fgetc(storage);
}

void storage_write_byte(uint32_t addr, char byte) {
    fseek(storage, addr, SEEK_SET);
    fputc(byte, storage);
}
