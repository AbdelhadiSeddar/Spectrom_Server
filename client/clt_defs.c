#include "../_Imports.h"
#include "clt_defs.h"

pthread_mutex_t CURRENT_INFO_MUTEX;

clt_lnk CLT_LIST = NULL;
clt_lnk NULL_CLIENT = NULL;
int INIS = 0;

int clt_inis()
{
    INIS = 1;
    NULL_CLIENT = malloc(sizeof(clt));
    CLT_LIST = NULL_CLIENT;
    strcpy((NULL_CLIENT->Client.GUID), "00000000-0000-0000-0000-000000000000");
    int sock = -1;
    NULL_CLIENT ->Client.addr = NULL;
    NULL_CLIENT ->Client.ID = 0;
    NULL_CLIENT ->INDEX = 0;

    NULL_CLIENT->left = NULL;
    NULL_CLIENT->right = NULL;

    return 0;
}

clt_lnk clt_new(clt_inf *Info)
{
    clt_lnk re = malloc(sizeof(clt));

    re->Client = *Info;
    re->left = (re->right = NULL);
    return re;
}

clt_inf clt_inf_new(FILE *file, int sock, int ID, char *GUID, sa_in Addr)
{
    clt_inf re;
    re.file = file;
    re.sock = sock;
    re.ID = ID;
    re.addr = Addr;
    return re;
}

int clt_disconnect(clt_lnk clt)
{
    if (clt == NULL)
        return -1;

    epoll_del(clt->Client.sock, &(clt->epoll_ev));
    close(clt->Client.sock);
    clt->Client.sock = -1;
    char cli[32];
    sprintf(cli, "Client:%d", (clt->Client.ID));
    cnsle_print(cli, "Has Disconnected");
    clts--;
    return 1;
}

int clt_add(clt_lnk New_Client)
{
    ev.events = EPOLLIN | EPOLLET;
    ev.data.fd = (New_Client->Client.sock);
    New_Client->epoll_ev = ev;
    epoll_add((New_Client->Client.sock), &ev);
    /*  Send "Accepted" Connection   */
    snd((New_Client->Client.sock), STT_CONN_ACC, 4, 0);
    /// Recive GUID
    char err[255];
    sprintf(err, "Could not Initialize Mutex for Client On Socket : %d", (New_Client->Client.sock));
    checkerr(pthread_mutex_init(&(New_Client->MUTEX), NULL), err);
    pthread_mutex_lock(&(New_Client->MUTEX));
    snd((New_Client->Client.sock), STT_CLT_SND_GUID, 4, 0);
    rcv(&(New_Client->Client.sock), (New_Client->Client.GUID), 37, 0);
    cnsle_print_sys((New_Client->Client.GUID));
    pthread_mutex_unlock(&(New_Client->MUTEX));
    clt_lnk Old_Client;
    if ((Old_Client = clt_find_local_uuid(NULL_CLIENT, (New_Client->Client.GUID))) != NULL)
    {
        clt_inf *Cloned;
        (Old_Client->Client) = *(Cloned = clt_inf_clone(&(New_Client->Client)));
        CLT_CNTRL_RCN(Old_Client);
        char own[64];
        sprintf(own, "Client:%d", (Old_Client->Client.ID));
        cnsle_print(own, "Reconnected");
        free(Cloned);
        free(New_Client);
        return 1;
    }
    else
    {
        pthread_mutex_lock(&CURRENT_INFO_MUTEX);
        checkerr(clt_add_R(NULL_CLIENT, New_Client), "Error While adding");

        pthread_mutex_unlock(&CURRENT_INFO_MUTEX);
        snd((New_Client->Client.sock), STT_CONN_CONF, 4, 0);
        snd((New_Client->Client.sock), STT_CONN_MTH, 4, 0);
        char own[128];
        sprintf(own, "Client:%d", (New_Client->Client.ID));
        cnsle_print(own, "Logged in");

        New_Client->Account.state = _NOTLOGGED;
        strcpy(New_Client->Account.UUID, (NULL_CLIENT->Client.GUID));

        return 0;
    }
}

int clt_add_R(clt_lnk Tree, clt_lnk NewClient)
{

    if (!INIS)
        clt_inis();

    int res;
    if ((res = strcmp((NewClient->Client.GUID), (Tree->Client.GUID))) < 0)
    {
        if ((Tree->right) != NULL)
            return clt_add_R(Tree->right, NewClient);
        else
        {
            Tree->right = NewClient;
            return 0;
        }
    }
    else if (res > 0)
    {
        if ((Tree->left) != NULL)
            return clt_add_R(Tree->left, NewClient);
        else
        {
            Tree->left = NewClient;
            return 0;
        }
    }

    return -1;
}

clt_lnk clt_find_local_uuid(clt_lnk Tree, char *GUID)
{
    if ((Tree) == NULL)
        return NULL;

    int res;
    if ((res = strcmp(GUID, (Tree->Client.GUID))) < 0)
    {
        return clt_find_local_uuid(Tree->right, GUID);
    }
    else if (res > 0)
    {
        return clt_find_local_uuid(Tree->left, GUID);
    }
    else
    {
        return Tree;
    }
}

clt_lnk clt_find_local_uuid_fv(clt_lnk Tree)
{
    if ((Tree) == NULL)
        return NULL;

    if (Tree->Client.sock > 0)
    {
        return Tree;
    }

    clt_lnk re;
    if ((re = clt_find_local_uuid_fv(Tree->right)) != NULL)
        return re;
    if ((re = clt_find_local_uuid_fv(Tree->left)) != NULL)
        return re;
    return NULL;
}

int clt_find_local_ClientID_R(clt_lnk Tree, int cltid, clt_lnk *Client)
{
    if (Tree == NULL)
        return 0;

    if (Tree->Client.ID == cltid)
    {
        *Client = Tree;
        return 1;
    }

    if (clt_find_local_ClientID_R(Tree->left, cltid, Client))
        return 1;
    else if (clt_find_local_ClientID_R(Tree->right, cltid, Client))
        return 1;

    return 0;
}
int clt_find_local_ClientID(int cltid, clt_lnk *Client)
{
    if (!NULL_CLIENT)
        return -1;

    if (clt_find_local_ClientID_R(NULL_CLIENT->left, cltid, Client))
        return 1;
    else if (clt_find_local_ClientID_R(NULL_CLIENT->right, cltid, Client))
        return 1;
    else
        return 0;
}

int clt_find_local_sock_R(clt_lnk Tree, int sockfd, clt_lnk *Client)
{
    if (Tree == NULL)
        return 0;

    if (Tree->Client.sock == sockfd)
    {
        *Client = Tree;
        return 1;
    }
    else
    {
        if (clt_find_local_sock_R(Tree->left, sockfd, Client))
            return 1;
        else if (clt_find_local_sock_R(Tree->right, sockfd, Client))
            return 1;
        else
            return 0;
    }
}
int clt_find_local_sock(int sockfd, clt_lnk *Client)
{
    if (!NULL_CLIENT)
        return -1;

    if (clt_find_local_sock_R(NULL_CLIENT->left, sockfd, Client))
        return 1;
    else if (clt_find_local_sock_R(NULL_CLIENT->right, sockfd, Client))
        return 1;
    else
        return 0;
}
