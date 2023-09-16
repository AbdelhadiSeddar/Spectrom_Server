#include "../../_Imports.h"
#include "srvrinfo.h"
char *temp = NULL;
void __show_srvrinfo()
{
    show_width = 48;
    show_height = 11;
    TARG_X = (MAX_X - show_width) / 2;
    TARG_Y = (MAX_Y - show_height) / 2;

    create_win_target(show_height, show_width, "[ Server Info ]", BTN_OK, 0);
    wattrset(TARGET_WIN, COLOR_PAIR(_C_TEXT_BLUE_WHITE) | A_UNDERLINE);
    mvwprintw(TARGET_WIN, 2, 2, "Time:");
    wattrset(TARGET_WIN, COLOR_PAIR(_C_TEXT_BLUE_WHITE));
    mvwprintw(TARGET_WIN, 3, 2, " | Current: ");
    wattrset(TARGET_WIN, COLOR_PAIR(_C_TEXT_BLUE_WHITE) | A_BOLD);
    twprinw(TARGET_WIN);
    wattrset(TARGET_WIN, COLOR_PAIR(_C_TEXT_BLUE_WHITE));
    mvwprintw(TARGET_WIN, 4, 2, " | Start: ");
    wattrset(TARGET_WIN, COLOR_PAIR(_C_TEXT_BLUE_WHITE) | A_BOLD);
    wprintw(TARGET_WIN, "%s", _CONSOLE_LINES->time);
    wattrset(TARGET_WIN, COLOR_PAIR(_C_TEXT_BLUE_WHITE));
    mvwprintw(TARGET_WIN, 5, 2, "Port: ");
    wattrset(TARGET_WIN, COLOR_PAIR(_C_TEXT_BLUE_WHITE) | A_BOLD);
    wprintw(TARGET_WIN, "%d", PORT);
    wattrset(TARGET_WIN, COLOR_PAIR(_C_TEXT_BLUE_WHITE));
    mvwprintw(TARGET_WIN, 5, 15, "Server Socket: ");
    wattrset(TARGET_WIN, COLOR_PAIR(_C_TEXT_BLUE_WHITE) | A_BOLD);
    wprintw(TARGET_WIN, "%d", server_sock);
    wattrset(TARGET_WIN, COLOR_PAIR(_C_TEXT_BLUE_WHITE));
    mvwprintw(TARGET_WIN, 6, 2, "Client States(%d): ", CLIENT_THREADS);
    for (int i = 0; i < CLIENT_THREADS; i++)
    {
        if (CLIENT_STATES[i] == _Used)
        {
            wattrset(TARGET_WIN, COLOR_PAIR(_C_TEXT_RED_WHITE));
            wprintw(TARGET_WIN, "%s", "Used");
        }
        else
        {
            wattrset(TARGET_WIN, COLOR_PAIR(_C_TEXT_GREEN_WHITE));
            wprintw(TARGET_WIN, "%s", "Not Used");
        }
        if (i < (CLIENT_THREADS - 1))
        {
            wattrset(TARGET_WIN, COLOR_PAIR(_C_TEXT_BLUE_WHITE));
            wprintw(TARGET_WIN, " | ");
        }
    }
    wattrset(TARGET_WIN, COLOR_PAIR(_C_TEXT_BLUE_WHITE));
    mvwprintw(TARGET_WIN, 7, 2, "Clients: ");
    wattrset(TARGET_WIN, COLOR_PAIR(_C_TEXT_BLUE_WHITE) | A_BOLD);
    wprintw(TARGET_WIN, "%d", clts);
    wattrset(TARGET_WIN, COLOR_PAIR(_C_TEXT_BLUE_WHITE));
    mvwprintw(TARGET_WIN, 8, 2, "Console Lines: ");
    wattrset(TARGET_WIN, COLOR_PAIR(_C_TEXT_BLUE_WHITE) | A_BOLD);
    wprintw(TARGET_WIN, "%d", _C_CNSLE_LINE->num);
    wrefresh(TARGET_WIN);
}

void _show_srvrinfo()
{
    __show_srvrinfo();

    char r;
    while (1)
    {
        r = getch();
        if (r == KEY_ENTR)
        {
            break;
        }
    }
}
