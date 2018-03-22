#include "common.h"
#include "client.h"


int release_connection(struct conn_data *conn) {
    if (conn == NULL) return 0;

    freeaddrinfo(conn->addr);
    return close(conn->sfd);
}
