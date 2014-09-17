#ifndef EMUL_NETWORK
#define EMUL_NETWORK

// Порт на котором ожидать подключение
#define COMM_PORT 7777

/*
 * Инициализация коммуникационного стека.
 * Ожидание подключения клиента.
 */
void network_init();

/*
 * Чтение данных от клиента.
 */
int comm_recv(char *buffer, int length);

/*
 * Отправка данных клиенту.
 */
int comm_send(char *buffer, int length);

#endif
