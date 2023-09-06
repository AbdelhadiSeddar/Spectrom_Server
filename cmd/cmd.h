#ifndef CMD_H
#define CMD_H

typedef struct CMD_ARGS_t CMD_ARGS;
extern CMD_ARGS *CMD;

struct CMD_ARGS_t
{
    char CMD[1024];
    char args[1024];
    unsigned int n_args;
    char *v_args[15];
};
extern void srvr_cmd();

extern void GetCMD_s(char *Origin);
extern void GetArgs_s();
extern void ResolveCMD();

extern void ShowCMD();

extern void cmd_exit_app();
extern void cmd_clear();

extern void get();

/// @brief Check if the arguments of Command are NULL or empty.
/// @return 1 => Arguments are NULL/Empty |[]| 0 => Arguments are not NULL/Empty
extern int ArgsAreNull();

#define KEY_U 3
#define KEY_D 2
#define KEY_L 4
#define KEY_R 5

#define KEY_F12 20

#define KEY_ENTR 10
#define KEY_ESC 27
#define KEY_DEL 127

#endif