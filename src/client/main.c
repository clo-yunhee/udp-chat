#include "common.h"
#include "client.h"


static struct conn_data *s_conn = NULL;
void exit_callback(void);


int main(int argc, char *argv[]) {
    const char *port;
    struct conn_data conn;

    // change the port on the command line
    port = (argc > 1) ? argv[1] : "30303";

    // open the broadcast socket
    conn.sfd = open_socket();
    if (conn.sfd == -1) {
        perror("Could not open socket");
        exit(EXIT_FAILURE);
    }

    // create the server addresses
    int gai = get_server_addr(port, &conn.addr);
    if (gai != 0) {
        fprintf(stderr, "Could not create server address: %s\n", gai_strerror(gai));
        exit(EXIT_FAILURE);
    }
    // register exit callback for addresses
    s_conn = &conn;
    atexit(exit_callback);
    
    // start the threads
    if (start_send_thread(conn) == -1) {
        perror("Could not start the send thread");
        exit(EXIT_FAILURE);
    }
    if (start_recv_thread(conn) == -1) {
        perror("Could not start the receive thread");
        exit(EXIT_FAILURE);
    }

    // exit
    return EXIT_SUCCESS;
}

void exit_callback(void) {
    if (release_connection(&conn) == -1) {
        perror("Could not release connection");
        exit(EXIT_FAILURE);
    }
}

