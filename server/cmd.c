#include "../_Imports.h"

CMD_ARGS *CMD;

void srvr_cmd()
{
    scrn_inis();
    // sleep(2);

e:;
    create_win_cmd();
    CMD = malloc(sizeof(CMD_ARGS));
    CMD->args = malloc(1024 * sizeof(char));

    char cmd[1024] = "";
    char tmp[1024], tst[1024];
    int curs = 6, tot = 6;
    char ch;
    /*attrset(COLOR_PAIR(R_GRN));
    printw("$ ");
    attrset(COLOR_PAIR(R_BLK));*/

    wmove(COMMAND_WIN, 3, curs);
    refresh();
    while (1)
    {
        ch = wgetch(COMMAND_WIN);
        sprintf(tst, "curs : %d | tot : %d | last char %c %d", curs, tot, ch, ch);
        mvwprintw(COMMAND_WIN, 2, (54 - strlen(tst)) / 2, tst);
        wrefresh(COMMAND_WIN);
        if (ch == KEY_L)
            wmove(COMMAND_WIN, 3, (curs > 6 ? (curs -= 1) : (curs = 6)));
        else if (ch == KEY_R)
            wmove(COMMAND_WIN, 3, (curs != tot ? (curs += 1) : (curs = tot)));
        else if (ch == KEY_ENTR)
            break;
        else if (ch == KEY_DEL || ch == KEY_BACKSPACE || ch == 127 || ch == '\b')
        {
            // F*** it i'll come back
        }
        else if (ch == KEY_F12)
        {
            strcpy(cmd, "help");
            break;
        }
        else if (IsInAllowedChars((ch)))
        {
            mvwprintw(COMMAND_WIN, 3, curs, "%c", ch);
            cmd[curs - 6] = ch;
            if ((curs - 6) == strlen(cmd))
                cmd[curs - 6 + 1] = '\0';

            curs++;
            tot += (tot <= curs ? 1 : 0);
        }
        wrefresh(COMMAND_WIN);
    }
    // wgetstr(COMMAND_WIN, cmd);
    GetCMD_s(cmd);

    ResolveCMD();
    goto e;
}

void GetCMD_s(char *Origin)
{
    long unsigned int pos;
    //    r_newline(Origin);
    strncpy(CMD->CMD, Origin, (pos = strcspn(Origin, " ")));
    if ((strlen(Origin)) > pos)
    {
        strcpy((CMD->args), Origin + pos + 1);
        GetArgs_s();
    }
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
        CMD->v_args[i] = malloc(256 * sizeof(char));

        if ((pos = strcspn((CMD->args), " ")))
            strncpy(CMD->v_args[i], CMD->args, pos);

        if ((strlen(CMD->args)) == pos)
            i = 10;

        (CMD->n_args)++;
        ((CMD->args = strchr((CMD->args), ' ') + 1) != NULL) ? i++ : ((CMD->args = strchr((CMD->args), '\0')) == NULL ? checkerr(-1, "Error While Parsing Arguments") : br++);
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
        tprintw("Null or Empty Command");
        return;
    }

    if (!strcmp((CMD->CMD), "clear") || !strcmp((CMD->CMD), "cls"))
    {
        cmd_clear();
    }
    else if (!strcmp((CMD->CMD), "exit") || !strcmp((CMD->CMD), "shutdown") || !strcmp((CMD->CMD), "stop"))
    {
        cmd_exit_app();
    }
    else if (!strcmp((CMD->CMD), "help") || !strcmp((CMD->CMD), "?"))
    {
        cmd_help();
    }

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
    printw(" Command: %s\n", (CMD->CMD));
    refresh();
    printw(" Args : %s\n", (CMD->args));
    refresh();
    for (int i = 0; i < (CMD->n_args); i++)
    {
        tprint();
        printw("\t\t\t - %s\n", (CMD->v_args[i]));
    }
}

void cmd_exit_app()
{
    tcprintw("Shutting Down Application");
    endwin();
    exit(0);
}

