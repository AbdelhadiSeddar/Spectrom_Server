#include <stdlib.h>
#include <stdio.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "../client/clt_defs.h"

void debug_clt_list(){
    FILE *f;

    f = fopen("/mnt/c/debug/clt.sout","w");

    clt_lnk clients = NULL_CLIENT;

    while(clients){
        fprintf(f,"Client:");
        fprintf(f,"-> GUID:\t%s\n", (clients->Client.GUID));
        fprintf(f,"-> ID:\t%d\n", (clients->Client.ID));
        fprintf(f,"-> sock:\t%d\n", (clients->Client.sock));
        fprintf(f,"-> Index:\t%d\n", (clients-> INDEX));
    }


}


