#include "../_Imports.h"

void *srvr_accept_clt(void *arg)
{
    clt_inf *TEMP = malloc(sizeof(clt_inf));
    unsigned int client_size = sizeof(struct sockaddr_in);
    (TEMP->addr) = malloc((size_t)client_size);
    int error = 0;
    int clts = 0;
re:;
    if (((TEMP->sock) = accept(server_sock, (struct sockaddr *)&(TEMP->addr), &client_size)) < 0)
    {
        perror("Accept() ");
        if (error < 20)
        {
            error++;
            goto re;
        }
        else
            exit(1);
    }
    tprintf("");
    printf("Accepted client %d, on socket %d\n", clts, (TEMP->sock));
    if (clts)
    {
        // When accepted
        clt_add(clt_new(*TEMP));
        clts++;
    }
    else
    {
        close((TEMP->sock));
    }
    SERVER_STATE = !SERVER_STATE;
}

void *srvr_clt_handle(void *arg)
{
    char GUID[37];
    clt_lnk clt;
    ST_T info = (struct SOCKET_THREAD_T)arg;
    recv(info.SOCK, GUID, 37, 0);
    clt_find_local_uuid(NULL_CLIENT, GUID, &clt);
    clt_handling(&clt);

    if (info.THREAD == &CLIENT_THREAD[0])
        CLIENTS_STATE--;
    else
        CLIENTS_STATE -= 10;
    return NULL;
}

void clt_handling(clt_lnk *clt)
{
    char rcv[4];
    recv((*clt)->Client.sock, rcv, 4, 0);
    if ((rcv[1]) == '1')
        switch ((rcv[2]))
        {
        case '1':

            switch ((rcv[3]))
            {
            case '0':
                checkerr(CLT_CNTRL_LOGI(clt), "Error While Logging Client");
                break;

            case '1':
                /* code */
                break;

            case 'F':
                /* code */
                break;

            default:
                break;
            }

            break;

        default:
            break;
        }
    else
        checkerr(-1, "Client Sent Invalid Code");
}

int CLT_CNTRL_LOGI(clt_lnk *client)
{
    clt_lnk clt = *client;
    int MsgSize;
    char *Msg, MsgSizeString[5];
    send(clt->Client.sock, CMD_CLT_SND_USRN, 4, 0);

    recv(clt->Client.sock, MsgSizeString, 5, 0);
    checkerr((MsgSize = FBSizeToInt(MsgSizeString)), "Could Not Write Message Size into and Int CHECK the VALUE!");
    Msg = calloc(MsgSize, sizeof(char));
    recv(clt->Client.sock, Msg, MsgSize, 0);
    teprintf("Received Username : ");
    printf(Msg);
    teprintf("Received Username : ");
    printf(Msg);

    recv(clt->Client.sock, MsgSizeString, 5, 0);
    checkerr((MsgSize = FBSizeToInt(MsgSizeString)), "Could Not Load Size Into an int");
    Msg = calloc(MsgSize, sizeof(char));
    recv(clt->Client.sock, Msg, MsgSize, 0);
    teprintf("Received Password : ");
    printf(Msg);
    send(clt->Client.sock, CMD_CLT_SND_PSWD, 4, 0);

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
