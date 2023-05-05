#include "../_Imports.h"
int clts = 0;
void *srvr_accept_clt(void *arg)
{
    clt_inf *TEMP = clt_inf_clone((clt_inf *)arg);

    clts++;
    /*
    tprint();
    printf("Accepted client %d, on socket %d\n", clts, (TEMP->sock));
    */
    (TEMP->ID) = clts;
    // When accepted
    clt_add(clt_new(*TEMP));

    SERVER_STATE = !SERVER_STATE;
    return NULL;
}

int clt_accept()
{
    if (INCOMING_CLT == NULL)
    {
        INCOMING_CLT = malloc(sizeof(clt_inf));
        unsigned int client_size = sizeof(struct sockaddr_in);
        (INCOMING_CLT->addr) = malloc((size_t)client_size);
    }

    int error = 0;
    while (((INCOMING_CLT->sock) = accept(server_sock, (struct sockaddr *)&(INCOMING_CLT->addr), &client_size)) < 0)
    {
        if ((INCOMING_CLT->sock) < 0)
            break;
        /*
        tprint();
        printf("Could not Accept() on socket %d, Tries left %d.", (INCOMING_CLT->sock), (5 - (error)));
        */
        if (error < 5)
        {
            error++;
        }
        else
        {
            return -1;
        }
    }
    return 0;
}

void *srvr_clt_handle(void *arg)
{
    char GUID[37];
    clt_lnk clt;
    ST_T info = *(ST_T *)arg;
    epoll_del((info.SOCK), NULL);
    recv(info.SOCK, GUID, 37, 0);
    checkerr(clt_find_local_uuid(NULL_CLIENT, GUID, &clt), "Could Not find USER");
    if (clt != NULL)
    {
        clt_handling(info, &clt);
    }
    else
    {
        /*
        tprintf("NULL Client");
        */
    }

    if (info.THREAD == &CLIENT_THREAD[0])
        CLIENTS_STATE--;
    else
        CLIENTS_STATE -= 10;

    epoll_ev *ev = malloc(sizeof(epoll_ev));
    ev -> events = info.events;
    epoll_add(info.SOCK, ev);
    return NULL;
}

void clt_handling(ST_T INF, clt_lnk *clt)
{
    char rcv[4];
    recv(INF.SOCK, rcv, 4, 0);
    if ((rcv[1]) == '1')
    {
        if (strcmp(rcv, "110") == 0)
        {
            checkerr(CLT_CNTRL_LOGI(clt), "Error While Logging Client");
        }
    }
    else
        checkerr(-1, "Client Sent Invalid Code");
}

int CLT_CNTRL_LOGI(clt_lnk *client)
{
    clt_lnk clt = *client;
    int MsgSize;
    char *Msg, MsgSizeString[5];
    
    //tprintf("Requesting Username.");
    send(clt->Client.sock, CMD_CLT_SND_USRN, 4, 0);

    recv(clt->Client.sock, MsgSizeString, 5, 0);
    
    MsgSize = FBSizeToInt( MsgSizeString);
    Msg = malloc(MsgSize * sizeof(char));
    recv(clt->Client.sock, Msg, MsgSize, 0);
    //tprint();
    //printf("Received Username : %s \n",Msg);

    send(clt->Client.sock, CMD_CLT_SND_PSWD,4 , 0);
    //tprintf("Requesting Password.");
    recv(clt->Client.sock, MsgSizeString, 5, 0);
    checkerr((MsgSize = FBSizeToInt(MsgSizeString)), "Could Not Load Size Into an int");
    Msg = calloc(MsgSize, sizeof(char));
    recv(clt->Client.sock, Msg, MsgSize, 0);
    //tprint();
    //printf("Received Password : %s \n",Msg);

    send(clt->Client.sock, CMD_CONN_CONF, 4,0);

    return 0;
}

int CLT_CNTRL_REGS(clt_lnk *client)
{

    return 0;
}

int CLT_CNTRL_LOGO(clt_lnk *client)
{
    return 0;
}

clt_inf *clt_inf_clone(clt_inf *original)
{
    if (original == NULL)
        return NULL;

    clt_inf *re = malloc(sizeof(clt_inf));

    (re->file) = (original->file);
    (re->sock) = (original->sock);
    (re->ID) = (original->ID);
    (re->addr) = (original->addr);
    strcpy((re->GUID), (original->GUID));

    return re;
}