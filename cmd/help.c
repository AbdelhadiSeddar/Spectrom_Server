#include "../_Imports.h"

int height, width;
int n_HELP_CMDS = 0;
char *re;
__HELP_INFO *_HELP_CMDS;

void _DEFINE_HELP()
{
    n_HELP_CMDS = 6;
    _HELP_CMDS = calloc(n_HELP_CMDS, sizeof(__HELP_INFO));

    // CLEAR
    strcpy(_HELP_CMDS[0].title, "Clear");
    _HELP_CMDS[0].n_formats = 1;
    strcpy(_HELP_CMDS[0].format[0], "");
    strcpy(_HELP_CMDS[0].format_INFO[0], "Clears the Console");
    _HELP_CMDS[0].n_aliases = 2;
    strcpy(_HELP_CMDS[0].aliases[0], "clear");
    strcpy(_HELP_CMDS[0].aliases[1], "cls");

    // Help
    strcpy(_HELP_CMDS[1].title, "Help");
    _HELP_CMDS[1].n_formats = 2;
    strcpy(_HELP_CMDS[1].format[0], "");
    strcpy(_HELP_CMDS[1].format_INFO[0], "Shows this menu");
    strcpy(_HELP_CMDS[1].format[1], "<Command>");
    strcpy(_HELP_CMDS[1].format_INFO[1], "Shows help for a certain Command");
    _HELP_CMDS[1].n_aliases = 2;
    strcpy(_HELP_CMDS[1].aliases[0], "help");
    strcpy(_HELP_CMDS[1].aliases[1], "?");

    // // Console
    strcpy(_HELP_CMDS[2].title, "Console");
    _HELP_CMDS[2].n_formats = 2;
    strcpy(_HELP_CMDS[2].format[0], "");
    strcpy(_HELP_CMDS[2].format_INFO[0], "Shows The console window");
    strcpy(_HELP_CMDS[2].format[1], "log [Optional: <PATH>]");
    strcpy(_HELP_CMDS[2].format_INFO[1], "Saves the console in a log file ( default path _PATH_LOG )");
    _HELP_CMDS[2].n_aliases = 2;
    strcpy(_HELP_CMDS[2].aliases[0], "console");
    strcpy(_HELP_CMDS[2].aliases[1], "cnsle");

    // EXIT
    strcpy(_HELP_CMDS[3].title, "Exit");
    _HELP_CMDS[3].n_formats = 1;
    _HELP_CMDS[3].n_aliases = 3;
    strcpy(_HELP_CMDS[3].format[0], "");
    strcpy(_HELP_CMDS[3].format_INFO[0], "Exit Application server");
    strcpy(_HELP_CMDS[3].aliases[0], "exit");
    strcpy(_HELP_CMDS[3].aliases[1], "shutdown");
    strcpy(_HELP_CMDS[3].aliases[2], "stop");

    //  Show
    strcpy(_HELP_CMDS[4].title, "Show");
    _HELP_CMDS[4].n_formats = 4;
    _HELP_CMDS[4].n_aliases = 1;
    strcpy(_HELP_CMDS[4].format[0], "");
    strcpy(_HELP_CMDS[4].format[1], "srvrinfo");
    strcpy(_HELP_CMDS[4].format[2], "cltinfo");
    strcpy(_HELP_CMDS[4].format[3], "cltinfo <ID>");
    strcpy(_HELP_CMDS[4].format_INFO[0], "Shows Seerver/Clients Information");
    strcpy(_HELP_CMDS[4].format_INFO[1], "Show Server Informations");
    strcpy(_HELP_CMDS[4].format_INFO[2], "Shows the first Valid Client's Informations");
    strcpy(_HELP_CMDS[4].format_INFO[3], "Show a Client's Informations");
    strcpy(_HELP_CMDS[4].aliases[0], "show");

    // No Forground
    strcpy(_HELP_CMDS[5].title, "Hide");
    _HELP_CMDS[5].n_formats = 1;
    strcpy(_HELP_CMDS[5].format[0], "");
    strcpy(_HELP_CMDS[5].format_INFO[0], "Hides the interface");
    _HELP_CMDS[5].n_aliases = 2;
    strcpy(_HELP_CMDS[5].aliases[0], "hide");  
    strcpy(_HELP_CMDS[5].aliases[1], "nofg");  
}

void getOtherAliases(__HELP_INFO INF, const char *Excluded)
{
    if (!re)
        free(re);

    re = malloc(sizeof(char) * 1024);
    for (int i = 0; i < INF.n_aliases; i++)
        if (strcmp(INF.aliases[i], Excluded) != 0)
        {
            strcat(re, INF.aliases[i]);
            strcat(re, " ");
        }
}
int findlongestformat(char *alia, int I)
{
    int max = 0;
    for (int i = 0; i < _HELP_CMDS[I].n_formats; i++)
        if ((strlen(_HELP_CMDS[I].format[i]) + strlen(_HELP_CMDS[I].format_INFO[i])) > (strlen(_HELP_CMDS[I].format[max]) + strlen(_HELP_CMDS[I].format_INFO[max])))
            max = i;
    return strlen(alia) + strlen(_HELP_CMDS[I].format[max]) + strlen(_HELP_CMDS[I].format_INFO[max]) + 3;
}
int findlongestcmd()
{
    int max = 0;
    int ifremax;
    int remax = (strlen(_HELP_CMDS[max].format[0]) + strlen(_HELP_CMDS[max].format_INFO[0]));
    for (int i = 1; i < n_HELP_CMDS; i++)
        if ((ifremax = strlen(_HELP_CMDS[i].format[0]) + strlen(_HELP_CMDS[i].format_INFO[0])) > remax)
        {
            max = i;
            remax = ifremax;
        }

    if ((ifremax = strlen(CMD->CMD) + strlen(_HELP_CMDS[1].format[1]) + strlen(_HELP_CMDS[1].format[1])) > remax)
        remax = ifremax;

    return remax + 20;
}
int _HELP_CMD_ISVALID()
{
    char re[1024];
    cnsle_print(_CNSLE_ERROR, "Check Start");
    for (int i = 0; i < n_HELP_CMDS; i++)
    {
        for (int u = 0; u < _HELP_CMDS[i].n_aliases; u++)
            if (!strcmp(_HELP_CMDS[i].aliases[u], CMD->v_args[0]))
                return i;
    }
    return -1;
}

