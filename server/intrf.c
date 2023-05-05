#include "../_Imports.h"
#include "intrf.h"

int MAX_X, MAX_Y, COMWIN_X, COMWIN_Y, TARG_Y, TARG_X;
WINDOW *COMMAND_WIN, *S_COMMAND_WIN, *TARGET_WIN, *S_TARGET_WIN;

void scrn_inis()
{
	clear();
	initscr();
	getmaxyx(stdscr, MAX_Y, MAX_X);
	SetColors();
	SetBckGrnd();

	raw();
	keypad(stdscr, TRUE);
	noecho();
	ShowInf();
	refresh();
}

void ShowInf()
{
	attrset(COLOR_PAIR(R_BLK));
	mvprintw(0, (MAX_X - strlen(SCRN_TITLE)) / 2, "%s\n", SCRN_TITLE);
	printw("Interface Started Dimentions: %dx%d\n", MAX_X, MAX_Y);
	char *help = "Press [ F12 ] to Show help.";
	attrset(COLOR_PAIR(R_BLK));
	mvprintw(MAX_Y - 1, MAX_X - strlen(help) - 1, "Press [ ");
	attrset(COLOR_PAIR(R_GRN) | A_DIM);
	mvprintw(MAX_Y - 1, MAX_X - strlen(help + 8) - 1, "F12");
	attrset(COLOR_PAIR(R_BLK));
	mvprintw(MAX_Y - 1, MAX_X - strlen(help + 12) - 1, "] to Show help.");
}

void SetColors()
{
	start_color();
	init_pair(R_BLK, COLOR_BLACK, COLOR_CYAN);
	init_pair(R_BLU, COLOR_BLUE, W_BCKGRND);
	init_pair(R_CYN, COLOR_CYAN, BCKGRND);
	init_pair(R_GRN, COLOR_GREEN, COLOR_CYAN);
	init_pair(R_MAG, COLOR_MAGENTA, BCKGRND);
	init_pair(R_RED, COLOR_RED, BCKGRND);
	init_pair(R_WHT, COLOR_WHITE, BCKGRND);
	init_pair(R_YEL, COLOR_YELLOW, BCKGRND);

	init_pair(B_BLK, BCKGRND, COLOR_BLACK);
	init_pair(B_BLU, BCKGRND, COLOR_BLUE);
	init_pair(B_CYN, BCKGRND, COLOR_CYAN);
	init_pair(B_GRN, W_BCKGRND, COLOR_GREEN);
	init_pair(B_MAG, W_BCKGRND, COLOR_MAGENTA);
	init_pair(B_RED, W_BCKGRND, COLOR_RED);
	init_pair(B_WHT, BCKGRND, COLOR_WHITE);
	init_pair(B_YEL, W_BCKGRND, COLOR_YELLOW);

	init_pair(SLCT, COLOR_WHITE, COLOR_BLUE);
	init_pair(N_SLCT, COLOR_BLACK, COLOR_WHITE);
	init_pair(CMD_SYM, COLOR_RED, COLOR_WHITE);
}

void SetBckGrnd()
{
	wbkgd(stdscr, COLOR_PAIR(B_CYN));
}

void create_win_cmd()
{

	COMWIN_X = (MAX_X - 54) / 2;
	COMWIN_Y = (MAX_Y - 8) / 2;
	S_COMMAND_WIN = newwin(8, 54, COMWIN_Y + 1, COMWIN_X + 1);
	COMMAND_WIN = newwin(8, 54, COMWIN_Y, COMWIN_X);

	keypad(COMMAND_WIN, TRUE);

	wbkgd(S_COMMAND_WIN, COLOR_PAIR(B_BLK));
	wbkgd(COMMAND_WIN, COLOR_PAIR(B_WHT));
	box(COMMAND_WIN, 0, 0);

	wattron(COMMAND_WIN, A_UNDERLINE | A_BLINK);
	mvwprintw(COMMAND_WIN, 0, (54 - strlen("[ Command ]")) / 2, "[ Command ]");
	wattroff(COMMAND_WIN, A_UNDERLINE | A_BLINK);

	wattron(COMMAND_WIN, COLOR_PAIR(CMD_SYM));
	mvwprintw(COMMAND_WIN, 3, 3, "~>");
	wattroff(COMMAND_WIN, COLOR_PAIR(CMD_SYM));

	wattron(COMMAND_WIN, COLOR_PAIR(SLCT));
	mvwprintw(COMMAND_WIN, 6, (54 - strlen("< Submit >")) / 2, "< Submit >");
	wattroff(COMMAND_WIN, COLOR_PAIR(SLCT));

	wmove(COMMAND_WIN, 3, 6);
	wrefresh(S_COMMAND_WIN);
	wrefresh(COMMAND_WIN);
}

void destroy_win_cmd()
{
}

void create_win_target(int Height, int Width, const char *Title, int BTN_TYPE)
{

	S_TARGET_WIN = newwin(Height, Width, TARG_Y + 1, TARG_X + 1);
	TARGET_WIN = newwin(Height, Width, TARG_Y, TARG_X);

	wbkgd(TARGET_WIN, COLOR_PAIR(B_BLK));
	wbkgd(TARGET_WIN, COLOR_PAIR(B_WHT));
	box(TARGET_WIN, 0, 0);

	mvwprintw(TARGET_WIN, 0, (Width - strlen(Title)) / 2, Title);

	switch (BTN_TYPE)
	{
	case BTN_OK:
		wattron(TARGET_WIN, COLOR_PAIR(SLCT));
		mvwprintw(TARGET_WIN, Height - 2, (Width - strlen("< Ok >")) / 2, "< Ok >");
		wattroff(TARGET_WIN, COLOR_PAIR(SLCT));
		break;
	case BTN_OK_CANCEL:
		break;
	case BTN_SUBMIT:
		break;
	case BTN_YES_NO:
		break;

	default:
		break;
	}

	wrefresh(S_TARGET_WIN);
	wrefresh(TARGET_WIN);
}

void destroy_win_target()
{
}
