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
#include "../debug/debug.h"


void srvr_load(int argc, char *argv[]){
    printf("Starting Time is "); tprintf("");
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
    clt_lnk client = NULL;    
    clt_inf c;
    pthread_t cmd;
    unsigned int client_size = sizeof(c.addr);
    int error = 0;
    int clts = 0;
    re: ;
    pthread_create(&cmd, NULL, srvr_cmd, NULL);
    for(;;){
        client = malloc(sizeof(*client));
            client -> Client.file = malloc(sizeof(*(client -> Client.file)));
            client -> Client.thread_id = NULL;
            client -> Client.addr = NULL;

        client -> prev = CURRENT_CLIENT;
        client -> next = NULL;

        (client -> Client.thread_id) = malloc(sizeof((client -> Client.thread_id)));
        (client -> Client.addr) = malloc(sizeof((client -> Client.addr)));
        if(((client-> Client.sock) = accept(server_sock, (struct sockaddr *) &(client->Client.addr), &client_size)) < 0){
            perror("Accept() ");
            if(error < 20){
                error++;
                goto re;
            }else
                exit(1);
        }

        CURRENT_CLIENT -> next = client;
        CURRENT_CLIENT = client;
        CURRENT_CLIENT -> INDEX = CURRENT_INDEX++;

        printf("Accepted client %d, on socket %d\n", clts, (client -> Client.sock));
        if(clts)
            pthread_create((client -> Client.thread_id), NULL, srvr_clt_handling, &client);
        else{
            close( (client -> Client.sock) );
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

void* srvr_clt_handling(void* clt){
    clt_lnk client = *(clt_lnk*)clt;
    char path[54];
    strcpy(path, PATH_TO_STORE_CLIENTS);
    
    send((client-> Client.sock), "1", sizeof("1"), 0);
    send((client->Client.sock), "00X", sizeof("00X"), 0);
    recv((client->Client.sock), (client->Client.GUID),sizeof((client->Client.GUID)),0);
    strcat(path, (client->Client.GUID));
    if(!( (client -> Client.file) = fopen(path, "w+") ) ){
        close(client->Client.sock);
        perror("Write()");
        exit(1);
    }

    fprintf((client -> Client.file), "Guid:\t%s\nSocket:\t%d\nAddr:\n", (client->Client.GUID), (client->Client.sock));
    fclose((client -> Client.file));

    send((client -> Client.sock), "LLL", sizeof("LLL"),0);
    close((client->Client.sock));
    return NULL;
}