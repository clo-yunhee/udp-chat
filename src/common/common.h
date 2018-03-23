#ifndef COMMON_COMMON_H
#define COMMON_COMMON_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <pwd.h>
#include <pthread.h>


/*
 * The maximum number of bytes that make a packet.
 * NB: the maximum size that is guaranteed by the IPv4 standard is 548 bytes.
 *     a 512 byte buffer more likely to align in memory, hence this choice.
 */
#define MAX_PACKET_SIZE  512

/*
 * The maximum number of errors that can occur during send / receive before it stops the loop.
 */
#define MAX_ERRORS 10



#endif // COMMON_COMMON_H
