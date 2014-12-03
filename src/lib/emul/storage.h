#ifndef EMUL_STORAGE
#define EMUL_STORAGE

#include <stdint.h>

/*
 * Инициализация хранилища.
 */
char eeprom_init();

/*
 * Чтение байта по адресу.
 */
char eeprom_read_byte(uint32_t);

/*
 * Запись байта по адресу.
 */
void eeprom_write_byte(uint32_t, char);

#endif
