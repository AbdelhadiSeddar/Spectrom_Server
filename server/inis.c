#include "../_Imports.h"
int server_sock;
pthread_t SERVER_THREAD;
pthread_t SRVR_LSTN_THREAD;
pthread_t CLIENT_THREAD[2];
_Atomic int SERVER_STATE = 0;
_Atomic int CLIENT_STATES[2] = {_NotUsed, _NotUsed};

struct sockaddr_in server_addr;

unsigned int client_size = sizeof(struct sockaddr_in);

char *r;
void srvr_load(int argc, char *argv[])
{
    system("clear");

    cnsle_print_sys("Declaring Locals");

    cnsle_print_sys("Initializing Mutexes");


    cnsle_print_sys("Inisialising the List");
    clt_inis();
    cnsle_print_sys("Inisialized");
    cnsle_print_sys("Creating Socket");

    checkerr(server_sock = socket(AF_INET, SOCK_STREAM, 0), "Socket()");

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    cnsle_print_sys("Socket Created");
    cnsle_print_sys("Binding Socket");

    checkerr(bind(server_sock, (struct sockaddr *)&server_addr, sizeof(server_addr)), "Bind()");
    cnsle_print_sys("Binded");
    sprintf((r = malloc(sizeof(char) * 1024)), "Setting up Socket (%d) to listen", server_sock);
    cnsle_print_sys(r);

    sprintf(r, "Socket Queue is %s", (MAX_QUEUE != 0) ? "Set to " : "Not Set");
    cnsle_print_sys(r);
    if (MAX_QUEUE)
    {
        sprintf(r, "%d allowed connections pending", MAX_QUEUE);
        cnsle_print_sys(r);
    }

    checkerr(listen(server_sock, 100), "Listen Failed.");

    cnsle_print_sys("Initalizing Epoll");
    cnsle_print_sys("Setting up Listener");

    cnsle_print_sys("Server Succesfully Started. Accepting Requests/Commands.");
    pthread_create(&SRVR_LSTN_THREAD, NULL, srvr_listen, NULL);
}

void *srvr_listen(void *args)
{
    clt_inf *INCOMING_CLT;
    epoll_inis();

    SetNonBlocking(server_sock);
re:;
    for (;;)
    {
        epoll_load_fds();
        for (int n = 0; n < n_fds; n++)
        {
            if (evs[n].data.fd == server_sock)
            {

                if (SERVER_STATE)
                    continue;

                _Update_Server_S(_Used);
                checkerr(clt_accept(&INCOMING_CLT), "Could not accept a client");

                if (INCOMING_CLT->sock > server_sock)
                {
                    pthread_create(&SERVER_THREAD, NULL, srvr_accept_clt, (void *)(INCOMING_CLT));
                }

                continue;
            }
            else
            {
                if (!evs[n].data.fd)
                    continue;
                int i = 1;
                do
                {
                    i = !i;
                    if (CLIENT_STATES[i])
                        continue;
                    break;
                } while (1);

                ST_T *ST_INFO = malloc(sizeof(ST_T));
                ST_INFO->SOCK = evs[n].data.fd;
                ST_INFO->events = evs[n].events;

                char inf[256];
                sprintf(inf, "Selected Thread [ %d ] for socket %d", i, ST_INFO->SOCK);
                cnsle_print_sys(inf);
                _Update_Client_S(i, _Used);
                pthread_create(&(CLIENT_THREAD[i]), NULL, srvr_clt_handle, (void *)ST_INFO);
            }
        }
        epoll_unload_fds();
    }
}

void _Update_Client_S(int _Client_Thread, int _Status)
{
    if (_Client_Thread >= 2)
        return;

    CLIENT_STATES[_Client_Thread] = _Status;

    if (__SCRN_STATUS && _IS_CNSLE_ACTIVE)
        cnsle_update();
    return;
}
void _Update_Server_S(int _Status)
{
    SERVER_STATE = _Status;

    if (__SCRN_STATUS && _IS_CNSLE_ACTIVE)
        cnsle_update();
    return;
}
