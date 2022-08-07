#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <netdb.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#include "../client/clt_defs.h"
#include "../misc.h"
// To be fixed
/*
char* GETIP(){
    struct addrinfo *dns;
    if (!getaddrinfo("site.spectrom.ro.lt","9114", NULL,&(dns))){
        tprintf("FATAL ERROR : Not Parsed");
        return NULL;
    }
    for( struct addrinfo res = dns; res != NULL ; res = res -> ai_next){
        if(!getnameinfo(res ->  ai_addr, ))
    
    }
}*/


void clt_handling(clt_lnk client){
    char GUID[37];
    if(recv((client -> Client.sock), (client ->Client.GUID), 37, 0) < 0){
        printf("UUID not recived");
        exit(1);
    }
    //Do wat you want

    
}
