
#ifndef INIS_H
#define INIS_H
#include "../client/clt_defs.h"

typedef struct SOCK_THREAD_T
{
    int SOCK;
    uint32_t events;
    pthread_t *THREAD;
} ST_T;

extern int server_sock, SERVER_STATE, CLIENTS_STATE;
extern pthread_t SERVER_THREAD;
extern pthread_t SRVR_LSTN_THREAD;
extern pthread_t CLIENT_THREAD[2];
extern pthread_mutex_t SERVER_MUTEX;
extern pthread_mutex_t CLIENT_MUTEX[2];

extern ST_T THREADS_INFO[2];

extern struct sockaddr_in server_addr;

extern char *r;
extern clt_inf *INCOMING_CLT;
extern unsigned int client_size;

extern void srvr_load(int argc, char *argv[]);

// Thread Functions
extern void *srvr_listen(void *_args);

#endif
