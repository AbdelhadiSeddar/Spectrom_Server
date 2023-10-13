#include "../_Imports.h"

int action_width, action_height;

#define _ACTION_ITEMS_AMOUNT 2
int _ACTION_ITEM_SELCT = -1;
char *_ACTION_ITEMS[_ACTION_ITEMS_AMOUNT] = {
    "Kick Client",
    "Logout Client"};
void _action_logout(clt_lnk _clt)
{
    if (_clt == NULL && alertbox(Info, "Client Not Found"))
        return;
    if (alertbox(Confirm))
    {
        clt_logout(_clt);
        alertbox(Info, "Client logged out");
        return;
    }
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

void _action_logout_cltID(int cltid)
{
    clt_lnk _clt = NULL;
    if (cltid >= 0)
        clt_find_local_ClientID(cltid, &_clt);

    _action_logout(_clt);
}

void _action_kick(clt_lnk _clt)
{
    if (_clt == NULL && alertbox(InfoTitled, "[ Invalid ]", "Client Not Found"))
        return;

    if (alertbox(Confirm))
    {
        clt_disconnect(_clt);
        alertbox(Info, "Client Kicked");
        return;
    }
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

void _action_kick_cltID(int cltid)
{
    clt_lnk _clt = NULL;
    if (cltid >= 0)
        clt_find_local_ClientID(cltid, &_clt);
    _action_kick(_clt);
}

int _action(int ActedOn)
{
    _ACTION_ITEM_SELCT = 0;
    action_width = 45;
    action_height = 7 + _ACTION_ITEMS_AMOUNT;
    TARG_X = (MAX_X - action_width) / 2;
    TARG_Y = (MAX_Y - action_height) / 2;

    char r;
    create_win_target(action_height, action_width, "[ Action ]", BTN_OK, 0);
    char *help = "Press [ ESC ] to Return.";
    mvprintw(MAX_Y - 1, MAX_X - strlen(help) - 1, "Press [ ");
    wattrset(stdscr, COLOR_PAIR(_C_TEXT_RED_CYAN));
    mvprintw(MAX_Y - 1, MAX_X - strlen(help + 8) - 1, "ESC");
    wattrset(stdscr, COLOR_PAIR(B_BCKGRND));
    mvprintw(MAX_Y - 1, MAX_X - strlen(help + 12) - 1, "] to Return.");
_refresh_show_:
    wrefresh(TARGET_WIN);
    mvwprintw(TARGET_WIN, 2, 2, "Select Action %s", ActedOn > 0 ? "On Client " : "(Enter Client ID after):");
    if (ActedOn > 0)
        wprintw(TARGET_WIN, "%d:", ActedOn);
    for (int i = 0; i < _ACTION_ITEMS_AMOUNT; i++)
    {
        wattrset(TARGET_WIN, COLOR_PAIR(i == _ACTION_ITEM_SELCT ? _C_TEXT_WHITE_BLUE : _C_TEXT_BLACK_WHITE));
        mvwprintw(TARGET_WIN, 4 + i, 4, "%d- ", i + 1);
        wprintw(TARGET_WIN, "%s", _ACTION_ITEMS[i]);
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
            if (_ACTION_ITEM_SELCT == 0)
                _ACTION_ITEM_SELCT = _ACTION_ITEMS_AMOUNT - 1;
            else
                _ACTION_ITEM_SELCT--;
            goto _refresh_show_;
        case KEY_D:
            if (_ACTION_ITEM_SELCT == (_ACTION_ITEMS_AMOUNT - 1))
                _ACTION_ITEM_SELCT = 0;
            else
                _ACTION_ITEM_SELCT++;
            goto _refresh_show_;
        case '1':
            _ACTION_ITEM_SELCT = 0;
            goto _refresh_show_;
        case '2':
            _ACTION_ITEM_SELCT = 1;
            goto _refresh_show_;
        case KEY_ESC:
            return 1;
        default:
            break;
        }
    }
}

void cmd_action()
{
    clear();
    refresh();
    noecho();
    int arg0, arg1;
    if (CMD->n_args > 0 && (arg0 = StringToInt(CMD->v_args[0])) > 0)
    {
        _action(arg0);
        switch (_ACTION_ITEM_SELCT)
        {
        case 0:
            _action_kick_cltID(arg0);
            break;
        case 1:
            _action_logout_cltID(arg0);
            break;

        default:
            break;
        }
        return;
    }
    else if (CMD->n_args >= 1)
    {
        if (!strcmp((CMD->v_args[0]), "kick"))
            if (CMD->n_args > 1 && (arg1 = StringToInt(CMD->v_args[1])) > 0)
                _action_kick_cltID(arg1);
            else
                _action_kick_cltID(-1);
        else if (!strcmp((CMD->v_args[0]), "logout"))
            _action_logout_cltID((CMD->n_args) > 2 ? arg0 : -1);
        else
            _action(-1);
        return;
    }
    else if (_action(-1))
        return;

    win_target_prompt_data(PROMPT_INT);
    switch (_ACTION_ITEM_SELCT)
    {
    case 0:
        _action_kick_cltID(*((int *)PROMPT_RESULT));
        break;
    case 1:
        _action_logout_cltID(*((int *)PROMPT_RESULT));
        break;
    default:
        break;
    }
    return;
}