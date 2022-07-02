#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>


#include "server/inis.h"

int main () {
    srvr_load();
    return 0;
}
