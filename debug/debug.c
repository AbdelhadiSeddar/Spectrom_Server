#include "../_Imports.h"

void debug_clt_list()
{
    FILE *f;

    f = fopen("/ftp/dev/clients/clt_sout", "w+");

    clt_lnk clients = CURRENT_CLIENT;

    while (clients)
    {
        fprintf(f, "Client:");
        fprintf(f, "-> GUID:\t%s\n", (clients->Client.GUID));
        fprintf(f, "-> ID:\t%d\n", (clients->Client.ID));
        fprintf(f, "-> sock:\t%d\n", (clients->Client.sock));
        fprintf(f, "-> Index:\t%d\n", (clients->INDEX));
        clients = clients->next;
    }

    fclose(f);
}
