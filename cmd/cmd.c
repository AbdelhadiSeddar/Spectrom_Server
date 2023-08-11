#include "../_Imports.h"

CMD_ARGS *CMD;

void __reset_CMD()
{
    if (CMD != NULL)
        free(CMD);

    CMD = malloc(sizeof(CMD_ARGS));
    CMD->n_args = 0;
}

int curs, tot;
char *cmd;

void srvr_cmd()
{
    scrn_inis();

e:;
    create_win_cmd();
    cmd = malloc(1024 * sizeof(char));
    __reset_CMD();
    curs = 6, tot = 6;
    char ch;

    wmove(COMMAND_WIN, 3, curs);
    refresh();
    while (1)
    {
        if (__POPUP_STATUS)
            ShowPopup();

        ch = wgetch(COMMAND_WIN);
        wrefresh(COMMAND_WIN);
        if(!IsValidChar(ch))
        {
            curs--;
            break;
        }
        if (ch == KEY_L)
            wmove(COMMAND_WIN, 3, (curs > 6 ? (curs -= 1) : (curs = 6)));
        else if (ch == KEY_R)
            wmove(COMMAND_WIN, 3, (curs != tot ? (curs += 1) : (curs = tot)));
        else if (ch == KEY_ENTR)
            break;
        else if (ch == KEY_DEL)
        {
            // Upcoming
        }
        else if (ch == KEY_F12)
        {
            strcpy(CMD->CMD, "help");
            goto cm;
        }
        else if (IsInAllowedChars((ch)))
        {
            mvwprintw(COMMAND_WIN, 3, curs, "%c", ch);
            cmd[curs - 6] = ch;

            curs++;
            tot += (tot <= curs ? 1 : 0);
        }
        if (__POPUP_STATUS)
            HidePopup();

        wrefresh(COMMAND_WIN);
        refresh();
    }
    AddNUllChar(cmd);
    GetCMD_s(cmd);
cm:;
    ResolveCMD();
    // if (CMD != NULL) /* Debugging */
    //    ShowCMD();
    free(cmd);
    goto e;
}

void GetCMD_s(char *Origin)
{
    unsigned int pos;
    char *indx = strchr(Origin, ' ');
    if (indx == NULL)
        strcpy(CMD->CMD, Origin);
    else
    {
        strncpy(CMD->CMD, Origin, (pos = (int)(indx - Origin)));
        CMD->CMD[pos] = '\0';
    }

    if (indx != NULL ? (strlen(Origin)) > strlen((char *)(indx + 1)) : 0)
    {
        strcpy((CMD->args), (char *)(indx - 1));
        GetArgs_s();
    }
    return;
}

void GetArgs_s()
{

    int s = 256, i = 0;
    unsigned int pos;
    char *indx;

    (CMD->n_args) = 0;
    while (i < 10)
    {
        indx = strchr(CMD->args, ' ');
        CMD->v_args[i] = malloc(s * sizeof(char));
        if (indx == NULL)
        {
            strcpy(CMD->v_args[i], CMD->args);
            break;
        }
        (CMD->n_args)++;

        strncpy(CMD->v_args[i], CMD->args, (pos = (int)(indx - CMD->args)));
        CMD->v_args[i][pos] = '\0';

        strcpy(CMD->args, (char *)(indx + 1));
    }
    if (i < 10)
        i++;
    else
        return;
}

void ResolveCMD()
{
    if ((CMD->CMD) == NULL || CMD->CMD[0] == '\0')
    {
        DefineError(__POPUP_ERR_CODE_EMPT);
        return;
    }

    if (!strcmp((CMD->CMD), "clear") || !strcmp((CMD->CMD), "cls"))
    {
        cmd_clear();
        DefineInfo(__POPUP_INFO_CODE_CLEARED);
    }
    else if (!strcmp((CMD->CMD), "exit") || !strcmp((CMD->CMD), "shutdown") || !strcmp((CMD->CMD), "stop"))
        cmd_exit_app();
    else if (!strcmp((CMD->CMD), "console") || !strcmp((CMD->CMD), "cnsle"))
        cnsle();
    else if (!strcmp((CMD->CMD), "help") || !strcmp((CMD->CMD), "?"))
        cmd_help();
    else
        DefineError(__POPUP_ERR_CODE_INVALID);

    cmd_clear();
}

void cmd_clear()
{
    clear();
    delwin(COMMAND_WIN);
    delwin(S_COMMAND_WIN);
    ShowInf();
    refresh();
    // DefineInfo(__POPUP_INFO_CODE_CLEARED);
}

void ShowCMD()
{
    int nulll = 0;
    for (int i = 0; cmd[i] != '\0'; i++)
        nulll++;
    mvprintw(3, 2, "Full Command: %s [ Curs %d Tot %d NULL at %d and %u  Valid : %d]\n", cmd, curs -6 +1, tot, nulll, cmd[1], IsValidChar(cmd[1]) );
    mvprintw(4, 2, "Command: %s (%d)\n", (CMD->CMD), strlen(CMD->CMD));
    refresh();
    mvprintw(5, 2, "N Args : %d\n", (CMD->n_args));
    refresh();
    for (int i = 0; i < (CMD->n_args); i++)
    {
        mvprintw(6 + i, 2, "Arg%d: - %s\n", i, (CMD->v_args[i]));
    }
}

void cmd_exit_app()
{
    cnsle_print_sys("Writing log");
    cnsle_print_sys("Shutting Down Application");
    debug_sys_cnsle_log();
    endwin();
    exit(0);
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
