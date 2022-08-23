#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <assert.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include "inis.h"
#include "../client/clt_defs.h"
#include "../debug/debug.h"


void srvr_load(int argc, char *argv[]){
    
    printf("Declaring Locals\n");
    int server_sock;
    struct sockaddr_in server_addr;
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

    printf("Setting the Socket (%d) as listen with 100 MAX oon Queue\n", server_sock);
    sleep(1);
    if(listen(server_sock, 100) < 0){
        perror("Listen()");
        exit(1);
    }
    
    printf("Setting up Listener\n");
    srvr_listen(server_sock, argc, argv);

}

void srvr_listen(int server_sock, int argc, char *argv[]){
    clt_lnk client;    
    clt_inf c;
    unsigned int client_size = sizeof(c.addr);
    int error = 0;
    int clts = 0;
    re: ;

    for(;;){
        client = malloc(sizeof(client));
        (client -> Client.thread_id) = malloc(sizeof((client -> Client.thread_id)));
        (client -> Client.addr) = malloc(sizeof((client -> Client.addr)));
        if((client-> Client.sock = accept(server_sock, (struct sockaddr *) &(client->Client.addr), &client_size)) < 0){
            perror("Accept() ");
            if(error < 20){
                error++;
                goto re;
            }else
                exit(1);
        }
        pthread_create((client -> Client.thread_id), NULL, srvr_clt_handling, &client);
        clts++;
        if(clts == 5)
            debug_clt_list();
    }
}
void* srvr_cmd(void* _args){
    return NULL;
}

void* srvr_clt_handling(void* clt){
    clt_lnk client = *(clt_lnk*)clt;
    char path[53];
    strcpy(path, PATH_TO_STORE_CLIENTS);
    if((send(client->Client.sock, "1", sizeof("1"), 0)) < 0){
            perror("Sending Error");
            exit(1);
        }
        
    send(client->Client.sock, "00X", sizeof("00X"), 0);
    recv(client->Client.sock, client->Client.GUID,37,0);
    strcat(path, client->Client.GUID);
    if(!((client -> Client.file) = fopen(path, "w+"))){
        close(client->Client.sock);
        return NULL;
    }

    fprintf((client -> Client.file), "Guid:\t%s\nSocket:\t%d\nAddr:\n\tip:\t%i",client->Client.GUID, client->Client.sock,client->Client.addr -> sin_addr.s_addr);
    fclose((client -> Client.file));

    send(client -> Client.sock, "LLL", sizeof("LLL"),0);
    close(client->Client.sock);
    close(*(client->Client.thread_id));
    return NULL;
}