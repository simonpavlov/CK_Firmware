#ifndef EMUL_STORAGE
#define EMUL_STORAGE

#include <stdint.h>

/*
 * Инициализация хранилища eeprom.
 */
char eeprom_init();

/*
 * Чтение байта по адресу eeprom.
 */
char eeprom_read_byte(uint32_t);

/*
 * Запись байта по адресу eeprom.
 */
void eeprom_write_byte(uint32_t, char);

/*
 * Инициализация хранилища storage.
 */
char storage_init();

/*
	Read Sector(s)

	buff	Data buffer to store read data
	sector	Sector address in LBA
	count	Number of sectors to read
 */
uint32_t storage_read(uint8_t *buff, uint32_t sector, uint32_t count);

/*
	Write Sector(s)

	buff	Data buffer to store read data
	sector	Sector address in LBA
	count	Number of sectors to read
 */
uint32_t storage_write(const uint8_t *buff, uint32_t sector, uint32_t count);

#endif
