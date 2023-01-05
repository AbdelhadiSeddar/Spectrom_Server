#include "../_Imports.h"


void srvr_load(int argc, char *argv[]){
    printf("Starting Time is "); tprintf("");
    tprintf("Declaring Locals\n");
    int server_sock;
    struct sockaddr_in server_addr;
    tprintf("Initializing Mutexes\n");

    if (pthread_mutex_init(&CURRENT_INFO_MUTEX, NULL) != 0) {
        perror("\n mutex init has failed\n");
        exit(1);
    }


    tprintf("Inisialising the List\n");
    clt_inis();
    tprintf("Inisialized\n");
    tprintf("Creating Socket\n");
    sleep(1);
    if((server_sock = socket(AF_INET, SOCK_STREAM, 0)) < 0){
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

    if(bind(server_sock, (struct sockaddr *) &server_addr, sizeof(server_addr)) < 0 ){
        perror("Bind()");
        exit(1);
    }

    tprintf("Binded\n");
    sleep(1);

    tprintf("Setting up Socket (%d) to listen\n", server_sock);
    tprintf("Socket Queue is %s", (MAX_QUEUE != 0) ? "Set to ": "Not Set\n");
    if(MAX_QUEUE)
        tprintf("%d allowed connections pending\n", MAX_QUEUE);
    
    sleep(1);
    if(listen(server_sock, 100) < 0){
        perror("Listen()");
        exit(1);
    }
    
    tprintf("Setting up Listener\n");

    pthread_t cmd;
    pthread_create(&cmd, NULL, srvr_cmd, NULL);

    srvr_listen(server_sock, argc, argv);

} 

void srvr_listen(int server_sock, int argc, char *argv[]){  
    clt_inf* TEMP;
    unsigned int client_size = sizeof(struct sockaddr_in);
    int error = 0;
    int clts = 0;
    re: ;
    for(;;){

        TEMP = malloc(sizeof(clt_inf));
        (TEMP -> addr ) = NULL;
        (TEMP -> addr) = malloc(sizeof(struct sockaddr_in));


        if(((TEMP -> sock) = accept(server_sock, (struct sockaddr *) &(TEMP -> addr), &client_size)) < 0){
            perror("Accept() ");
            if(error < 20){
                error++;
                goto re;
            }else
                exit(1);
        }

        tprintf("Accepted client %d, on socket %d\n", clts, (TEMP -> sock));
        if(clts){
            // When accepted
            clts ++;
        }else{
            close( (TEMP -> sock) );
            free(*TEMP);
        }
    }
}



void* srvr_cmd(void* _args){
    e:;
    char cmd[10];
    scanf("%s",cmd);
    debug_clt_list();
    goto e;
}

