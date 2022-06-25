#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>


#include "misc.h"
#include "client/clt_defs.h"
#include "Connections/cnx.h"

#define PORT 9114

int main () {
    tprintf("Turning Server On.");
    tprintf("Accpting Single Client");
    int server_sock,client_sock;
    unsigned int client_size;

    struct sockaddr_in server_addr, client_addr;

    socklen_t addr_leng;
    char smBuffer[4];
    if((server_sock = socket(AF_INET, SOCK_STREAM, 0)) < 0){
        teprintf("Socket Error");
        exit(1);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    // Binding the server

    if(bind(server_sock, (struct sockaddr*) &server_addr, sizeof(server_addr)) < 0 ){
        teprintf("Binding Error");
        exit(1);
    }
    tprintf("Binded Port 9114");

    if (listen(server_sock, 10) < 0){
        teprintf("Listening Error");
        exit(1);
    }

    if(clt_inis(NULL_CLIENT) < 0 ){
        teprintf("Links initialisation Error");
        exit(1);
    }

    CURRENT_CLIENT = NULL_CLIENT;
    restart:
    for(;;){
        CURRENT_CLIENT ->next = (clt_lnk) malloc(sizeof(CURRENT_CLIENT));
        CURRENT_CLIENT ->next ->prev = CURRENT_CLIENT;
        CURRENT_CLIENT = CURRENT_CLIENT ->next;


        client_sock = accept(server_sock, (struct sockaddr*) &client_addr, &client_size);
        //sending
        if(send(client_sock, "1", sizeof("1"), 0) < 0){
            teprintf("Sending Error");
            exit(1);
        }

        if((CURRENT_INDEX = clt_add(client_sock, NULL, -1, CURRENT_CLIENT)) < 0) {
            teprintf("Could not add Client");
            goto restart;
        }

        pthread_create(&(CURRENT_CLIENT ->thread_id), NULL,  clt_handling, CURRENT_CLIENT);
    }
    ;

    close(server_sock);

    
    return 0;
}
