#include "../../_Imports.h"
#include "cltlist.h"
#include "cltinfo.h"

clt_lnk *Current_Cltlist = NULL;
typedef enum CltListToShow_t
{
    next,
    prev,
    new,
    reshow
} CltListToShow;

int clts_amount = 0;

void __GetCltList(CltListToShow toshow)
{

    if (CLT_LIST == NULL_CLIENT || CLT_LIST == NULL)
    {
        clts_amount = 0;
        return;
    }

    int i;
    clt_lnk temp;
    switch (toshow)
    {
    case new:
        temp = NULL_CLIENT;
        break;
    case reshow:
        return;
    case next:
        temp = Current_Cltlist[clts_amount - 1]->next == NULL ? Current_Cltlist[0]->prev : Current_Cltlist[clts_amount - 1]->next;
        break;
    case prev:
        temp = Current_Cltlist[0]->prev;
        break;
    }

    if (Current_Cltlist)
        free(Current_Cltlist);
    Current_Cltlist = calloc(show_height - 6, sizeof(clt_lnk));
    if (toshow != prev)
    {
        for (i = 0; i < (MAX_Y * 0.75) && temp->next != NULL; i++)
            Current_Cltlist[i] = (temp = temp->next);
        clts_amount = i;
        return;
    }
    for (i = (MAX_Y * 0.75) - 1; i >= 0 && temp->prev != NULL; i--)
        Current_Cltlist[i] = (temp = temp->prev);
    i = (MAX_Y * 0.75);
    return;
}

void _show_cltlist()
{
    int _ITEM_SELCT;
    char r;
    CltListToShow ToShow = new;
_change_cltlist:;
    show_width = 57;
    show_height = MAX_Y * 0.75 + 6;

    __GetCltList(ToShow);
    TARG_X = (MAX_X - show_width) / 2;
    TARG_Y = (MAX_Y - show_height) / 2;
    create_win_target(show_height, show_width, CLT_LIST == NULL_CLIENT ? "[No Clients Found]" : "[ Clients List ]", BTN_OK, 0);
    _ITEM_SELCT = 0;
_refresh_cltlist_:;
    wrefresh(TARGET_WIN);
    if (clts_amount)
    {
        for (int i = 0; i < (show_height - 6); i++)
        {
            wattrset(TARGET_WIN, COLOR_PAIR(i == _ITEM_SELCT ? _C_TEXT_WHITE_BLUE : _C_TEXT_BLACK_WHITE));
            if (i < clts_amount)
                mvwprintw(TARGET_WIN, 2 + i, 2, " Client (%d) : %s %s", Current_Cltlist[i]->Client.ID, Current_Cltlist[i]->Client.GUID, i == _ITEM_SELCT ? " >" : "  ");
            else
                mvwprintw(TARGET_WIN, 2 + i, 2, "                                                     ");
        }
    }
    else
    {
        mvwprintw(TARGET_WIN, (show_height - 1) / 2, (show_width - strlen("Nothing To Show")) / 2, "Nothing To Show");
    }
    wattrset(TARGET_WIN, COLOR_PAIR(_C_TEXT_BLACK_WHITE));
    wrefresh(TARGET_WIN);
    noecho();
    if (clts_amount)
        while (1)
        {
            r = getch();
            switch (r)
            {
            case KEY_R:
            case KEY_ENTR:
                _show_cltinfo_id(Current_Cltlist[_ITEM_SELCT]->Client.ID);
                delwin(TARGET_WIN);
                ToShow = reshow;
                goto _change_cltlist;
            case KEY_U:
                if (_ITEM_SELCT == 0)
                {
                    if (Current_Cltlist[0]->prev != NULL_CLIENT)
                    {
                        ToShow = prev;
                        goto _change_cltlist;
                    }
                    goto _refresh_cltlist_;
                }
                else
                {
                    _ITEM_SELCT--;
                    goto _refresh_cltlist_;
                }
            case KEY_D:
                if (_ITEM_SELCT == (clts_amount - 1))
                {
                    if (Current_Cltlist[(clts_amount - 1)]->next != NULL)
                    {
                        ToShow = next;
                        goto _change_cltlist;
                    }
                    goto _refresh_cltlist_;
                }
                else
                {
                    _ITEM_SELCT++;
                    goto _refresh_cltlist_;
                }
            case KEY_ESC:
                if (alertbox(Confirm))
                    return;
                else
                    goto _refresh_cltlist_;
            default:
                goto _refresh_cltlist_;
            }
        }
    else
        while (1)
        {
            r = getch();
            if (r == KEY_ENTR)
                break;
        }
}