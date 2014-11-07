#include "../network.h"
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

static int sock = 0;

char network_init() {
    int serv_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (serv_sock < 0)
        error("Unable to open socket");

    struct sockaddr_in serv_addr, cli_addr;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(COMM_PORT);
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    // Биндимся
    if (bind(serv_sock, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
        error("ERROR on binding");

    // Ожидаем подключения
    listen(serv_sock, 1);
    // Акцептим подключение
    int clilen = sizeof(cli_addr);
    sock = accept(serv_sock, (struct sockaddr *) &cli_addr, &clilen);
    if (sock < 0)
        error("ERROR on accept");

    struct timeval tv;
    tv.tv_sec = 0;  /* 30 Secs Timeout */
    tv.tv_usec = 500;  // Not init'ing this can cause strange errors
    setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, (char *)&tv, sizeof(struct timeval));

    return 0;
}

int comm_recv(uint8_t *buffer, int length) {
    return sock ? recv(sock, buffer, length, 0) : 0;
}

int comm_send(const uint8_t *buffer, int length) {
    return sock ? send(sock, buffer, length, 0) : 0;
}
