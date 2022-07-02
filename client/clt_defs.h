#ifndef CLT_DEFS_H
#include <pthread.h>
#include "server/inis.h"
#define CLT_DEFS_H

typedef struct client_info clt_inf;
typedef struct client_links* clt_lnk;
typedef struct client clt;


struct client_info{
    pthread_t thread_id;
    int sock;
    int ID;
    char GUID[37];
    struct sockaddr_in addr;
};
struct client_links
{
    clt_lnk prev;
    int INDEX;
    clt_inf Client;
    clt_lnk next;
};

clt_lnk CLT_LIST = NULL;
clt_lnk NULL_CLIENT = NULL;
clt CLIENT;
clt_lnk CURRENT_CLIENT = NULL;
int CURRENT_INDEX = -1;
int INIS = 0;

//Initialises the 
//Clients linked List
//Return :
// 0 -> Success
// -1-> Failure
extern int clt_inis();/**/

//Add a Client
//Returns:
//INTEGER -> index
//-1 -> Error Somewere
extern int clt_add(int sock, char* UUID, int ID, clt_lnk New_Client);

//Check for past Connections
// Returns:
// 0 -> Client Exists
// 1 -> Client Doesn't Exist
extern int clt_check(int UUID);

//Deletion Functions
// Returns :
// 0 -> Success
// 1 -> User non-existant (Fail)
extern int clt_delete(int index);
extern int clt_delete(int sock);
extern int clt_delete(char* UUID);
extern int clt_delete(int ID);

//Case of Reconnection
//Returns:
// 0 -> Success
// 1 -> Client non-existant
extern int clt_update(char* UUID, int sock);
extern int clt_update(int index, int sock);


#endif