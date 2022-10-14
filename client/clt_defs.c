#include "clt_defs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

clt_lnk CLT_LIST        = NULL;
clt_lnk NULL_CLIENT     = NULL;
clt_lnk CURRENT_CLIENT  = NULL;
int     CURRENT_INDEX   = -1;
int     INIS            = 0;

int clt_inis(){
    CURRENT_INDEX = 0;
    INIS = 1;
    NULL_CLIENT = malloc(sizeof(*NULL_CLIENT));
    strcpy((NULL_CLIENT -> Client.GUID), "00000000-0000-0000-0000-000000000000");
    int sock = 3;

    NULL_CLIENT -> next = NULL;
    NULL_CLIENT -> prev = NULL;
    CURRENT_CLIENT = NULL_CLIENT;
    return 0;
}

