#include "common.h"
#include "client.h"


static struct conn_data *s_conn = NULL;
void exit_callback(void);


int main(int argc, char *argv[]) {
    const char *port;
    struct conn_data conn;

    int s;

    // change the port on the command line
    port = (argc > 1) ? argv[1] : "30303";

    // open the broadcast socket
    conn.sfd = open_socket();
    if (conn.sfd == -1) {
        perror("Could not open socket");
        exit(EXIT_FAILURE);
    }

    // create the server addresses
    if ((s = get_server_addr(port, &conn.addr)) != 0) {
        fprintf(stderr, "Could not create server address: %s\n", gai_strerror(s));
        exit(EXIT_FAILURE);
    }
    // check that we found at least one
    if (&conn.addr == NULL) {
        fprintf(stderr, "Could not find any server\n");
        exit(EXIT_FAILURE);
    }

    // register exit callback for addresses
    s_conn = &conn;
    atexit(exit_callback);
    
    // start the threads
    if ((s = start_send_thread(&conn)) != 0) {
        fprintf(stderr, "Could not start the send thread: %s\n", strerror(s));
        exit(EXIT_FAILURE);
    }
    if ((s = start_recv_thread(&conn)) != 0) {
        fprintf(stderr, "Could not start the receive thread: %s\n", strerror(s));
        exit(EXIT_FAILURE);
    }
  
    // the send thread never returns, it never ends, except when it exits.
    // the recv thread can receive a kill message from the server,
    // so we do have to join on it.
    
    // FIXME: temporary, until recv is implemented
    pthread_join(thread_send, NULL);

    return EXIT_SUCCESS;
}

void exit_callback(void) {
    //pthread_cancel(thread_send);
    //pthread_cancel(thread_recv);

    if (release_connection(s_conn) == -1) {
        perror("Could not release connection");
        exit(EXIT_FAILURE);
    }
}

