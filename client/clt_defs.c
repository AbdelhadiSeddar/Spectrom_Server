#include "../_Imports.h"

pthread_mutex_t CURRENT_INFO_MUTEX;

clt_lnk CLT_LIST = NULL;
clt_lnk NULL_CLIENT = NULL;
int INIS = 0;

int clt_inis()
{
    INIS = 1;
    NULL_CLIENT = malloc(sizeof(*NULL_CLIENT));
    CLT_LIST = NULL_CLIENT;
    strcpy((NULL_CLIENT->Client.GUID), "00000000-0000-0000-0000-000000000000");
    int sock = 3;

    NULL_CLIENT->left = NULL;
    NULL_CLIENT->right = NULL;

    return 0;
}

clt_lnk clt_new(clt_inf Info)
{
    clt_lnk re = malloc(sizeof(clt));

    re->Client = Info;

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

int clt_add(clt_lnk New_Client)
{
    send((New_Client->Client.sock), CMD_CONN_ACC, 4, 0);
    /// Recive GUID
    char *err;
    sprintf(err, "Could not Initialize Mutex for Client On Socket : %d", (New_Client->Client.sock));
    checkerr(pthread_mutex_init(&(New_Client->MUTEX), NULL), err));
    pthread_mutex_lock(&(New_Client->MUTEX));
    send((New_Client->Client.sock), CMD_CLT_SND_GUID, 4, 0);
    recv((New_Client->Client.sock), (New_Client->Client.GUID), 37, 0);
    pthread_mutex_unlock(&(New_Client->MUTEX));

    pthread_mutex_lock(&CURRENT_INFO_MUTEX);

    int re = clt_add_R(NULL_CLIENT, New_Client);

    pthread_mutex_unlock(&CURRENT_INFO_MUTEX);
    send((New_Client->Client.sock), CMD_CONN_CONF, 4, 0);
    send((New_Client->Client.sock), CMD_CONN_MTH, 4, 0);
    return re;
}

int clt_add_R(clt_lnk Tree, clt_lnk NewClient)
{

    if (!INIS)
        clt_inis();

    for (int i = 0; i < 37; i++)
    {
        if ((NewClient->Client.GUID[i]) < (Tree->Client.GUID[i]))
        {
            if (!(Tree->right))
                return clt_add_R(Tree->right, NewClient);
            else
            {
                Tree->right = NewClient;
                return 0;
            }
        }
        else if ((NewClient->Client.GUID[i]) > (Tree->Client.GUID[i]))
        {
            if (!(Tree->left))
                return clt_add_R(Tree->left, NewClient);
            else
            {
                Tree->left = NewClient;
                return 0;
            }
        }
    }

    return -1;
}

int clt_find_local_uuid(clt_lnk Tree, char *GUID, clt_lnk *Client)
{
    if ((*Tree) == NULL)
        return -1;

    for (int i = 0; i < 37; i++)
    {
        if ((GUID[i]) < (Tree->Client.GUID[i]))
        {
            if (!(Tree->right))
                return clt_find_local_uuid(Tree->right, GUID, Client);
        }
        else if ((GUID[i]) > (Tree->Client.GUID[i]))
        {
            if (!(Tree->left))
                return clt_find_local_uuid(Tree->left, Client);
        }
    }

    *Client = Tree;
    return 0;

    return 0;
}
