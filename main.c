#include "_Imports.h"

int main(int argc, char *argv[])
{
    cnsle_inis();

    srvr_load(argc, argv);
    srvr_cmd();
    return 0;
}
