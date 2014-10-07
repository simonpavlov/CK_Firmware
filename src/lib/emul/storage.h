#ifndef EMUL_STORAGE
#define EMUL_STORAGE

#include <stdint.h>

/*
 * Инициализация хранилища.
 */
void storage_init();

/*
 * Чтение байта по адресу.
 */
char storage_read_byte(uint32_t);

/*
 * Запись байта по адресу.
 */
void storage_write_byte(uint32_t, char);

#endif
