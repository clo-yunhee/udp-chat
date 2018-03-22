#include "common.h"
#include "client.h"

int open_socket(void) {
    return socket(AF_INET, SOCK_DGRAM, 0);
}

int get_server_addr(const char *port, struct addrinfo **addr) {
    struct addrinfo hints;
    memset(&hints, 0, sizeof (struct addrinfo));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_DGRAM;
    hints.ai_flags = 0;
    hints.ai_protocol = 0;

    return getaddrinfo(NULL, port, &hints, addr);
}
