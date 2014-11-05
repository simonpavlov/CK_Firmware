#ifndef EMUL_FLASH
#define EMUL_FLASH

#include <stdint.h>

/*
 * Инициализация хранилища.
 */
void flash_init();

/*
 * Чтение байта по адресу.
 */
char flash_read_byte(uint32_t);

/*
 * Запись байта по адресу.
 */
void flash_write_byte(uint32_t, char);

#endif
