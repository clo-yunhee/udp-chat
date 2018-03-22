#ifndef COMMON_COMMON_H
#define COMMON_COMMON_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <pwd.h>
#include <pthread.h>


// note: the standard maximum packet size for IPv4 is 548 bytes
// in practice, it is higher, but let's be safe.
// assume that messages will be short enough.
#define MAX_PACKET_SIZE  512


#endif // COMMON_COMMON_H
