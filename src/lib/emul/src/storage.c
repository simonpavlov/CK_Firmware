#include "../storage.h"
#include <stdio.h>
#include <string.h>
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

void eeprom_quit(){
	fclose(eeprom);
}

FILE *storage;

#define STORAGE_SECOTR_SIZE		512
#define STORAGE_SECOTR_COUNT	20480
#define STORAGE_BLOCK_SIZE		512

char storage_init(){
	storage = fopen("storage.img", "r+b");
	if(storage == NULL){
		storage = fopen("storage.img", "w+b");
		if(storage == NULL){
			perror("Unable to open & create storage file");
			exit(EXIT_FAILURE);
		}

		uint8_t *buffer;
		buffer = (uint8_t *) malloc(STORAGE_SECOTR_SIZE);
		memset(buffer, 0, STORAGE_SECOTR_SIZE);

		int i;
		for(i = 0; i < STORAGE_SECOTR_COUNT; i++){
			fwrite(buffer, STORAGE_SECOTR_SIZE, 1, storage); // Записываем один сектор
		}

		free(buffer);
	}

	return 0;
}

uint32_t storage_read(uint8_t *buff, uint32_t sector, uint32_t count){
	if (fseek(storage, STORAGE_BLOCK_SIZE * sector, SEEK_SET)) return 0;
	return fread(buff, STORAGE_BLOCK_SIZE, count, storage);
}

uint32_t storage_write(const uint8_t *buff, uint32_t sector, uint32_t count){
	if (fseek(storage, STORAGE_BLOCK_SIZE * sector, SEEK_SET)) return 0;
	return fwrite(buff, STORAGE_BLOCK_SIZE, count, storage);

	//Необходимость следующей строки под вопросом
	fflush(storage);
}

uint32_t get_storage_sector_size(){
	return STORAGE_SECOTR_SIZE;
}

uint32_t get_storage_sector_count(){
	return STORAGE_SECOTR_COUNT;
}

uint32_t get_storage_block_size(){
	return STORAGE_BLOCK_SIZE;
}

void storage_quit(){
	fclose(storage);
}
