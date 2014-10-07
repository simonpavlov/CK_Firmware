#include "../app.h"
#include "../callback.h"
#include <IO/IO.h>
#include <IO/message.h>
#include <IO/serial.h>

#include <stdio.h>
#include <stdlib.h>

void
setup(void) {

}

void app_password_get(Message *m) {
    printf("Deserialize... %d\n", m->data);
    char *login = deserialize_qbytearray(m->data, 0);
    printf("\tLOGIN: %s\n", login);
//free(login);
}

void message_handler(Message *m) {
    switch (m->type) {
        case mPasswordGet:
            printf("Password get message\n");
            app_password_get(m);
            break;
        case mPasswordPut:
            break;
        case mAuthGet:
            break;
        case mAuthPut:
            break;
        default:
            printf("Unknown message\n");
    }
    message_free(m);
}

void main_loop(void) {
    serial_handler();

    switch (io_get_event()) {
        case MESSAGE:
            message_handler(serial_get_message());
        default:
            break;
    }
}

void
application(void) {
    setup();
    while (1) {
        main_loop();
    }
}
