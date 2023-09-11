#include "../_Imports.h"
int clts = 0;

void *srvr_accept_clt(void *arg)
{
    clt_inf *TEMP = clt_inf_clone((clt_inf *)arg);
    free(((clt_inf *)arg)->addr);
    free((clt_inf *)arg);
    clts++;

    (TEMP->ID) = clts;

    clt_add(clt_new(TEMP));

    SERVER_STATE = !SERVER_STATE;
    free(TEMP);
    return NULL;
}

int clt_accept(clt_inf **INCOMING_CLT)
{
    clt_inf *CLT = malloc(sizeof(clt_inf));
    unsigned int client_size = sizeof(struct sockaddr_in);
    (CLT->addr) = malloc((size_t)client_size);

    int error = 0;
    while (((CLT->sock) = accept(server_sock, (struct sockaddr *)(CLT->addr), &client_size)) < 0)
    {
        if ((CLT->sock) < 0)
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
    *INCOMING_CLT = CLT;
    return 0;
}

void *srvr_clt_handle(void *arg)
{
    char GUID[37];
    clt_lnk clt;
    ST_T info = *(ST_T *)arg;
    free((ST_T *)arg);
    epoll_del((info.SOCK), NULL);
    rcv(&(info.SOCK), GUID, 36, 0);
    GUID[36] = '\0';
    checkerr((clt = clt_find_local_uuid(NULL_CLIENT, GUID)) == NULL ? -1 : 0, "Could Not find USER");
    if (clt == NULL)
    {
        RESET_THREAD();
        return NULL;
    }

    clt_handling(info, &clt);

    if (clt->Client.sock > server_sock)
    {
        epoll_ev *ev = malloc(sizeof(epoll_ev));
        ev->events = info.events;
        ev->data.fd = info.SOCK;
        epoll_add(info.SOCK, ev);
        free(ev);
    }
    RESET_THREAD();
    return NULL;
}

void clt_handling(ST_T INF, clt_lnk *clt)
{
    char rciv[4];
    rcv(&(INF.SOCK), rciv, 4, 0);
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
        else if (!strcmp(rciv, STT_CLT_RQST_REGS))
            checkerr(CLT_CNTRL_REGS(clt), "Error While registering an Account");
        return;
    case '3':
        if (!strcmp(rciv, STT_ACC_RQST_CONN))
            checkerr(CLT_CNTRL_LOGI(clt), "Error While Logging Client");
        return;
    default:
        break;
    }
}

int CLT_CNTRL_DISC(clt_lnk *client)
{
    return clt_disconnect(*client);
}

int CLT_CNTRL_RCN(clt_lnk client)
{
    char MsgSize[5];
    char Str[1024];
    snd(client->Client.sock, STT_CONN_RCN, 4, 0);
    if (client->Account.state == _LOGGED)
    {
        snd(client->Client.sock, STT_ACC_ALR, 4, 0);
        sprintf(Str, "%s\n%s", client->Account.UUID, client->Account.USRNM);
        FByteSize(Str, MsgSize);
        snd(client->Client.sock, MsgSize, 5, 0);
        snd(client->Client.sock, Str, FBSizeToInt(MsgSize), 0);
    }
    else
    {
        snd(client->Client.sock, STT_ACC_NCON, 4, 0);
    }
    return 0;
}

int CLT_CNTRL_LOGI(clt_lnk *client)
{
    clt_lnk clt = *client;
    int MsgSize;
    char *Msg, MsgSizeString[5];
    char *Acc, *indx;
    int pos;

    rcv(&(clt->Client.sock), MsgSizeString, 5, 0);
    MsgSize = FBSizeToInt(MsgSizeString);
    Msg = malloc(MsgSize * sizeof(char));
    rcv(&(clt->Client.sock), Msg, MsgSize, 0);

    if ((indx = strchr(Msg, UNIT_SEPARATOR)) == NULL)
    {
        snd(clt->Client.sock, STT_ACC_INVR, 4, 0);
        return 0;
    }
    Acc = calloc((pos = (int)(indx - Msg)) + 1, sizeof(char));
    strncpy(Acc, Msg, pos);
    Acc[pos] = '\0';
    clt->Account.USRNM = calloc(strlen(Acc) + 1, sizeof(char));
    strcpy(clt->Account.USRNM, Acc);

    free(Acc);
    Acc = calloc((pos = strlen(indx + 1) + 1), sizeof(char));
    strcpy(Acc, indx + 1);

    clt->Account.PSWD = malloc(strlen(Acc) * sizeof(char) + 1);
    strcpy(clt->Account.PSWD, Acc);
    free(Acc);

    (clt->Account.state) = _LOGGED;

    snd(clt->Client.sock, STT_ACC_YES, 4, 0);
    free(Msg);
    return 0;
}

