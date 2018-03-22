#include "common.h"
#include "client.h"

void *send_callback(void *);

int start_send_thread(struct conn_data *conn) {
    pthread_create(&thread_send, NULL, send_callback, conn);
}

