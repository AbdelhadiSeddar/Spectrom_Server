#include "../_Imports.h"

void debug_clt_list()
{
    FILE *f;

    f = fopen("/ftp/dev/clients/clt_sout", "w+");

    fclose(f);
}
