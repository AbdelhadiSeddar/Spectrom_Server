#include "../_Imports.h"

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
	_DEFINE_HELP();
	ShowInf();
	refresh();
}

void ShowInf()
{
	wattrset(stdscr, COLOR_PAIR(B_BCKGRND));
	mvprintw(0, (MAX_X - strlen(SCRN_TITLE)) / 2, "%s\n", SCRN_TITLE);
	printw("Interface Started Dimentions: %dx%d\n", MAX_X, MAX_Y);
	char *help = "Press [ F12 ] to Show help.";
	mvprintw(MAX_Y - 1, MAX_X - strlen(help) - 1, "Press [ ");
	wattrset(stdscr, COLOR_PAIR(_C_TEXT_GREEN_CYAN) | A_DIM);
	mvprintw(MAX_Y - 1, MAX_X - strlen(help + 8) - 1, "F12");
	wattrset(stdscr, COLOR_PAIR(B_BCKGRND));
	mvprintw(MAX_Y - 1, MAX_X - strlen(help + 12) - 1, "] to Show help.");
}

void SetColors()
{
	start_color();

	/// START TEXT COLORS
	init_pair(_C_TEXT_BLACK_BLACK, COLOR_BLACK, COLOR_BLACK);
	init_pair(_C_TEXT_RED_BLACK, COLOR_RED, COLOR_BLACK);
	init_pair(_C_TEXT_BLUE_BLACK, COLOR_BLUE, COLOR_BLACK);
	init_pair(_C_TEXT_GREEN_BLACK, COLOR_GREEN, COLOR_BLACK);
	init_pair(_C_TEXT_YELLOW_BLACK, COLOR_YELLOW, COLOR_BLACK);
	init_pair(_C_TEXT_CYAN_BLACK, COLOR_CYAN, COLOR_BLACK);
	init_pair(_C_TEXT_WHITE_BLACK, COLOR_WHITE, COLOR_BLACK);

	init_pair(_C_TEXT_WHITE_RED, COLOR_WHITE, COLOR_RED);

	init_pair(_C_TEXT_BLACK_GREEN, COLOR_BLACK, COLOR_GREEN);
	init_pair(_C_TEXT_WHITE_GREEN, COLOR_WHITE, COLOR_GREEN);

	init_pair(_C_TEXT_WHITE_BLUE, COLOR_WHITE, COLOR_BLUE);

	init_pair(_C_TEXT_BLACK_CYAN, COLOR_BLACK, COLOR_CYAN);
	init_pair(_C_TEXT_GREEN_CYAN, COLOR_GREEN, COLOR_CYAN);
	init_pair(_C_TEXT_BLUE_CYAN, COLOR_BLUE, COLOR_CYAN);

	init_pair(_C_TEXT_BLACK_WHITE, COLOR_BLACK, COLOR_WHITE);
	init_pair(_C_TEXT_RED_WHITE, COLOR_RED, COLOR_WHITE);
	init_pair(_C_TEXT_GREEN_WHITE, COLOR_GREEN, COLOR_WHITE);
	init_pair(_C_TEXT_BLUE_WHITE, COLOR_BLUE, COLOR_WHITE);
	init_pair(_C_TEXT_MAGENTA_WHITE, COLOR_MAGENTA, COLOR_WHITE);
}

void SetBckGrnd()
{
	wbkgdset(stdscr, COLOR_PAIR(B_BCKGRND));
	wrefresh(stdscr);
	clear();
}

void create_win_cmd()
{

	COMWIN_X = (MAX_X - 54) / 2;
	COMWIN_Y = (MAX_Y - 8) / 2;
	S_COMMAND_WIN = newwin(8, 54, COMWIN_Y + 1, COMWIN_X + 1);
	COMMAND_WIN = newwin(8, 54, COMWIN_Y, COMWIN_X);
	keypad(COMMAND_WIN, TRUE);

	wbkgd(S_COMMAND_WIN, COLOR_PAIR(SHADOW));
	wbkgdset(COMMAND_WIN, COLOR_PAIR(B_BCKGRND_WIN));
	wclear(COMMAND_WIN);
	box(COMMAND_WIN, 0, 0);

	wattron(COMMAND_WIN, A_UNDERLINE | A_BLINK | COLOR_PAIR(B_TITLE));
	mvwprintw(COMMAND_WIN, 0, (54 - strlen("[ Command ]")) / 2, "[ Command ]");
	wattroff(COMMAND_WIN, A_UNDERLINE | A_BLINK | COLOR_PAIR(B_TITLE));

	wattron(COMMAND_WIN, A_DIM | COLOR_PAIR(CMD_SYM));
	mvwprintw(COMMAND_WIN, 3, 3, "~>");
	wattroff(COMMAND_WIN, A_DIM | COLOR_PAIR(CMD_SYM));

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

void create_win_target(int Height, int Width, const char *Title, int BTN_TYPE, int BLC_BCK_GRN)
{

	if (!BLC_BCK_GRN)
		S_TARGET_WIN = newwin(Height, Width, TARG_Y + 1, TARG_X + 1);
	TARGET_WIN = newwin(Height, Width, TARG_Y, TARG_X);

	if (!BLC_BCK_GRN)
		wbkgd(S_TARGET_WIN, COLOR_PAIR(SHADOW));

	wbkgd(TARGET_WIN, COLOR_PAIR((BLC_BCK_GRN ? B_CNSLE_HEADER : B_BCKGRND_WIN)));
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
	case BTN_NULL:
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
