
#ifndef INIS_H
#define INIS_H
#include "../client/clt_defs.h"

typedef struct SOCK_THREAD_T
{
    int SOCK;
    uint32_t events;
} ST_T;

extern int server_sock;
extern _Atomic int SERVER_STATE;
extern pthread_t SERVER_THREAD;
extern pthread_t SRVR_LSTN_THREAD;
extern pthread_t CLIENT_THREAD[2];

#define _Used 1
#define _NotUsed 0
#define CLIENT_THREADS 2
extern _Atomic int CLIENT_STATES[CLIENT_THREADS];

extern ST_T THREADS_INFO[2];

extern struct sockaddr_in server_addr;

extern char *r;
extern unsigned int client_size;


extern void srvr_load(int argc, char *argv[]);

// Thread Functions
extern void *srvr_listen(void *_args);

extern void _Update_Client_S(int _Client_Thread, int _Status);
extern void _Update_Server_S(int _Status);
#endif
