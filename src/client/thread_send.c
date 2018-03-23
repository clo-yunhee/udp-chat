#include "common.h"
#include "client.h"

void *send_callback(void *);

pthread_t thread_send;

int start_send_thread(struct conn_data *conn) {
    errno = 0;
    return pthread_create(&thread_send, NULL, send_callback, conn);
}

/*
 * Basic error handling, we keep an error counter.
 * If it reaches a certain point, we just exit.
 */

void *send_callback(void *arg) {
    struct conn_data *conn = arg;

    char buffer[MAX_PACKET_SIZE];

    int err = 0;
    while (err < MAX_ERRORS) {
        // print the chat prompt
        printf(">>> ");
        fflush(stdout);

        // read the input
        if (fgets(buffer, MAX_PACKET_SIZE, stdin) == NULL) {
            fprintf(stderr, "Could not read from the standard input\n");
            ++err;
            continue;
        }

        // add prefix, format the message to be sent
        char *packet = prepare_packet(buffer);
        if (packet == NULL) {
            fprintf(stderr, "Could not prepare the send packet\n");
            ++err;
            continue;
        }
        
        // try to send it
        int s = send_to_server(packet, conn);
        // free the packet, not needed after sending
        free(packet);
        if (s == -1) {
            perror("Could not send packet to the server");
            ++err;
            continue;
        }
    }
    
    // this point is reached only when there is an error.

    fprintf(stderr, "Reached maximum consecutive errors (%d), exiting...\n", MAX_ERRORS);
    
    exit(EXIT_FAILURE);
}
