#ifndef INIS_H
#include <pthread.h>
#include <sys/socket.h>
#include <netinet/in.h>
#define INIS_H

extern pthread_t _COMMAND_THREAD_ID;


extern void srvr_load(int argc, char *argv[]);
extern void srvr_listen(int server_sock, int argc, char *argv[]);

//Thread Functions
extern void* srvr_cmd(void* _args);
extern void* srvr_clt_handling(void* clt);

#endif
#define PORT 9114
