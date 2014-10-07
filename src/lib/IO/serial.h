#ifndef SERIAL_H
#define SERIAL_H

#include "message.h"

/*
 * Обработчик прерывания при поступлении новых данных.
 */
void serial_handler();
/*
 * Возвращает 1, если доступны новые сообщения, в противном случае 0.
 */
int serial_avail();
/*
 * Возвращает принятое сообщение или 0, если сообщений нет.
 */
Message * serial_get_message();

#endif // SERIAL_H

