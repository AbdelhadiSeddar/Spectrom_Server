#include "../_Imports.h"
int server_sock, SERVER_STATE = 0, CLIENTS_STATE = 0;
pthread_t SERVER_THREAD;
pthread_t SRVR_LSTN_THREAD;
pthread_t CLIENT_THREAD[2];
pthread_mutex_t SERVER_MUTEX;
pthread_mutex_t CLIENT_MUTEX[2];
struct sockaddr_in server_addr;

clt_inf *INCOMING_CLT;
unsigned int client_size = sizeof(struct sockaddr_in);

void srvr_load(int argc, char *argv[])
{
    system("clear");
    printf("Starting Time is ");
    tprintf("");

    tprintf("Declaring Locals");

    tprintf("Initializing Mutexes");

    checkerr((pthread_mutex_init(&CURRENT_INFO_MUTEX, NULL) != 0), "Could not Initialize CURRENT_INFO_MUTEX");

    tprintf("Inisialising the List");
    clt_inis();
    tprintf("Inisialized");
    tprintf("Creating Socket");
    sleep(1);

    if ((server_sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("Socket()");
        exit(1);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    tprintf("Socket Created");
    // sleep(1);
    tprintf("Binding Socket");
    //sleep(1);

    if (bind(server_sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
    {
        perror("Bind()");
        exit(1);
    }

    tprintf("Binded");
    tprint();
    printf("Setting up Socket (%d) to listen\n", server_sock);
    tprint();
    printf("Socket Queue is %s", (MAX_QUEUE != 0) ? "Set to " : "Not Set\n");
    if (MAX_QUEUE)
    {
        printf("%d allowed connections pending\n", MAX_QUEUE);
    }

    checkerr(listen(server_sock, 100), "Listen Failed.");
    //sleep(1);

    tprintf("Initalizing Epoll");
    tprintf("Setting up Listener");

    tprintf("Server Succesfully Started. Accepting Requests/Commands.");
    pthread_create(&SRVR_LSTN_THREAD, NULL, srvr_listen, NULL);
}

void *srvr_listen(void *args)
{
    epoll_inis();
    checkerr(pthread_mutex_init(&SERVER_MUTEX, NULL), "SERVER_MUTEX Could not be Initialized");

    SetNonBlocking(server_sock);
re:;
    for (;;)
    {
        epoll_load_fds();

        for (int n = 0; n < n_fds; n++)
        {

            if (evs[n].data.fd == server_sock)
            {
                if (pthread_mutex_trylock(&SERVER_MUTEX) < -1)
                {
                    if (errno != EBUSY)
                    {
                        checkerr(-1, "Error handling SERVER_MUTEX");
                    }
                    else
                    {
                        if (!SERVER_STATE)
                        {
                            pthread_mutex_unlock(&SERVER_MUTEX);
                            SERVER_STATE = !SERVER_STATE;
                        }
                        else
                            continue;
                    }
                }

                SERVER_STATE = 1;
                checkerr(clt_accept(), "Could not accept a client");

                if ((INCOMING_CLT->sock) > server_sock)
                {
                    pthread_create(&SERVER_THREAD, NULL, srvr_accept_clt, (void *)INCOMING_CLT);
                }

                continue;
            }
            else
            {
                int i = 0;
                do
                {
                    i = !i;
                    if (pthread_mutex_trylock(&CLIENT_MUTEX[i]) < -1)
                    {
                        if (errno == EBUSY)
                        {
                            if (CLIENTS_STATE == 11)
                                continue;
                            else if (CLIENTS_STATE == 1)
                                pthread_mutex_unlock(&CLIENT_MUTEX[0]);
                            else if (CLIENTS_STATE == 10)
                                pthread_mutex_unlock(&CLIENT_MUTEX[1]);
                            else if (CLIENTS_STATE != 0)
                                checkerr(-1, "Invalid CLIENT_STATE value");
                        }
                        else
                        {
                            continue;
                        }
                    }
                    break;
                } while (1);

                ST_T ST_INFO;
                ST_INFO.SOCK = evs[n].data.fd;
                ST_INFO.events = evs[n].events;
                ST_INFO.THREAD = &CLIENT_THREAD[i];
                if (!i) // == 0
                    CLIENTS_STATE++;
                else
                    CLIENTS_STATE += 10;
                /*
                tprint();
                printf("Selected Thread [ %d ] for socket %d \n", i, ST_INFO.SOCK);
                */
                pthread_create(&(CLIENT_THREAD[i]), NULL, srvr_clt_handle, (void *)&ST_INFO);
            }
        }
        //sleep(3);
        epoll_unload_fds();
    }
}