void __show_help_EMPT()
{
    width = 8 + findlongestcmd();
    height = 6 + n_HELP_CMDS;
    TARG_X = (MAX_X - width) / 2;
    TARG_Y = (MAX_Y - height) / 2;

    create_win_target(height, width, "[ Help ]", BTN_OK, 0);
    for (int i = 0; i < n_HELP_CMDS; i++)
    {
        wattrset(TARGET_WIN, COLOR_PAIR(B_BCKGRND_WIN));
        mvwprintw(TARGET_WIN, 2 + i, 2, "- [");
        wattrset(TARGET_WIN, COLOR_PAIR(B_HELP_ALIAS));
        wprintw(TARGET_WIN, " %s ", _HELP_CMDS[i].aliases[0]);
        wattrset(TARGET_WIN, COLOR_PAIR(B_BCKGRND_WIN));
        wprintw(TARGET_WIN, "] :");
        wattrset(TARGET_WIN, COLOR_PAIR(B_HELP_INFO));
        wprintw(TARGET_WIN, " %s ", _HELP_CMDS[i].format_INFO[0]);
    }

    wattrset(TARGET_WIN, COLOR_PAIR(B_HELP_ALIAS));
    mvwprintw(TARGET_WIN, height - 3, 2, "%s", CMD->CMD);
    wattrset(TARGET_WIN, COLOR_PAIR(B_HELP_FORMAT));
    wprintw(TARGET_WIN, " %s", _HELP_CMDS[1].format[1]);
    wattrset(TARGET_WIN, COLOR_PAIR(B_HELP_INFO));
    wprintw(TARGET_WIN, ": %s", _HELP_CMDS[1].format_INFO[1]);
}

void __show_help_INVALID()
{
    width = 6 + strlen(CMD->v_args[0]) + 20;
    height = 6;
    TARG_X = (MAX_X - width) / 2;
    TARG_Y = (MAX_Y - height) / 2;

    create_win_target(height, width, "[ Help ]", BTN_OK, 0);
    mvwprintw(TARGET_WIN, 2, 2, "No help for \"%s\"", CMD->v_args[0]);
}

void __show_help_VALID(int HELP_INDEX)
{
    int width = 8 + findlongestformat(CMD->v_args[0], HELP_INDEX);
    int height = 7 + _HELP_CMDS[HELP_INDEX].n_formats;

    TARG_X = (MAX_X - width) / 2;
    TARG_Y = (MAX_Y - height) / 2;

    create_win_target(height, width, "[ Help ]", BTN_OK, 0);

    wattron(TARGET_WIN, COLOR_PAIR(_C_TEXT_BLUE_WHITE) | A_BOLD);
    mvwprintw(TARGET_WIN, 1, (width - strlen(" Command : ") - strlen(_HELP_CMDS[HELP_INDEX].title)) / 2, " Command : ");
    wattroff(TARGET_WIN, COLOR_PAIR(_C_TEXT_BLUE_WHITE) | A_BOLD);
    wprintw(TARGET_WIN, "%s", _HELP_CMDS[HELP_INDEX].title);

    for (int i = 0; i < _HELP_CMDS[HELP_INDEX].n_formats; i++)
    {
        wattrset(TARGET_WIN, COLOR_PAIR(B_HELP_ALIAS));
        mvwprintw(TARGET_WIN, 3 + i, 2, "%s", CMD->v_args[0]);
        wattrset(TARGET_WIN, COLOR_PAIR(B_HELP_FORMAT));
        wprintw(TARGET_WIN, " %s", _HELP_CMDS[HELP_INDEX].format[i]);
        wattrset(TARGET_WIN, COLOR_PAIR(B_HELP_INFO));
        wprintw(TARGET_WIN, ": %s", _HELP_CMDS[HELP_INDEX].format_INFO[i]);
    }

    if(_HELP_CMDS[HELP_INDEX].n_aliases == 1)
        return;

    getOtherAliases(_HELP_CMDS[HELP_INDEX], CMD->v_args[0]);
    wattrset(TARGET_WIN, COLOR_PAIR(B_HELP_ALIASES_TEXT));
    mvwprintw(TARGET_WIN, height - 3, 2, "Aliases: ");
    wattrset(TARGET_WIN, COLOR_PAIR(B_HELP_ALIASES));
    wprintw(TARGET_WIN, "%s", re);
}

void cmd_help()
{
    int indx;
    clear();
    refresh();
    if (ArgsAreNull())
        __show_help_EMPT();
    else
    {
        if ((indx = _HELP_CMD_ISVALID()) < 0)
            __show_help_INVALID();
        else
            __show_help_VALID(indx);
    }
    refresh();
    wrefresh(TARGET_WIN);
    char r;
    noecho();
    while (1)
    {
        r = getch();
        if (r == '\n')
        {
            break;
        }
    }
    echo();
}