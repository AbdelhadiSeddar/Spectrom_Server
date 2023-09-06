#ifndef CLTINFO_H
#define CLTINFO_H

extern WINDOW* Account;

extern void _show_cltinfo_(int cltid);

#define _show_cltinfo() _show_cltinfo_(-1)
#define _show_cltinfo_id(cltid) _show_cltinfo_(cltid)


#endif
