#ifndef EPOLL_H
#define EPOLL_H

#include "../_Imports.h"

typedef struct epoll_event epoll_ev;

extern int n_fds, epollfd;
extern epoll_ev ev, *evs;

extern void epoll_inis();
extern void epoll_add(int, epoll_ev *);
extern void epoll_del(int, epoll_ev *);
extern void epoll_load_fds();
extern void epoll_unload_fds();

/// @brief Sets the File Descriptor ( fd ) Into Non-Blocking. Recommended By Linux Manual. ( Actual Code Gotten From StackOverFlow ).
/// @param fd File Descriptor.
extern int SetNonBlocking(int fd);
extern int SetBlocking(int fd);

#endif