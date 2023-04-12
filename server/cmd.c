#include "../_Imports.h"

CMD_ARGS *CMD;

void *srvr_cmd(void *_args)
{

    sleep(2);
    system("clear");
e:;
    CMD = malloc(sizeof(CMD_ARGS));
    CMD->CMD = malloc(1024 * sizeof(char));
    CMD->args = malloc(1024 * sizeof(char));

    long unsigned int size = 1024;
    char *cmd = malloc(size * sizeof(char));

    printf("%s$ %s", B_GRN, R_WHT);
    getline(&cmd, &size, stdin);
    GetCMD_s(cmd);

    ResulveCMD();
    goto e;
}

void GetCMD_s(char *Origin)
{
    long unsigned int pos;
    r_newline(Origin);
    strncpy(CMD->CMD, Origin, (pos = strcspn(Origin, " ")));

    CMD->args = strchr(Origin, ' ') + 1;

    GetArgs_s();
    return;
}

void GetArgs_s()
{

    int s = 256, i = 0;
    int br = 0;
    long unsigned int pos;

    (CMD->n_args) = 0;
    while (i < 10)
    {
        CMD->v_args[i] = malloc(s * sizeof(char));

        if ((CMD->args)[0] == '\0')
            break;
        if ((pos = strcspn((CMD->args), " ")))
            strncpy(CMD->v_args[i], CMD->args, pos);

        (CMD->n_args)++;
        ((CMD->args = strchr((CMD->args), ' ') + 1) != NULL) ? i++ : ((CMD->args = strchr((CMD->args), '\0')) == NULL ? checkerr(-1, "Error While Parsing Arguments") : br++);
    }
    if (i < 10)
        i++;
    else
        return;
}

void ResulveCMD()
{
    if ((CMD->CMD) == NULL || CMD->CMD[0] == '\0')
    {
        tprintf("Null or Empty Command");
        return;
    }

    if (!strcmp((CMD->CMD), "clear") || !strcmp((CMD->CMD), "cls"))
        system("clear");
    else if (!strcmp((CMD->CMD), "exit") || !strcmp((CMD->CMD), "shutdown") || !strcmp((CMD->CMD), "stop"))
    {
        cmd_exit_app();
    }
    else if (!strcmp((CMD->CMD), "help") || !strcmp((CMD->CMD), "?"))
    {
        cmd_help();
    }
}
void ShowCMD()
{
    tprint();
    printf(" Command: %s\n", (CMD->CMD));
    tprint();
    printf(" Args : \n");
    for (int i = 0; i < (CMD->n_args); i++)
    {
        tprint();
        printf("\t\t\t - %s\n", (CMD->v_args[i]));
    }
}

void cmd_exit_app()
{
    ChangeColor(R_RED);
    tcprintf("Shutting Down Application");
    ChangeColor(R_WHT);
    exit(0);
}

void cmd_help()
{

    ChangeColor(R_GRN);
    tcprintf("Showing Help:");
    ChangeColor(R_WHT);
    if (ArgsAreNull())
    {
        printf("- [ clear ] :  Clears Console \n");
        printf("- [ help ] :  Show this menu \n");
        printf("- [ exit ] :  Exit this application \n");
        printf("\n");

        printf(" help <command> : To Show the help for the command\n");
        printf("\t%seg: %s$ %shelp help\n", R_CYN, R_GRN, R_WHT);
    }
    else
    {
        printf("\t Command : ");
        if (!strcmp((CMD->v_args[0]), "clear") || !strcmp((CMD->v_args[0]), "cls"))
        {
            printf("\"%s\" :\n", CMD->v_args[0]);
            printf("- %s : Exists the apllication\n", CMD->v_args[0]);

            printf("\n");
            printf("%sAliases:%s%s%s\n", B_GRN, R_WHT, (!strcmp(CMD->v_args[0], "clear") ? "" : " clear"), (!strcmp(CMD->v_args[0], "cls") ? "" : " cls"));
        }
        else if (!strcmp(CMD->v_args[0], "help") || !strcmp((CMD->CMD), "?"))
        {
            printf("\"help\" :\n");
            printf("- help : Shows all available commands.\n");
            printf("- help <command> : Shows how to use <commands>.\n");
            printf("\t%seg: %s$ %shelp help\n", R_CYN, R_GRN, R_WHT);

            printf("\n");
            printf("%sAliases:%s ?\n", B_GRN, R_WHT);
        }
        else if (!strcmp((CMD->v_args[0]), "exit") || !strcmp((CMD->v_args[0]), "shutdown") || !strcmp((CMD->v_args[0]), "stop"))
            cmd_help_exit_app();
        else
        {
            printf("Invalid Command\n");
        }
    }
    ChangeColor(R_GRN);
    tcprintf("Help End.");
}

void cmd_help_exit_app()
{
    printf("\"%s\" :\n", CMD->v_args[0]);
    printf("- %s : Exists the apllication\n", CMD->v_args[0]);

    printf("\n");
    printf("%sAliases:%s%s%s%s\n", B_GRN, R_WHT, (!strcmp(CMD->v_args[0], "exit") ? "" : " exit"), (!strcmp(CMD->v_args[0], "stop") ? "" : " stop"), (!strcmp(CMD->v_args[0], "shutdown") ? "" : " shutdown"));
}

void get(char *args)
{
}

int ArgsAreNull()
{
    if (CMD->n_args == 0)
        return 1;

    for (int i = 0; i < CMD->n_args; i++)
        if (strcmp(CMD->v_args[i], " ") || strcmp(CMD->v_args[i], ""))
            return 0;

    return 1;
}
