#ifndef INTRF_H
#define INTRF_H

#define SCRN_TITLE "Application"

#pragma region TEXTCOLORS
#define _C_TEXT_BLACK_BLACK 00
#define _C_TEXT_RED_BLACK 10
#define _C_TEXT_GREEN_BLACK 20
#define _C_TEXT_YELLOW_BLACK 30
#define _C_TEXT_BLUE_BLACK 40
#define _C_TEXT_CYAN_BLACK 60
#define _C_TEXT_WHITE_BLACK 70

#define _C_TEXT_WHITE_RED 71

#define _C_TEXT_BLACK_GREEN 02
#define _C_TEXT_WHITE_GREEN 72

#define _C_TEXT_BLACK_BLUE 03
#define _C_TEXT_GREEN_BLUE 23
#define _C_TEXT_WHITE_BLUE 73

#define _C_TEXT_BLACK_CYAN 06
#define _C_TEXT_RED_CYAN 16
#define _C_TEXT_GREEN_CYAN 26
#define _C_TEXT_BLUE_CYAN 46

#define _C_TEXT_BLACK_WHITE 07
#define _C_TEXT_RED_WHITE 17
#define _C_TEXT_GREEN_WHITE 27
#define _C_TEXT_BLUE_WHITE 47
#define _C_TEXT_MAGENTA_WHITE 57
#define _C_TEXT_CYAN_WHITE 57
#pragma endregion

#pragma endregion BTN COLORS

#define SLCT _C_TEXT_WHITE_BLUE
#define N_SLCT _C_TEXT_BLACK_WHITE
#define CMD_SYM _C_TEXT_RED_WHITE
#pragma endregion

#define SHADOW _C_TEXT_BLACK_BLACK

#pragma region MAIN
#define B_BCKGRND _C_TEXT_BLACK_CYAN
#define B_BCKGRND_WIN _C_TEXT_BLACK_WHITE
#define B_TITLE _C_TEXT_GREEN_WHITE
#define B_HELP _C_TEXT_GREEN_CYAN
#pragma endregion

#pragma region POPUP
#define B_ERR _C_TEXT_WHITE_RED
#define B_INFO _C_TEXT_BLACK_GREEN

#define B_ERR_TEXT _C_TEXT_WHITE_RED
#define B_ERR_HIGHLIGHT _C_TEXT_WHITE_RED
#pragma endregion

#pragma region B_CNSLE //2XX
#define B_CNSLE _C_TEXT_BLUE_BLACK
#define B_CNSLE_HEADER _C_TEXT_GREEN_BLACK

#define B_CNSLE_PRINT_TIME _C_TEXT_YELLOW_BLACK
#define B_CNSLE_PRINT_OWN_SYS _C_TEXT_YELLOW_BLACK
#define B_CNSLE_PRINT_OWN_USR _C_TEXT_BLUE_BLACK
#define B_CNSLE_PRINT_OWN_ERR _C_TEXT_RED_BLACK

#define B_CNSLE_PRINT_VAL_SYS _C_TEXT_WHITE_BLACK
#define B_CNSLE_PRINT_VAL_USR _C_TEXT_WHITE_BLACK
#define B_CNSLE_PRINT_VAL_ERR _C_TEXT_RED_BLACK

#define B_CNSLE_PRINT_EXTRA_SPLIT _C_TEXT_BLUE_BLACK
#pragma endregion

#pragma region Help

#define B_HELP_ALIAS _C_TEXT_BLUE_WHITE
#define B_HELP_FORMAT _C_TEXT_MAGENTA_WHITE
#define B_HELP_INFO _C_TEXT_BLACK_WHITE
#define B_HELP_ALIASES _C_TEXT_RED_WHITE
#define B_HELP_ALIASES_TEXT _C_TEXT_GREEN_WHITE

#pragma endregion

#pragma region BUTTONS
#define BTN_NULL -1
#define BTN_OK 0
#define BTN_OK_CANCEL 1
#define BTN_YES_NO 2
#define BTN_SUBMIT 3
#pragma endregion

extern WINDOW *COMMAND_WIN, *S_COMMAND_WIN, *TARGET_WIN;

extern int MAX_X, MAX_Y, TARG_Y, TARG_X;

extern void scrn_inis();

extern void SetColors();
extern void SetBckGrnd();

extern void ShowInf();

extern void create_win_cmd();
extern void create_win_target(int Height, int Width, const char *Title, int BTN_TYPE, int BLC_BCK_GRN);

// COLOR_BLACK 0
// COLOR_RED 1
// COLOR_GREEN 2
// COLOR_YELLOW 3
// COLOR_BLUE 4
// COLOR_MAGENTA 5
// COLOR_CYAN 6
// COLOR_WHITE 7
typedef enum PROMPT_TYPE_t
{
    PROMPT_STRING,
    PROMPT_INT
} PROMPT_TYPE;
extern void *PROMPT_RESULT;
extern int win_target_prompt_data(PROMPT_TYPE Type);
#endif

