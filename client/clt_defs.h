#ifndef CLT_DEFS_H
#define CLT_DEFS_H
#include <sys/epoll.h>

#define _NOTLOGGED 0
#define _LOGGED 1


typedef struct client_info_t clt_inf;
typedef struct client_links clt;
typedef struct client_links *clt_lnk;
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
struct usr_info_t
{
    int state;// States [ _NOTLOGGED : Not Connected | _LOGGED: Connected ]
    char UUID[37];
    char *USRNM;
    char *PSWD;
};

struct client_links
{
    pthread_mutex_t MUTEX;
    int INDEX;
    struct epoll_event epoll_ev;
    clt_inf Client;
    usr_inf Account;
    clt_lnk next;   // For Linked List Struct
    clt_lnk prev;   // For Linked List Struct
    
    clt_lnk left;   // For Binary Tree Struct 
    clt_lnk right;  // For Binary Tree Struct
    
};

extern pthread_mutex_t CURRENT_INFO_MUTEX;
extern int INIS;
extern clt_lnk CLT_LIST;
extern clt_lnk NULL_CLIENT;

/// @brief Initialise Client List
/// @return -1 => Error |[]| 0 => Initialized.
extern int clt_inis();

/// @brief Creates new Client Structure
/// @param Info Pointer to Client Information (See struct client_info)
/// @return NULL => ERROR |[]| clt_lnk => Pointer to new Client
extern clt_lnk clt_new(clt_inf *Info);

extern clt_inf *clt_inf_clone(clt_inf *original);

/// @brief Updates the existing client's required info.
/// @param Original Client's Old save pointer
/// @param temp Client's new save pointer after reconnecting
extern void clt_update(clt_lnk Original, clt_lnk temp);

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

/// @brief Binary Search Tree of a Client Using GUID.
/// @param Tree
/// @param GUID
/// @return  NULL => Client Not Found. |[]| Pointer of Type [clt_lnk] returned
extern clt_lnk clt_find_local_uuid(clt_lnk Tree, char *GUID);
extern clt_lnk clt_find_local_uuid_fv(clt_lnk Tree);

/// @brief Searches for a client using their ID
/// @param cltid CLient's id
/// @param Client Return Not Found  |[]| 1 => Client Found
extern int clt_find_local_ClientID(int cltid, clt_lnk *Client);

/// @brief Searches for a client using their Socket
/// @param cltid CLient's id
/// @param Client 0 => Return Not Found  |[]| 1 => Client Found
extern int clt_find_local_sock(int sockfd, clt_lnk *Client);

/// @brief Disconnects from a client but allow for reconnection
/// @return 0 => Works as intended
extern int clt_disconnect(clt_lnk clt);

/// @brief Disconnects & Remove from the memory
/// @return 0 => Works as intended
extern int clt_remove(clt_lnk clt);

/*
//Deletion Functions
// Returns :
// 0 -> Success
// 1 -> User non-existant (Fail)

extern int clt_delete_runtime_findex(int index);
extern int clt_delete_runtime_fsock(int sock);
extern int clt_delete_runtime_fuuid(const char* UUID);
extern int clt_delete_runtime_fid(int ID);
*/

#endif