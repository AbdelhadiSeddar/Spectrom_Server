#include "../../_Imports.h"
#include "alertbox.h"

WINDOW *alertbox_w, *s_alertbox_w;
int alertbox(alertbox_type type, ...)
{
    char *Text, *Title;
    va_list va;

    Title = (char *)"[ Alert ]";
    switch (type)
    {
    case Confirm:
        Title = (char *)"[ Confirm ]";
        Text = (char *)"Are you Sure?";
        break;
    case HelpNotFound:
        Title = (char *)"[ Help ]";
    case Info:
        va_start(va, type);
        Text = va_arg(va, char *);
        va_end(va);
        break;
    default:
        break;
    }
    int alertbox_height = 6;
    int alertbox_width = strlen(Text) + (type == HelpNotFound ? 21 : 0) + 16;
    s_alertbox_w = newwin(alertbox_height, alertbox_width, ((MAX_Y - alertbox_height) / 2) + 1, ((MAX_X - alertbox_width) / 2) + 1);
    alertbox_w = newwin(alertbox_height, alertbox_width, (MAX_Y - alertbox_height) / 2, (MAX_X - alertbox_width) / 2);

    wbkgd(s_alertbox_w, COLOR_PAIR(SHADOW));
    wbkgdset(alertbox_w, COLOR_PAIR(B_BCKGRND_WIN));
    wclear(alertbox_w);
    box(alertbox_w, 0, 0);
    wrefresh(s_alertbox_w);
    wrefresh(alertbox_w);

    mvwprintw(alertbox_w, 0, (alertbox_width - strlen(Title)) / 2, "%s", Title);
    if (type == HelpNotFound)
        mvwprintw(alertbox_w, 2, (alertbox_width - strlen(Text) - 21) / 2, "Help Not found for \"%s\"", Text);
    else
        mvwprintw(alertbox_w, 2, (alertbox_width - strlen(Text)) / 2, "%s", Text);
    refresh();
    char r;
    int select;
    switch (type)
    {
    case Confirm:
        select = 0;
    _refresh_alertbox_confirm_:;
        wattron(alertbox_w, COLOR_PAIR(select ? SLCT : B_BCKGRND_WIN));
        mvwprintw(alertbox_w, alertbox_height - 2, (alertbox_width - 18) / 2, "< Ok >");
        wattroff(alertbox_w, COLOR_PAIR(select ? SLCT : B_BCKGRND_WIN));
        wattron(alertbox_w, COLOR_PAIR(!select ? SLCT : B_BCKGRND_WIN));
        mvwprintw(alertbox_w, alertbox_height - 2, (alertbox_width - 18) / 2 + 8, "< Cancel >");
        wattroff(alertbox_w, COLOR_PAIR(!select ? SLCT : B_BCKGRND_WIN));
        wrefresh(alertbox_w);

        r = getch();
        switch (r)
        {
        case KEY_ENTR:
            wclear(alertbox_w);
            wclear(s_alertbox_w);
            wrefresh(alertbox_w);
            delwin(alertbox_w);
            delwin(s_alertbox_w);
            return select;
        case KEY_L:
        case KEY_R:
            select = !select;
        default:
            goto _refresh_alertbox_confirm_;
        }
    case HelpNotFound:
    case Info:
        wattron(alertbox_w, COLOR_PAIR(SLCT));
        mvwprintw(alertbox_w, alertbox_height - 2, (alertbox_width - strlen("< Ok >")) / 2, "< Ok >");
        wattroff(alertbox_w, COLOR_PAIR(SLCT));
        wrefresh(alertbox_w);
        refresh();
        while (1)
        {
            r = getch();
            if (r == KEY_ENTR)
                return 1;
            else
            {
                mvprintw(2, 2, "%d %c", r, r);
                refresh();
            }
        }
    }
}