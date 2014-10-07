#include "../IO.h"
#include "../message.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// Temporary
static DeviceInfo d;
DeviceInfo * get_device_info() {
    d.ident = 3321;
    return &d;
}

#define COMM_BUF_LEN 10000
static Message *msg = 0;

// Simple stack
void msg_push(Message *m) {
    if (!msg) {
        msg = malloc(sizeof(Message));
        if (msg != NULL)
            memcpy(msg, m, sizeof(Message));
        msg->next = 0;
        return;
    }
    Message *head = msg;
    while (head->next)
        head = head->next;
    head->next = malloc(sizeof(Message));
    if (head->next != NULL)
        memcpy(head->next, m, sizeof(Message));
    head->next->next = 0;
}

Message * msg_pop() {
    if (!msg)
        return 0;
    Message *tmp;
    if (!msg->next) {
        tmp = msg;
        msg = 0;
        return tmp;
    }
    Message *head = msg;
    while (head->next->next)
        head = head->next;
    tmp = head->next;
    head->next = 0;
    return tmp;
}

int send_init() {
    uint8_t msg = mDeviceInit;
    return comm_send(&msg, 1);
}

int send_info() {
    char buf[1+sizeof(DeviceInfo)];
    buf[0] = mDeviceInfo;
    memcpy(buf+1, get_device_info(), sizeof(DeviceInfo));
    return comm_send(buf, sizeof(buf));
}

int serial_avail() {
    return msg ? 1 : 0;
}

Message * serial_get_message() {
    return msg_pop();
}

void serial_handler() {
    Message m;
    if(comm_recv(&m.type, sizeof(uint8_t)) != sizeof(uint8_t))
        return;

    switch (m.type) {
        case mDeviceInit:
            printf("DeviceInit request\n");
            send_init();
            break;

        case mDeviceInfo:
            printf("DeviceInfo request\n");
            send_info();
            break;

        default:
            printf("New message:\n\ttype: %d\n", m.type);
            if(comm_recv(&m.size, sizeof(uint32_t)) == sizeof(uint32_t)) {
                printf("\tsize: %d\n", m.size);
                // Allocate new region
                m.data = malloc(m.size);
                if (m.data != NULL) {
                    // Receive data
                    if (comm_recv(m.data, m.size) == m.size) {
                        printf("\tdata: SUCCESS\n");
                        msg_push(&m);
                    }
                    else
                        printf("\tdata: FAIL\n");
                }
            }
    }
}