void cmd_help()
{
    clear();
    refresh();
    if (ArgsAreNull())
    {
        TARG_X = (MAX_X - 45) / 2;
        TARG_Y = (MAX_Y - 12) / 2;

        create_win_target(12, 45, "[ Help ]", BTN_OK);

        mvwprintw(TARGET_WIN, 2, 2, "- [ clear ] :  Clears Console ");
        mvwprintw(TARGET_WIN, 3, 2, "- [ help ] :  Show this menu ");
        mvwprintw(TARGET_WIN, 4, 2, "- [ exit ] :  Exit this application ");

        mvwprintw(TARGET_WIN, 6, 2, " help <command> : To Show the help ");
        mvwprintw(TARGET_WIN, 7, 4, " for the command");
        mvwprintw(TARGET_WIN, 8, 2, "\teg: $ help help");
    }
    else
    {
        TARG_X = (MAX_X - 54) / 2;
        TARG_Y = (MAX_Y - 10) / 2;
        create_win_target(10, 54, "[ Help ]", BTN_OK);
        wattron(TARGET_WIN, COLOR_PAIR(R_BLU) | A_BOLD);
        mvwprintw(TARGET_WIN, 2, (54 - strlen(" Command : ") - strlen(CMD->v_args[0]))/2, " Command : ");
        wattroff(TARGET_WIN, COLOR_PAIR(R_BLU) | A_BOLD);
        if (!strcmp((CMD->v_args[0]), "clear") || !strcmp((CMD->v_args[0]), "cls"))
        {
            wprintw(TARGET_WIN, "\"%s\"", CMD->v_args[0]);
            mvwprintw(TARGET_WIN, 4, 2, "- %s : Exits the application", CMD->v_args[0]);

            mvwprintw(TARGET_WIN, 7, 2, "Aliases:%s%s\n", (!strcmp(CMD->v_args[0], "clear") ? "" : " clear"), (!strcmp(CMD->v_args[0], "cls") ? "" : " cls"));
        }
        else if (!strcmp(CMD->v_args[0], "help") || !strcmp((CMD->v_args[0]), "?"))
        {
            wprintw(TARGET_WIN, "\"%s\"",CMD->v_args[0]);
            mvwprintw(TARGET_WIN, 3, 2, "- help : Shows all available commands.");
            mvwprintw(TARGET_WIN, 4, 2, "- help <command> : Shows how to use <commands>.");
            mvwprintw(TARGET_WIN, 5, 2, "\teg: $ help help");

            mvwprintw(TARGET_WIN, 7, 2, "Aliases:%s%s", (!strcmp(CMD->v_args[0], "help") ? "" : " help"), (!strcmp(CMD->v_args[0], "?") ? "" : " ?"));
        }
        else if (!strcmp((CMD->v_args[0]), "exit") || !strcmp((CMD->v_args[0]), "shutdown") || !strcmp((CMD->v_args[0]), "stop"))
            cmd_help_exit_app();
        else
        {
            mvwprintw(TARGET_WIN, 5, (54 - 15 - strlen(CMD->v_args[0]))/2, "No help for \"%s\"", CMD ->v_args[0]);
        }
    }
    refresh();
    wrefresh(TARGET_WIN);
    char r;
    noecho();
    while (1)
    {
        r = getch();
        if (r == '\n')
            break;
    }
    echo();
}

void cmd_help_exit_app()
{
    wprintw(TARGET_WIN, "\"%s\"", CMD->v_args[0]);
    mvwprintw(TARGET_WIN, 4, 2, "- %s : Exits the application\n", CMD->v_args[0]);

    mvwprintw(TARGET_WIN, 7, 2, "Aliases:%s%s%s\n", (!strcmp(CMD->v_args[0], "exit") ? "" : " exit"), (!strcmp(CMD->v_args[0], "stop") ? "" : " stop"), (!strcmp(CMD->v_args[0], "shutdown") ? "" : " shutdown"));
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
