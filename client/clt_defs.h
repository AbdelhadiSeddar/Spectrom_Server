#ifndef CLT_DEFS_H
#include <pthread.h>
#define CLT_DEFS_H
typedef struct client_links* clt_lnk;
typedef struct client clt;


struct client
{
    int index;
    char UUID[37];
    int ID;
};
struct client_links
{
    clt_lnk prev;
    pthread_t thread_id;
    struct sockaddr address;
    int sock;
    clt Client;
    clt_lnk next;
};

extern clt_lnk CLT_LIST;
extern clt_lnk NULL_CLIENT;
extern clt_lnk CURRENT_CLIENT;
extern int CURRENT_INDEX;
extern int INIS;

//Initialises the 
//Clients linked List
//Return :
// 0 -> Success
// -1-> Failure
extern int clt_inis(clt_lnk NULL_client);

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