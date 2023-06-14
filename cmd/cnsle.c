#include "../_Imports.h"

CNSLE_LINE _CONSOLE_LINES = NULL;
CNSLE_LINE _C_CNSLE_LINE = NULL;

pthread_mutex_t _CONSOLE_MUTEX;
pthread_mutex_t _CONSOLE_TIME_VERIFY_MUTEX;

void cnsle_inis()
{
    checkerr(pthread_mutex_init(&(_CONSOLE_MUTEX), NULL), "Could intitiate MUTEX for CONSOLE");
    checkerr(pthread_mutex_init(&(_CONSOLE_TIME_VERIFY_MUTEX), NULL), "Could intitiate MUTEX for CONSOLE TIME");
    pthread_mutex_lock(&_CONSOLE_MUTEX);

    _CONSOLE_LINES = malloc(sizeof(C_LINE));
    _CONSOLE_LINES->num = 0;
    strcpy((_CONSOLE_LINES->origin), _CNSLE_SYSTEM);
    strcpy((_CONSOLE_LINES->val), "Started Console");
    tsprint((_CONSOLE_LINES->time));

    _CONSOLE_LINES->NXT = (_CONSOLE_LINES->PREV = NULL);

    _C_CNSLE_LINE = _CONSOLE_LINES;
    pthread_mutex_unlock(&_CONSOLE_MUTEX);
}

CNSLE_LINE line;
WINDOW *_CNSLE_SCRN = NULL;
int _C_LINES;
int LN;

void cnsle_write()
{
    char t[64];
    sprintf(t, "Clients: %d Client State: %d Server State %d", clts, CLIENTS_STATE, SERVER_STATE);
    mvwprintw(TARGET_WIN, 2, (MAX_X - strlen(t)) / 2, t);
    wrefresh(TARGET_WIN);

    if (LN != (_C_CNSLE_LINE->num))
    {
        line = _C_CNSLE_LINE;
        for (int i = 0; line != NULL && i < (_C_LINES - 3); i++)
        {
            cnsle_printf(_C_LINES - 2 - i, 1, line);
            line = line->PREV;
        }
        wrefresh(_CNSLE_SCRN);
    }
}

void cnsle_cntrl()
{
    nodelay(stdscr, TRUE);
    char r;
    while (1)
    {
        r = getch();
        if (r == ERR)
        {
            if (pthread_mutex_trylock(&_CONSOLE_TIME_VERIFY_MUTEX))
            {
                cnsle_write();
                sleep(1);
                pthread_mutex_unlock(&_CONSOLE_TIME_VERIFY_MUTEX);
            }
        }
        else
            switch (r)
            {
            case KEY_D:
                break;
            case KEY_U:
                break;
            case KEY_ESC:
                delwin(_CNSLE_SCRN);
                clear();
                nodelay(stdscr, FALSE);
                return;
                break;

            default:
                break;
            }
        refresh();
    }
    nodelay(stdscr, FALSE);
}

void cnsle()
{
    if ((CMD->n_args) == 0 || ArgsAreNull())
        cnsle_show();
    else
        debug_cmd_cnsle_log();
}

void cnsle_show()
{
    clear();
    wbkgdset(stdscr, COLOR_PAIR(B_CNSLE_HEADER));
    refresh();
    TARG_X = 0;
    TARG_Y = 0;
    create_win_target(MAX_Y, MAX_X, "[ Console ]", BTN_NULL, 1);

    wrefresh(TARGET_WIN);
    refresh();

    _CNSLE_SCRN = newwin(MAX_Y - 6, MAX_X, 6, 0);

    wattrset(_CNSLE_SCRN, COLOR_PAIR(B_CNSLE));
    box(_CNSLE_SCRN, 0, 0);

    _C_LINES = getmaxy(_CNSLE_SCRN);
    cnsle_write();

    wrefresh(_CNSLE_SCRN);
    wrefresh(TARGET_WIN);
    refresh();

    cnsle_cntrl();

    SetBckGrnd();
}

/// @brief
/// @param line
/// @return 0 SYSTEM 1 USER -1 ERROR
int getownertype(CNSLE_LINE line)
{
    if (!strcmp((line->origin), _CNSLE_SYSTEM))
        return 0;
    if (!strcmp((line->origin), _CNSLE_ERROR))
        return -1;

    return 1;
}

void cnsle_printf(int Y, int X, CNSLE_LINE line)
{
    for (int i = 1; i < MAX_X - 1; i++)
        mvwprintw(_CNSLE_SCRN, Y, i, " ");

    int o = getownertype(line);
    int s = X + strlen(line->time);
    wattrset(_CNSLE_SCRN, COLOR_PAIR(B_CNSLE));
    mvwprintw(_CNSLE_SCRN, Y, X, "[");

    wattrset(_CNSLE_SCRN, COLOR_PAIR(B_CNSLE_PRINT_TIME));
    mvwprintw(_CNSLE_SCRN, Y, X + 1, (line->time));

    wattrset(_CNSLE_SCRN, COLOR_PAIR(B_CNSLE));
    mvwprintw(_CNSLE_SCRN, Y, (s += 1), "]");

    wattrset(_CNSLE_SCRN, COLOR_PAIR(o == 0 ? B_CNSLE_PRINT_OWN_SYS : (o == -1 ? B_CNSLE_PRINT_OWN_ERR : B_CNSLE_PRINT_OWN_USR)));
    mvwprintw(_CNSLE_SCRN, Y, (s += 1), " %s ", (line->origin));

    wattrset(_CNSLE_SCRN, A_DIM | COLOR_PAIR(B_CNSLE_PRINT_EXTRA_SPLIT));
    mvwprintw(_CNSLE_SCRN, Y, (s += 3 + strlen(line->origin)), "~$ ");

    wattrset(_CNSLE_SCRN, COLOR_PAIR(o == 0 ? B_CNSLE_PRINT_VAL_SYS : (o == -1 ? B_CNSLE_PRINT_VAL_ERR : B_CNSLE_PRINT_VAL_USR)));
    mvwprintw(_CNSLE_SCRN, Y, (s += 3), (line->val));
}

int cnsle_print(char *owner, char *text)
{
    CONSOLE_LINE ln;
    ln = malloc(sizeof(C_LINE));

    tsprint(ln->time);
    strcpy((ln->val), text);
    strcpy((ln->origin), owner);

    ln->NXT = NULL;

    while (1)
    {
        if (!pthread_mutex_lock(&_CONSOLE_MUTEX))
            break;
    }
    ln->num = (_C_CNSLE_LINE->num) + 1;
    ln->PREV = _C_CNSLE_LINE;
    _C_CNSLE_LINE->NXT = ln;
    _C_CNSLE_LINE = ln;
    pthread_mutex_unlock(&_CONSOLE_MUTEX);

    return 0;
}
