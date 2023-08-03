#include "../_Imports.h"
int clts = 0;

void *srvr_accept_clt(void *arg)
{
    clt_inf *TEMP = clt_inf_clone((clt_inf *)arg);

    clts++;

    (TEMP->ID) = clts;

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
    rcv(&(info.SOCK), GUID, 36, 0);
    GUID[36] = '\0';
    checkerr(clt_find_local_uuid(NULL_CLIENT, GUID, &clt), "Could Not find USER");
    if (clt == NULL)
    {
        if (info.THREAD == &CLIENT_THREAD[0])
            CLIENTS_STATE--;
        else
            CLIENTS_STATE -= 10;
        return NULL;
    }

    clt_handling(info, &clt);

    if (info.THREAD == &CLIENT_THREAD[0])
        CLIENTS_STATE--;
    else
        CLIENTS_STATE -= 10;

    if (clt->Client.sock > server_sock)
    {
        epoll_ev *ev = malloc(sizeof(epoll_ev));
        ev->events = info.events;
        ev->data.fd = info.SOCK;
        epoll_add(info.SOCK, ev);
    }
    return NULL;
}

void clt_handling(ST_T INF, clt_lnk *clt)
{
    char rciv[4];
    rcv(&(INF.SOCK), rciv, 4, 0);
    sleep(2);
    switch (rciv[0])
    {
    case '0':
        if (!strcmp(rciv, STT_CONN_END))
            checkerr(CLT_CNTRL_DISC(clt), "Error While Disconnecting a Client");
        return;
    case '1':
        if (!strcmp(rciv, STT_CLT_RQST_LOGI))
            checkerr(CLT_CNTRL_LOGI(clt), "Error While Logging a Client");
        else if (!strcmp(rciv, STT_CLT_RQST_LOGO))
            checkerr(CLT_CNTRL_LOGO(clt), "Error While logging out a Client");
        return;
    case '3':
        if (!strcmp(rciv, STT_ACC_RQST_CONN))
            checkerr(CLT_CNTRL_LOGI(clt), "Error While Logging Client");
        return;
    default:
        break;
    }
}

int CLT_CNTRL_LOGI(clt_lnk *client)
{
    clt_lnk clt = *client;
    int MsgSize;
    char *Msg, MsgSizeString[5];
    char *Acc, *indx;
    int pos;
    char r[1024];
    sprintf(r, "Client:%d", clt->Client.ID);
    cnsle_print(r, " logging on ");

    rcv(&(clt->Client.sock), MsgSizeString, 5, 0);
    MsgSize = FBSizeToInt(MsgSizeString);
    Msg = malloc(MsgSize * sizeof(char));
    rcv(&(clt->Client.sock), Msg, MsgSize, 0);

    if ((indx = strchr(Msg, '\n')) == NULL)
        snd(clt->Client.sock, STT_ACC_INVR, 4, 0);
    Acc = malloc((pos = (int)(indx - Msg)) * sizeof(char) + 1);
    strncpy(Acc, Msg, pos);
    Acc[pos] = '\0';

    (clt->Account.USRNM) = Acc;

    Acc = malloc((pos = strlen(indx + 1)) * sizeof(char) + 1);
    strcpy(Acc, indx + 1);

    (clt->Account.PSWD) = Acc;
    (clt->Account.PSWD) = Acc;
    (clt->Account.state) = 1;

    snd(clt->Client.sock, STT_ACC_YES, 4, 0);
    return 0;
}

int CLT_CNTRL_REGS(clt_lnk *client)
{

    return 0;
}

int CLT_CNTRL_LOGO(clt_lnk *client)
{
    clt_lnk clt = *client;
    if (!(clt->Account.state))
    {
        snd(clt->Client.sock, STT_ACC_NCON, 4, 0);
        return 0;
    }

    usr_inf inf;
    clt->Account = inf;
    snd(clt->Client.sock, STT_CLT_SND_OK, 4, 0);
    return 0;
}

int CLT_CNTRL_DISC(clt_lnk *client)
{
    snd((*client)->Client.sock, STT_CONN_CONF, 4, 0);
    clt_disconnect(*client);
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