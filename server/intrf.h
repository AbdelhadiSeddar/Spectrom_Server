#ifndef INTRF_H
#define INTRF_H

#define SCRN_TITLE "Application"

#define BCKGRND COLOR_BLACK
#define W_BCKGRND COLOR_WHITE

#define NRML 1
#define R_BLK 2
#define R_RED 3
#define R_GRN 4
#define R_YEL 5
#define R_BLU 6
#define R_MAG 7
#define R_CYN 8
#define R_WHT 9

#define B_BLK 11
#define B_RED 12
#define B_GRN 13
#define B_YEL 14
#define B_BLU 15
#define B_MAG 16
#define B_CYN 17
#define B_WHT 18

#define SLCT 19
#define N_SLCT 20
#define CMD_SYM 21


#define BTN_OK 0
#define BTN_OK_CANCEL 1
#define BTN_YES_NO 2
#define BTN_SUBMIT 3

extern WINDOW *COMMAND_WIN, *S_COMMAND_WIN, *TARGET_WIN;

extern int MAX_X, MAX_Y, TARG_Y, TARG_X;

extern void scrn_inis();

extern void SetColors();
extern void SetBckGrnd();

extern void ShowInf();

extern void create_win_cmd();
extern void create_win_target(int Height, int Width, const char* Title, int BTN_TYPE);
#endif