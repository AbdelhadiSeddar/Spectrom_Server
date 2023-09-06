#include "../../_Imports.h"
#include "cltinfo.h"
WINDOW *Account = NULL;

#define __show_nullclt() __show_cltinfo(NULL_CLIENT)

void __show_cltinfo(clt_lnk clt)
{
    show_width = 5 + (clt->Account.state == _NOTLOGGED ? strlen("- GUID: ") : strlen(" - UUID: ")) + 38;
    show_height = 13;
    TARG_X = (MAX_X - show_width) / 2;
    TARG_Y = (MAX_Y - show_height) / 2;

    create_win_target(show_height, show_width, clt == NULL_CLIENT ? "[No Client Found]" : "[ Client Info ]", BTN_OK, 0);
    wattrset(TARGET_WIN, COLOR_PAIR(_C_TEXT_BLUE_WHITE));
    mvwprintw(TARGET_WIN, 1, 1, " Client");
    mvwprintw(TARGET_WIN, 2, 2, " GUID:");
    mvwprintw(TARGET_WIN, 3, 2, " Socket:");
    wattrset(TARGET_WIN, COLOR_PAIR(_C_TEXT_CYAN_WHITE));
    mvwprintw(TARGET_WIN, 1, 8, "(%d)", clt->Client.ID);
    mvwprintw(TARGET_WIN, 2, 11, "%s", clt->Client.GUID);
    mvwprintw(TARGET_WIN, 3, 11, "%d", clt->Client.sock);

    Account = newwin(5, show_width - 2, TARG_Y + 5, TARG_X + 1);
    wbkgdset(Account, COLOR_PAIR(clt->Account.state ? _C_TEXT_WHITE_BLUE : _C_TEXT_WHITE_RED));
    wclear(Account);
    box(Account, 0, 0);
    refresh();
    wrefresh(Account);
    wrefresh(TARGET_WIN);

    wattrset(Account, COLOR_PAIR(clt->Account.state ? _C_TEXT_WHITE_BLUE : _C_TEXT_WHITE_RED));
    mvwprintw(Account, 0, 1, "Account");
    wattron(Account, COLOR_PAIR(clt->Account.state ? _C_TEXT_WHITE_BLUE : _C_TEXT_WHITE_RED));
    if (clt->Account.state == _LOGGED)
    {
        mvwprintw(Account, 1, 2, "- UUID: %s", clt->Account.UUID);
        mvwprintw(Account, 2, 2, "- Username: %s", clt->Account.USRNM);
    }
    else
    {
        mvwprintw(Account, 2, (show_width - 17) / 2, "<Not Connected>");
    }
    wattroff(Account, COLOR_PAIR(clt->Account.state ? _C_TEXT_WHITE_BLUE : _C_TEXT_WHITE_RED));
    wrefresh(Account);
}

void _show_cltinfo_(int cltid)
{
    clt_lnk _clt = NULL;
    if (cltid >= 0)
        clt_find_local_ClientID(cltid, &_clt);
    else if (CMD->n_args >= 2)
        clt_find_local_ClientID(StringToInt(CMD->v_args[1]), &_clt);
    else
        _clt = clt_find_local_uuid_fv(NULL_CLIENT);

    if (_clt == NULL)
        __show_nullclt();
    else
        __show_cltinfo(_clt);
}
