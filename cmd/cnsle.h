#ifndef CNSL_H
#define CNSL_H

#define cnsle_update() cnsle_reset(0)
#define cnsle_set() cnsle_reset(1)

#define _CNSLE_SYSTEM "System"
#define _CNSLE_ERROR "Error"

/// @brief Print on the console as "System"
/// @param char Content of the Console Line
/// @return 0
#define cnsle_print_sys(char) cnsle_print(_CNSLE_SYSTEM, char);
/// @brief Print on the console as an Error
/// @param char Content of the Console Line
/// @return 0
#define cnsle_print_err(char) cnsle_print(_CNSLE_ERROR, char);

typedef struct CNSLE_LINE_t C_LINE;
typedef struct CNSLE_LINE_t *CNSLE_LINE;
typedef CNSLE_LINE CONSOLE_LINE;
struct CNSLE_LINE_t
{
    char origin[32];
    char val[1024];
    char time[128];
    int num;

    CNSLE_LINE PREV;
    CNSLE_LINE NXT;
};
extern pthread_mutex_t _CONSOLE_MUTEX;

extern CNSLE_LINE _CONSOLE_LINES;
extern CNSLE_LINE _C_CNSLE_LINE;

extern void cnsle();

extern void cnsle_inis();
extern void cnsle_reset(int mode);
extern void cnsle_show();
extern void cnsle_refresh();
extern void cnsle_printf(int X, int Y, CNSLE_LINE line);

/// @brief Default console print [ Other cnsle_print rely on this ]
/// @param owner Who sent the Console Line
/// @param text Content of the Console Line
/// @return 0
extern int cnsle_print(char *owner, char *text);

#endif