#ifndef CLIENT_CLIENT_H
#define CLIENT_CLIENT_H

/*
 * Open an Internet UDP socket.
 * Returns -1 and sets errno on error.
 */
int open_socket(void);

/*
 * Searches for possible addresses for the server.
 * Returns a nonzero error value on error.
 */
int get_server_addr(const char *port, struct addrinfo **addr);

/*
 * Prepares a packet string with the message and the user's name.
 * Returns NULL on error.
 */
char *prepare_packet(const char *msg);

/*
 * Structure to hold the requirements to send/receive.
 */
struct conn_data {
    int sfd;
    struct addrinfo *addr;
};

/*
 * Sends the packet to all the addresses.
 * Returns -1 and sets errno on error.
 */
int send_to_server(const char *packet, struct conn_data *conn);

/*
 * Release resources from the connection.
 * Returns -1 on error.
 */
int release_connection(struct conn_data *conn);

/*
 * Threads for sending and receiving.
 */
extern pthread_t thread_send, thread_recv;

/*
 * Create the send / receive thread.
 * Returns a nonzero value on error.
 */
int start_send_thread(struct conn_data *conn);
int start_recv_thread(struct conn_data *conn);


#endif // CLIENT_CLIENT_H
