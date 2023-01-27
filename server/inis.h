#ifndef INIS_H
#define INIS_H

typedef struct SOCK_THREAD_T ST_T;
struct SOCK_THREAD_T
{
    int SOCK;
    pthread_t *THREAD;
};

extern int server_sock, SERVER_STATE, CLIENTS_STATE;
extern pthread_t SERVER_THREAD;
extern pthread_t CLIENT_THREAD[2];
extern pthread_mutex_t SERVER_MUTEX;
extern pthread_mutex_t CLIENT_MUTEX[2];

extern void srvr_load(int argc, char *argv[]);
extern void srvr_listen(int argc, char *argv[]);

// Thread Functions
extern void *srvr_cmd(void *_args);

#endif