#define W_FNAME 1
#define W_LNAME 2
#define W_EMAIL 4
int CLT_CNTRL_REGS(clt_lnk *client)
{
    clt_lnk clt = *client;
    char *Msg, *Msg_R, MsgSizeString[5], *indx, *temp;
    int MsgSize, pos;

    rcv(&(clt->Client.sock), MsgSizeString, 5, 0);
    MsgSize = FBSizeToInt(MsgSizeString);
    Msg = malloc(MsgSize * sizeof(char));
    Msg_R = Msg;
    rcv(&(clt->Client.sock), Msg_R, MsgSize, 0);

    if ((indx = strchr(Msg_R, UNIT_SEPARATOR)) == NULL)
    {
        snd(clt->Client.sock, STT_ACC_INVR, 4, 0);
        return 0;
    }

    temp = calloc((pos = (int)(indx - Msg_R)) + 1, sizeof(char));
    strncpy(temp, Msg_R, pos);
    temp[pos] = '\0';
    // Temp now == Username

    Msg_R = (char *)(indx + 1);
    if ((indx = strchr(Msg_R, UNIT_SEPARATOR)) == NULL)
    {
        snd(clt->Client.sock, STT_ACC_INVR, 4, 0);
        return 0;
    }
    temp = calloc((pos = (int)(indx - Msg_R)) + 1, sizeof(char));
    strncpy(temp, Msg_R, pos);
    temp[pos] = '\0';
    // Temp now == Passsword

    Msg_R = (char *)(indx + 1);
    if ( Msg_R[0] == '\0')
    {
        snd(clt->Client.sock, STT_ACC_INVF, 4, 0);
        return 0;
    }
    //  Get the registeration format
    int Regs_format;
    temp = calloc(2, sizeof(char));
    strncpy(temp, Msg_R, 1);
    temp[1] = '\0';
    Regs_format = StringToInt(temp);

    if (Regs_format & W_FNAME)
    {
        Msg_R = (char *)(indx + 1);
        if ((indx = strchr(Msg_R, UNIT_SEPARATOR)) == NULL)
        {
            snd(clt->Client.sock, STT_ACC_INVF, 4, 0);
            return 0;
        }
        temp = calloc((pos = (int)(indx - Msg_R)) + 1, sizeof(char));
        strncpy(temp, Msg_R, pos);
        temp[pos] = '\0';
        // Temp now == First Name
    }
    if (Regs_format & W_LNAME)
    {
        Msg_R = (char *)(indx + 1);
        if ((indx = strchr(Msg_R, UNIT_SEPARATOR)) == NULL)
        {
            snd(clt->Client.sock, STT_ACC_INVF, 4, 0);
            return 0;
        }
        temp = calloc((pos = (int)(indx - Msg_R)) + 1, sizeof(char));
        strncpy(temp, Msg_R, pos);
        temp[pos] = '\0';
        // Temp now == Last Name
    }
    if (Regs_format & W_EMAIL)
    {
        Msg_R = (char *)(indx + 1);
        if ((indx = strchr(Msg_R, UNIT_SEPARATOR)) == NULL)
        {
            snd(clt->Client.sock, STT_ACC_INVF, 4, 0);
            return 0;
        }
        temp = calloc((pos = (int)(indx - Msg_R)) + 1, sizeof(char));
        strncpy(temp, Msg_R, pos);
        temp[pos] = '\0';
        // Temp now == Email
    }

    snd(clt->Client.sock, STT_ACC_YES, 4, 0);
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

clt_inf *clt_inf_clone(clt_inf *original)
{
    if (original == NULL)
        return NULL;

    clt_inf *Return = malloc(sizeof(clt_inf));

    Return->file = (original->file);
    Return->sock = (original->sock);
    Return->ID = (original->ID);
    Return->addr = (original->addr);
    strcpy(Return->GUID, (original->GUID));

    return Return;
}