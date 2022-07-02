#ifndef INIS_H
#include <pthread.h>
#include <sys/socket.h>
#include <netinet/in.h>
#define INIS_H

pthread_t _COMMAND_THREAD_ID;


extern void srvr_load();
extern void* srvr_cmd(void* _args);
extern void srvr_listen(int server_sock);

extern void* srvr_clt_handling(void* clt);

#endif
#define PORT 9114