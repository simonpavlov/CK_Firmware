#ifndef EMUL_NETWORK

#include <stdint.h>

#define EMUL_NETWORK

// Порт на котором ожидать подключение
#define COMM_PORT 7777

/*
 * Инициализация коммуникационного стека.
 * Ожидание подключения клиента.
 */
char network_init();

/*
 * Чтение данных от клиента.
 */
int comm_recv(uint8_t *buffer, int length);

/*
 * Отправка данных клиенту.
 */
int comm_send(uint8_t *buffer, int length);

#endif
