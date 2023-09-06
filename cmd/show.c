#include "../_Imports.h"
#include "show/cltinfo.h"
#include "show/srvrinfo.h"

int show_width, show_height;
/// @brief Amount of items show in _show()
#define _ITEMS_AMOUNT 3
int _SHOW_ITEM_SELCT = -1;
char *_SHOW_ITEMS[_ITEMS_AMOUNT] = {
    "Server Info (srvrinfo)",
    "Client Info (cltinfo) ( First valid )",
    "Client Info (cltinfo) ( Search with ID)"};

int _show()
{
    _SHOW_ITEM_SELCT = 0;
    show_width = 52;
    show_height = 7 + _ITEMS_AMOUNT;
    TARG_X = (MAX_X - show_width) / 2;
    TARG_Y = (MAX_Y - show_height) / 2;

    char r;
    create_win_target(show_height, show_width, "[ Show ]", BTN_OK, 0);
    char *help = "Press [ ESC ] to Return.";
    mvprintw(MAX_Y - 1, MAX_X - strlen(help) - 1, "Press [ ");
    wattrset(stdscr, COLOR_PAIR(_C_TEXT_RED_CYAN));
    mvprintw(MAX_Y - 1, MAX_X - strlen(help + 8) - 1, "ESC");
    wattrset(stdscr, COLOR_PAIR(B_BCKGRND));
    mvprintw(MAX_Y - 1, MAX_X - strlen(help + 12) - 1, "] to Return.");
_refresh_show_:
    wrefresh(TARGET_WIN);
    mvwprintw(TARGET_WIN, 2, 2, "Select What to show:");
    for (int i = 0; i < _ITEMS_AMOUNT; i++)
    {
        wattrset(TARGET_WIN, COLOR_PAIR(i == _SHOW_ITEM_SELCT ? _C_TEXT_WHITE_BLUE : _C_TEXT_BLACK_WHITE));
        mvwprintw(TARGET_WIN, 4 + i, 4, "%d- ", i + 1);
        wprintw(TARGET_WIN, "%s", _SHOW_ITEMS[i]);
    }
    wattrset(TARGET_WIN, COLOR_PAIR(_C_TEXT_BLACK_WHITE));
    wrefresh(TARGET_WIN);
    noecho();
    while (1)
    {
        r = getch();
        switch (r)
        {
        case KEY_ENTR:
            return 0;
        case KEY_U:
            if (_SHOW_ITEM_SELCT == 0)
                _SHOW_ITEM_SELCT = _ITEMS_AMOUNT - 1;
            else
                _SHOW_ITEM_SELCT--;
            goto _refresh_show_;
        case KEY_D:
            if (_SHOW_ITEM_SELCT == (_ITEMS_AMOUNT - 1))
                _SHOW_ITEM_SELCT = 0;
            else
                _SHOW_ITEM_SELCT++;
            goto _refresh_show_;
        case '1':
            _SHOW_ITEM_SELCT = 0;
            goto _refresh_show_;
        case '2':
            _SHOW_ITEM_SELCT = 1;
            goto _refresh_show_;
        case '3':
            _SHOW_ITEM_SELCT = 2;
            goto _refresh_show_;
        case KEY_ESC:
            return 1;
        default:
            //mvprintw(1, 1, "%c   %d", r, r);
            break;
        }
    }
}

void cmd_show()
{
    clear();
    refresh();
    noecho();
    if (CMD->n_args >= 1)
    {
        if (!strcmp((CMD->v_args[0]), (_HELP_CMDS[4].format[1])))
            _show_srvrinfo();
        else if (!strcmp((CMD->v_args[0]), (_HELP_CMDS[4].format[2])))
            _show_cltinfo();
        else if (_show())
            return;
    }
    else if (_show())
        return;
    switch (_SHOW_ITEM_SELCT)
    {
    case 0:
        _show_srvrinfo();
        break;
    case 1:
        _show_cltinfo();
        break;
    case 2:
        win_target_prompt_data(PROMPT_INT);
        _show_cltinfo_id(*((int *)PROMPT_RESULT));
        break;

    default:
        break;
    }

    char r;
    while (1)
    {
        r = getch();
        if (r == '\n')
        {
            break;
        }
    }
    return;
}