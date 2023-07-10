#include "../_Imports.h"

int __POPUP_STATUS = 0;
int _CODE = 0;
va_list ARG_POPUP;

char **__POPUP_ARGS;
int __NPOPUP_ARGS;

char *__POPUP_VAL;
int POPUP_X, POPUP_Y;

WINDOW *_POPUP_WIN, *_S_POPUP_WIN;
void create_POPUP_WIN(int __POPUP_TYPE)
{
    POPUP_X = (MAX_X - strlen(__POPUP_VAL) + 2) / 2;
    POPUP_Y = (MAX_Y - 5);
    _S_POPUP_WIN = newwin(3, strlen(__POPUP_VAL) + 2, POPUP_Y + 1, POPUP_X + 1);
    _POPUP_WIN = newwin(3, strlen(__POPUP_VAL) + 2, POPUP_Y, POPUP_X);

    wbkgdset(_S_POPUP_WIN, COLOR_PAIR(SHADOW));
    switch (__POPUP_TYPE)
    {
    case __POPUP_STATUS_ERR:
        wbkgdset(_POPUP_WIN, COLOR_PAIR(B_ERR));
        break;
    case __POPUP_STATUS_INFO:
        wbkgdset(_POPUP_WIN, COLOR_PAIR(B_INFO));
        break;
    }

    box(_POPUP_WIN, 0, 0);
    wrefresh(_S_POPUP_WIN);
    wrefresh(_POPUP_WIN);
    refresh();
}

void ShowPopupVal(int CODE)
{
    __POPUP_VAL = calloc(256, sizeof(char));
    switch (__POPUP_STATUS)
    {
    case __POPUP_STATUS_ERR:
        switch (CODE)
        {
        case __POPUP_ERR_CODE_EMPT:
            sprintf(__POPUP_VAL, "Empty Command");
            break;
        case __POPUP_ERR_CODE_INVALID:
            sprintf(__POPUP_VAL, "Invalid Command");
            break;
        case __POPUP_ERR_CODE_INVALID_ARG:
            sprintf(__POPUP_VAL, "Invalid Argument");
            break;
        case __POPUP_ERR_CODE_INVALID_PATH:
            sprintf(__POPUP_VAL, "Given path is Invalid");
            break;

        default:
            break;
        }
        create_POPUP_WIN_ERR();
        break;
    case __POPUP_STATUS_INFO:
        switch (CODE)
        {
        case __POPUP_INFO_CODE_CLEARED:
            sprintf(__POPUP_VAL, "Window Cleared");
            break;
        case __POPUP_INFO_CODE_SUCCESS:
            sprintf(__POPUP_VAL, "Command Successfully executed.");
            break;
        case __POPUP_INFO_CODE_LOGWRITTEN:
            sprintf(__POPUP_VAL, "Log Successfully written as %s", __POPUP_ARGS[0]);
            break;

        default:
            break;
        }
        create_POPUP_WIN_INFO();
        break;
    }

    mvwprintw(_POPUP_WIN, 1, 1, __POPUP_VAL);
    wrefresh(_POPUP_WIN);
}

int DefinePopup(int POPUP_STATUS, int POPUP_CODE, ...)
{

    _CODE = POPUP_CODE;
    __POPUP_STATUS = POPUP_STATUS;
    va_list POPUP_ARGS;

    switch (__POPUP_STATUS)
    {
    case __POPUP_STATUS_INFO:

        /*          For INFO Status          */

        switch (POPUP_CODE)
        {
        // special cases
        case __POPUP_INFO_CODE_LOGWRITTEN:
            __NPOPUP_ARGS = 1;
            break;

        // Normal cases
        default:
            __NPOPUP_ARGS = 0;
            break;
        }

        if (__NPOPUP_ARGS)
        {
            __POPUP_ARGS = malloc(__NPOPUP_ARGS * sizeof(char **));
            va_start(POPUP_ARGS, POPUP_CODE);
            for (int i = 0; i < __NPOPUP_ARGS; i++)
            {
                __POPUP_ARGS[i] = calloc(128, sizeof(char *));
                strcpy(__POPUP_ARGS[i], va_arg(POPUP_ARGS, char *));
            }
            va_end(POPUP_ARGS);
        }

        break;

    default:
        __NPOPUP_ARGS = 0;
        break;
    }
}

int ShowPopup()
{
    if (__POPUP_STATUS == __POPUP_STATUS_ERR)
        switch (_CODE)
        {
        case __POPUP_ERR_CODE_EMPT:
        case __POPUP_ERR_CODE_INVALID:
        case __POPUP_ERR_CODE_INVALID_ARG:
            ShowPopupVal(_CODE);
            return 0;
            break;

        default:
            break;
        }
    else
        switch (_CODE)
        {
        case __POPUP_INFO_CODE_CLEARED:
        case __POPUP_INFO_CODE_LOGWRITTEN:
        case __POPUP_INFO_CODE_SUCCESS:
            ShowPopupVal(_CODE);
            return 0;
            break;

        default:
            break;
        }

    return -1;
}
void HidePopup()
{
    __POPUP_STATUS = 0;
    _CODE = 0;
    refresh();
    if (_POPUP_WIN != NULL)
    {
        delwin(_POPUP_WIN);
    }
    if (_S_POPUP_WIN != NULL)
        delwin(_S_POPUP_WIN);

    attrset(COLOR_PAIR(B_BCKGRND));
    for (int i = POPUP_Y; i < POPUP_Y + 4; i++)
    {
        for (int u = 0; u < MAX_X; u++)
        {
            mvprintw(i, u, " ");
        }
    }

    refresh();
}