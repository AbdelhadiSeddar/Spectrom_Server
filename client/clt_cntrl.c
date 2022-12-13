#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <netdb.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>


#include "clt_cmd.h"
#include "clt_defs.h"
#include "../misc.h"

void* clt_handling(void* client_){
    clt_inf clt = *(clt_inf*)client_;
    free( (clt_inf*)client_);


    clt_lnk client; 
    clt_add(clt, &client);

    CONF:;
    send((client -> Client.sock), CMD_CONN_CONF, 4, 0);
    /// Recive GUID
    pthread_mutex_lock(&(client -> MUTEX));
    send((client -> Client.sock), CMD_CLT_SND_GUID, 4,0);
    recv((client -> Client.sock), (client -> Client.GUID), 4, 0);

    CONN_METHOD:
    send((client -> Client.sock), CMD_CONN_CONF, 4, 0);
    char RCV_CMD[4];
    recv((client -> Client.sock), RCV_CMD, 4,0);

    if(!strcmp(RCV_CMD, CMD_CLT_RCV_LOGI))
        // FUNCTION FOR LOGIN
        printf("Yikes");
    else if (!strcmp(RCV_CMD, CMD_CLT_RCV_REGS)){
        // FUNCTION FOR REGISTER
        goto CONN_METHOD;

    };
    



    return NULL;
}

int CLT_CNTRL_LOGI(clt_lnk* client){
    
    return 0;
}

int CLT_CNTRL_REGS(clt_lnk* client){
    
    return 0;
}

int CLT_CNTRL_LOGO(clt_lnk* client){
    return 0;
}




