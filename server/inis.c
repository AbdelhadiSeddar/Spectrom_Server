#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <assert.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#include "inis.h"
#include "../client/clt_defs.h"

#define PATH_TO_STORE_CLIENTS "/mnt/c/clients/"

void srvr_load(){
    printf("Declaring Locals\n");
    int server_sock;
    struct sockaddr_in server_addr;

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

    printf("Setting the Socket (%d) as listen with 100 MAX oon Queue\n", server_sock);
    sleep(1);
    if(listen(server_sock, 100) < 0){
        perror("Listen()");
        exit(1);
    }
    
    printf("Setting up Listener");
    srvr_listen(server_sock);

}

void srvr_listen(int server_sock){
    clt_inf client;
    unsigned int client_size = sizeof(client.addr);
    int error = 0;
    re:
    for(;;){
        
        if((client.sock = accept(server_sock, (struct sockaddr *) &client.addr, &client_size)) < 0){
            perror("Accept() ");
            if(error < 20)
                goto re;
            else
                exit(1);
        }
        pthread_t thread_id;
        int re = pthread_create(&thread_id, NULL, srvr_clt_handling, &client);
        assert(!re);
    }
}
void* srvr_cmd(void* _args){
    return NULL;
}

void* srvr_clt_handling(void* clt){
    clt_inf client = *(clt_inf*)clt;
    char path[53]; strcpy(path, PATH_TO_STORE_CLIENTS);
    if(send(client.sock, "1", sizeof("1"), 0) < 0){
            perror("Sending Error");
            exit(1);
        }
    printf("test");
    send(client.sock, "00X", sizeof("00X"), 0);
    recv(client.sock, client.GUID,37,0);

    FILE *fl;
    strcat(path, client.GUID);
    if(!(fl = fopen(path, "w"))){
        close(client.sock);
        return NULL;
    }

    fprintf(fl, "Guid:\t%s\nSocket:\t%d\nAddr:\n\tip:\t%i",client.GUID, client.sock,client.addr.sin_addr.s_addr);
    fclose(fl);
    send(client.sock, "LLL", sizeof("LLL"),0);
    close(client.sock);
    close(client.thread_id);
    return NULL;
}