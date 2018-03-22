#include "common.h"
#include "client.h"

int send_to_server(const char *packet, struct conn_data *conn) {
    struct addrinfo *res;

    size_t len = strlen(packet) + 1;

    // for each address returned by getaddrinfo...
    for (res = conn->addr; res != NULL; res = res->ai_next) {
        // send the packet to it
        if (sendto(conn->sfd, packet, len, 0,
                    res->ai_addr, res->ai_addrlen) == -1) {
            return -1;
        }
    }

    return 0;
}
