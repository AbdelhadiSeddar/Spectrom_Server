#include "server/*.h"
#include "clt_defs.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int clt_inis(){
    if(!NULL_CLIENT && !INIS){
        CURRENT_INDEX = 1;
        INIS = 1;
        strcpy((NULL_CLIENT -> Client.GUID), "00000000-0000-0000-0000-000000000000")
        int sock = 3;

        NULL_CLIENT -> next = NULL;
        NULL_CLIENT -> prev = NULL;
        CURRENT_CLIENT = NULL_CLIENT;
        return 0;
    }else{
        NULL_CLIENT = NULL;
        INIS = 0;
        return -1;
    }
}

int clt_add(int sock, char* UUID, int ID, clt_lnk New_Client){
    New_Client = malloc(sizeof(CLIENT));
    New_Client -> Client.sock = sock;
    New_Client -> Client.ID = ID;
    New_Client -> INDEX = CURRENT_INDEX++;

    strcpy((New_Client -> Client.GUID), UUID);

    CURRENT_CLIENT -> next = New_Client;
    New_Client -> prev = CURRENT_CLIENT;

    CURRENT_CLIENT = CURRENT_CLIENT -> next;
    return (New_Client ->INDEX);
}
