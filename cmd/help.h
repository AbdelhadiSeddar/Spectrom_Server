#ifndef HELP_H
#define HELP_H

typedef struct __HELP_INFO_t
{
    int n_formats;
    int n_aliases;
    char title[64];
    char format[10][32];
    char format_INFO[10][128];
    char aliases[10][32];
} __HELP_INFO;
typedef __HELP_INFO *_HELP_CMD;
extern __HELP_INFO *_HELP_CMDS;

extern void _DEFINE_HELP();

extern void cmd_help();

#endif