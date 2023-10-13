#include "../_Imports.h"

int nulll = 0;
CMD_ARGS *CMD;

void __reset_CMD()
{
    if (CMD != NULL)
    {
        for (int i = 0; i < CMD->n_args; i++)
            free(CMD->v_args[i]);
        free(CMD);
    }
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
    __reset_CMD();
    cmd = malloc(1024 * sizeof(char));
    curs = 6, tot = 6;
    char ch;

    wmove(COMMAND_WIN, 3, curs);
    refresh();
    while (1)
    {
        if (__POPUP_STATUS)
            ShowPopup();
        ch = getch();

        wrefresh(COMMAND_WIN);
        if (!IsValidChar(ch))
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
    cmd[curs - 6] = (char)0;
    nulll = curs - 6;
    GetCMD_s(cmd);
cm:;
    ResolveCMD();
    //if (CMD != NULL) /* Show Command info for debugging*/
    //    ShowCMD();
    free(cmd);
    if (__SCRN_STATUS)
        goto e;
    else
    {
        endwin();
        return;
    }
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
        strcpy((CMD->args), (char *)(indx + 1));
        GetArgs_s();
    }
    return;
}

void GetArgs_s()
{

    int s = 256, i = 0;
    unsigned int pos;
    char *args = CMD->args;
    char *indx;

    (CMD->n_args) = 0;
    while (i < 10)
    {
        indx = strchr(args, ' ');
        CMD->v_args[i] = calloc(s, sizeof(char));
        (CMD->n_args)++;
        if (indx == NULL)
        {
            strcpy(CMD->v_args[i], args);
            break;
        }

        strncpy(CMD->v_args[i], args, (pos = (int)(indx - args)));
        CMD->v_args[i][pos] = '\0';

        args = (char *)(indx + 1);
        i++;
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

    for (int cmd = 0; cmd < _n_CMDS; cmd++)
        for (int alia = 0; alia < _HELP_CMDS[cmd].n_aliases; alia++)
            if (!strcmp((CMD->CMD), _HELP_CMDS[cmd].aliases[alia]))
            {
                _HELP_CMDS_f(cmd);
                goto EndResolve;
            }
    DefineError(__POPUP_ERR_CODE_INVALID);
EndResolve:;
    cmd_clear();
}

void cmd_clear()
{
    clear();
    delwin(COMMAND_WIN);
    delwin(S_COMMAND_WIN);
    ShowInf();
    refresh();
}

void ShowCMD()
{
    int Strlen = strlen(cmd);
    for (int i = 0; i < Strlen; i++)
    {

        mvprintw(2, 2 + i * 10, "%c %u [] ", cmd[i], cmd[i]);
    }
    mvprintw(3, 2, "Full Command: %s [ Curs %d Tot %d NULL at %d and %u  Valid : %d]", cmd, curs - 6 + 1, tot - 6 + 1, nulll, cmd[nulll], IsValidChar(cmd[nulll]));
    mvprintw(4, 2, "Command: %s (%lu)", (CMD->CMD), strlen(CMD->CMD));
    refresh();
    mvprintw(5, 2, "Args : %s", (CMD->args));
    mvprintw(6, 2, "N Args : %d", (CMD->n_args));
    refresh();
    for (int i = 0; i < (CMD->n_args); i++)
    {
        mvprintw(7 + i, 2, "Arg%d: - %s", i, (CMD->v_args[i]));
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
