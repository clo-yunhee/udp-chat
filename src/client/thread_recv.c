#include "common.h"
#include "client.h"

void *recv_callback(void *);

pthread_t thread_recv;

int start_recv_thread(struct conn_data *conn) {
    errno = 0;
    fprintf(stderr, "Recv not implemented yet\n");

    (void) conn;
    return 0;
}
