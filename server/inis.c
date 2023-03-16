#include "../_Imports.h"
int server_sock, SERVER_STATE = 0, CLIENTS_STATE = 0;
pthread_t SERVER_THREAD;
pthread_t CLIENT_THREAD[2];
pthread_mutex_t SERVER_MUTEX;
pthread_mutex_t CLIENT_MUTEX[2];

void srvr_load(int argc, char *argv[])
{
    printf("Starting Time is ");
    tprintf("");
    tprintf("Declaring Locals\n");

    struct sockaddr_in server_addr;
    tprintf("Initializing Mutexes\n");

    checkerr((pthread_mutex_init(&CURRENT_INFO_MUTEX, NULL) != 0), "Could not Initialize CURRENT_INFO_MUTEX");

    tprintf("Inisialising the List\n");
    clt_inis();
    tprintf("Inisialized\n");
    tprintf("Creating Socket\n");
    sleep(1);
    if ((server_sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("Socket()");
        exit(1);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    tprintf("Socket Created\n");
    sleep(1);
    tprintf("Binding Socket\n");
    sleep(1);

    if (bind(server_sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
    {
        perror("Bind()");
        exit(1);
    }

    tprintf("Binded\n");
    sleep(1);
    tprintf("");
    printf("Setting up Socket (%d) to listen\n", server_sock);
    tprintf("");
    printf("Socket Queue is %s", (MAX_QUEUE != 0) ? "Set to " : "Not Set\n");
    if (MAX_QUEUE)
    {
        tprintf("");
        printf("%d allowed connections pending\n", MAX_QUEUE);
    }

    sleep(1);
    checkerr(listen(server_sock, 100), "Listen Failed.");

    tprintf("Setting up Listener\n");

    pthread_t cmd;
    pthread_create(&cmd, NULL, srvr_cmd, NULL);

    srvr_listen(argc, argv);
}

void srvr_listen(int argc, char *argv[])
{
    tprintf("Initalizing Epoll");
    epoll_inis();
    checkerr(pthread_mutex_init(&SERVER_MUTEX, NULL), "SERVER_MUTEX Could not be Initialized");
re:;
    for (;;)
    {
        epoll_load_fds();

        for (int n = 0; n < n_fds; ++n)
        {
            char PEEK[4];
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
                            pthread_mutex_unlock(&SERVER_MUTEX);
                        else
                            continue;
                    }
                }
                else if (recv(server_sock, PEEK, 4, MSG_PEEK) != 0)
                {
                    if (!SERVER_STATE)
                    {
                        SERVER_STATE = 1;
                        tprintf("Test1");
                        pthread_create(&SERVER_THREAD, NULL, srvr_accept_clt, NULL);
                        continue;
                    }
                }
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

                    tprintf("Got ahold of a Mutex and initializing Client.");
                    ST_T ST_INFO;
                    ST_INFO.SOCK = evs[n].data.fd;
                    ST_INFO.THREAD = &CLIENT_THREAD[i];
                    if (!i) // == 0
                        CLIENTS_STATE++;
                    else
                        CLIENTS_STATE += 10;
                    tprintf("");
                    printf("Selected Thread [ %d ] for socket %d \n", i, ST_INFO.SOCK);
                    pthread_create(&(CLIENT_THREAD[i]), NULL, srvr_clt_handle, (void *)&ST_INFO);
                    break;
                } while (1);
            }
        }
    }
}

void *srvr_cmd(void *_args)
{
e:;
    char cmd[10];
    scanf("%s", cmd);
    printf(cmd);
    goto e;
}
