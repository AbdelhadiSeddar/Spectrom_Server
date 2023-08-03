#ifndef CLT_DEFS_H
#define CLT_DEFS_H

#include <sys/epoll.h>

typedef struct client_info_t clt_inf;
typedef struct client_links *clt_lnk;
typedef struct client_links clt;
typedef struct sockaddr_in *sa_in;

typedef struct usr_info_t usr_inf;

struct client_info_t
{
    FILE *file;
    int sock;
    int ID;
    char GUID[37];
    struct sockaddr_in *addr;
};
// States [ 0: Not Connected | 1: Connected ]
struct usr_info_t
{
    int state;
    char UUID[37];
    char *USRNM;
    char *PSWD;
    // char KEY[256];
};

struct client_links
{
    pthread_mutex_t MUTEX;
    int INDEX;
    struct epoll_event epoll_ev;
    clt_inf Client;
    usr_inf Account;
    clt_lnk left;
    clt_lnk right;
};

extern pthread_mutex_t CURRENT_INFO_MUTEX;
extern int INIS;
extern clt_lnk CLT_LIST;
extern clt_lnk NULL_CLIENT;

/// @brief Disconnects from a client but allow for reconnection
/// @return 0 => Works as intended
int clt_disconnect(clt_lnk clt);

/// @brief Disconnects & Remove from the memory
/// @return 0 => Works as intended
int clt_remove(clt_lnk clt);

/// @brief Initialise Client List
/// @return -1 => Error |[]| 0 => Initialized.
extern int clt_inis();

/// @brief Creates new Client Structure
/// @param Info Client Information (See struct client_info)
/// @return NULL => ERROR |[]| clt_lnk => Pointer to new Client
extern clt_lnk clt_new(clt_inf Info);

/// @brief Creates new Client Structure
/// @param Info Client Information (See struct client_info)
/// @param file
/// @param sock
/// @param ID
/// @param ID
/// @param Addr
/// @return clt_inf => New Client info struct
extern clt_inf clt_inf_new(FILE *file, int sock, int ID, char *GUID, sa_in Addr);

/// @brief Add Client to the Binary Search Tree.
/// @param NewClient
/// @return 0 => Client Added Successfully |[]| -1 => Client Already Exists
extern int clt_add(clt_lnk New_Client);

/// @brief Add Client to the Binary Search Tree Recursively.
/// @param Tree Head
/// @param NewClient
/// @return 0 => Client Added Successfully |[]| -1 => Client Already Exists
extern int clt_add_R(clt_lnk Tree, clt_lnk NewClient);
/*
//Check for past Connections
// Returns:
// -1-> Invalid
// 0 -> Correct
// 1 -> Incorrect

extern int clt_find_local_sock(int sock, clt_lnk* New_Client);
*/

/// @brief Binary Search Tree of a Client Using GUID ( Currently being the fastest search method due to GUID being the Primary Index).
/// @param Tree
/// @param GUID
/// @param Client
/// @return 0 => Client Found and Returned in *Client* parameter. |[]| -1 => Client Not Found.
extern int clt_find_local_uuid(clt_lnk Tree, char *GUID, clt_lnk *Client);

extern int clt_find_local_sock(int sockfd, clt_lnk *Client);
/*
//Deletion Functions
// Returns :
// 0 -> Success
// 1 -> User non-existant (Fail)

extern int clt_delete_runtime_findex(int index);
extern int clt_delete_runtime_fsock(int sock);
extern int clt_delete_runtime_fuuid(const char* UUID);
extern int clt_delete_runtime_fid(int ID);

//Case of Reconnection
//Returns:
// 0 -> Success
// 1 -> Client non-existant
//////// FIx here GIVE ALL to-be-updates values (NULL them if you dont want to change), search using ###### /////
extern int clt_update_runtime_findex(const int* sock, const char* UUID, const int* ID, int INDEX);
extern int clt_update_runtime_fsock(const char* UUID, const int* ID, int sock);
//NotYet
/*
extern int clt_update_runtime_fthread(const int* sock, const char* UUID, const int* ID, int INDEX);
*/

#endif