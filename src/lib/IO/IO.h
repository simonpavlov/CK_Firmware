#ifndef IO_H
#define IO_H

typedef enum {
    NOOP
  , PRESSED
  , MESSAGE
} Event;

/*
 * Возвращает событие или NOOP.
 */
Event io_get_event();

#endif // _H

