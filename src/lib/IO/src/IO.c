#include "../IO.h"
#include "../message.h"
#include "../serial.h"

Event io_get_event() {
    if (serial_avail())
        return MESSAGE;
    return NOOP;
}
