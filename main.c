#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>


#include "server/inis.h"

int main (int argc, char *argv[]) {
    srvr_load(argc, argv);
    return 0;
}
