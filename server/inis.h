#ifndef INIS_H
#include "../_Imports.h"
#define INIS_H

extern pthread_t _COMMAND_THREAD_ID;


extern void srvr_load(int argc, char *argv[]);
extern void srvr_listen(int server_sock, int argc, char *argv[]);

//Thread Functions
extern void* srvr_cmd(void* _args);

#endif
#define PORT 9114
