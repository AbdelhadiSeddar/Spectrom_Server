#include "clt_defs.h"

pthread_mutex_t CURRENT_INFO_MUTEX;

clt_lnk CLT_LIST        = NULL;
clt_lnk NULL_CLIENT     = NULL;
clt_lnk CURRENT_CLIENT  = NULL;
int     CURRENT_INDEX   = -1;
int     INIS            = 0;

int clt_inis(){
    CURRENT_INDEX = 0;
    INIS = 1;
    NULL_CLIENT = malloc(sizeof(*NULL_CLIENT));
    CLT_LIST = NULL_CLIENT;
    strcpy((NULL_CLIENT -> Client.GUID), "00000000-0000-0000-0000-000000000000");
    int sock = 3;

    NULL_CLIENT -> next = NULL;
    NULL_CLIENT -> prev = NULL;
    CURRENT_CLIENT = NULL_CLIENT;


    return 0;
}

int clt_add(clt_inf New_Inf, clt_lnk* New_Client){

    clt_lnk client = malloc(sizeof(*client));

    (client -> Client.file) = malloc(sizeof(*(client -> Client.file)));
    (client -> Client.thread_id) = malloc(sizeof((client -> Client.thread_id)));
    (client -> Client.addr) = malloc(sizeof((client -> Client.addr)));
    
    pthread_mutex_lock(&CURRENT_INFO_MUTEX);

    client -> prev = CURRENT_CLIENT;
    client -> next = NULL;
    client -> INDEX = CURRENT_INDEX;
    
    CURRENT_INDEX++;
    CURRENT_CLIENT = client;

    pthread_mutex_unlock(&CURRENT_INFO_MUTEX);

    return 0;
}
