#include "../_Imports.h"

char *__PATH_LOG;

void debug_clt_list()
{
    FILE *f;

    f = fopen("/ftp/dev/clients/clt_sout", "w+");

    fclose(f);
}
void __debug_cnsle_log()
{
    FILE *f;

    if ((f = fopen(__PATH_LOG, "w+")) == NULL)
    {
        DefineError(__POPUP_ERR_CODE_INVALID_PATH);
        return;
    }

    CNSLE_LINE line = _CONSOLE_LINES;
    while (line != NULL)
    {
        fprintf(f, "[%s] %s ~$ %s\n", line->time, line->origin, line->val);
        line = line->NXT;
    }

    fclose(f);
    DefineInfo(__POPUP_INFO_CODE_LOGWRITTEN, __PATH_LOG);
}

void debug_cnsle_log_c(int __TYPE)
{
    __PATH_LOG = calloc(1024, sizeof(char));
    switch (__TYPE)
    {
    case __CNSLE_LOG_CMD:
        if (CMD->n_args >= 2 && strcmp("log", CMD->v_args[0]))
            DefineError(__POPUP_ERR_CODE_INVALID_ARG);

        if (CMD->n_args == 2 && CMD->v_args[1] != NULL && (!strcmp(CMD->v_args[1], " ") || !strcmp(CMD->v_args[1], "")))
            sprintf(__PATH_LOG, "%s", _PATH_LOG);
        else if (CMD->n_args == 1)
            sprintf(__PATH_LOG, "%s", _PATH_LOG);
        else
            sprintf(__PATH_LOG, "%s", (CMD->v_args[1]));

        break;
    case __CNSLE_LOG_SYS:
        sprintf(__PATH_LOG, _PATH_LOG);
        break;

    default:
        break;
    }

    __debug_cnsle_log();
}
