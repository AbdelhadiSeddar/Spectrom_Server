#include "_Imports.h"

void Exec_ArgResolv(int argc, char **argv)
{
    char out[1024];
    for (int i = 0; i < argc; i++)
    {
        sprintf(out, "Argc %d  { } Argv %s", i, argv[i]);
        cnsle_print_sys(out);
        if (!strcmp(argv[i], "--nofg"))
            __SCRN_OFF();
    }
}

int main(int argc, char **argv)
{
    cnsle_inis();

    pthread_mutex_init(&(__SCRN_MUTEX), NULL);
    Exec_ArgResolv(argc, argv);

    srvr_load(argc, argv);

    char _SCRN;
    size_t _Len = 32;
re:;
    if(!__SCRN_STATUS)
        _SCRN = getchar();
        
    __SCRN_ON();
    srvr_cmd();
    goto re;
    return 0;
}
