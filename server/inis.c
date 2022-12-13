#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <assert.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "inis.h"
#include "../main_defs.h"
#include "../misc.h"
#include "../client/clt_defs.h"
#include "../client/clt_cntrl.h"
#include "../debug/debug.h"


void srvr_load(int argc, char *argv[]){
    printf("Starting Time is "); tprintf("");
    printf("Declaring Locals\n");
    int server_sock;
    struct sockaddr_in server_addr;
    printf("Initializing Mutexes\n");

    if (pthread_mutex_init(&CURRENT_INFO_MUTEX, NULL) != 0) {
        perror("\n mutex init has failed\n");
        exit(1);
    }


    printf("Inisialising the List\n");
    clt_inis();
    printf("Inisialized\n");
    printf("Creating Socket\n");
    sleep(1);
    if((server_sock = socket(AF_INET, SOCK_STREAM, 0)) < 0){
        perror("Socket()");
        exit(1);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    printf("Socket Created\n");
    sleep(1);
    printf("Binding Socket\n");
    sleep(1);

    if(bind(server_sock, (struct sockaddr *) &server_addr, sizeof(server_addr)) < 0 ){
        perror("Bind()");
        exit(1);
    }

    printf("Binded\n");
    sleep(1);

    printf("Setting up Socket (%d) to listen\n", server_sock);
    printf("Socket Queue is %s", (MAX_QUEUE != 0) ? "Set to ": "Not Set\n");
    if(MAX_QUEUE)
        printf("%d allowed connections pending\n", MAX_QUEUE);
    
    sleep(1);
    if(listen(server_sock, 100) < 0){
        perror("Listen()");
        exit(1);
    }
    
    printf("Setting up Listener\n");
    srvr_listen(server_sock, argc, argv);

} 

void srvr_listen(int server_sock, int argc, char *argv[]){  
    clt_inf* TEMP;
    pthread_t cmd;
    unsigned int client_size = sizeof(TEMP -> addr);
    int error = 0;
    int clts = 0;
    re: ;
    pthread_create(&cmd, NULL, srvr_cmd, NULL);
    for(;;){


        TEMP = malloc(sizeof(TEMP));
        (TEMP -> thread_id) = NULL;
        (TEMP -> addr ) = NULL;

        (TEMP -> thread_id )= malloc(sizeof((TEMP -> thread_id)));
        (TEMP -> addr) = malloc(sizeof((TEMP -> addr)));


        if(((TEMP -> sock) = accept(server_sock, (struct sockaddr *) &(TEMP -> addr), &client_size)) < 0){
            perror("Accept() ");
            if(error < 20){
                error++;
                goto re;
            }else
                exit(1);
        }

        printf("Accepted client %d, on socket %d\n", clts, (TEMP -> sock));
        if(clts){
            pthread_create((TEMP -> thread_id), NULL, clt_handling, (void *) TEMP);
        }else{
            close( (TEMP -> sock) );
            free(TEMP);
            clts ++;
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

