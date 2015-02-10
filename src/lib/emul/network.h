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
uint32_t comm_recv(uint8_t *buffer, uint32_t length);

/*
 * Отправка данных клиенту.
 */
uint32_t comm_send(const uint8_t *buffer, uint32_t length);

/*
 * TODO: Функция завершения работы со стеком
 */
//void comm_quit();

#endif
