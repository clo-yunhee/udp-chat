#include "common.h"
#include "client.h"

char *prepare_packet(const char *msg) {
    uid_t uid;
    struct passwd *pw;

    uid = geteuid();

    errno = 0;
    pw = getpwuid(uid);
    if (pw == NULL) {
        return NULL;
    }

    char *name = pw->pw_name;

    /* $PACK = $NAME: $MSG */
    /* len = sum + 2 */
    size_t len = strlen(name) + strlen(msg) + 3; // +1 for NUL
    if (len > MAX_PACKET_SIZE) {
        return NULL;
    }

    char *packet = malloc(len);

    snprintf(packet, len, "%s: %s", name, msg); 

    return packet;
}

