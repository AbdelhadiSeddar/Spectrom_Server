#ifndef EPOLL_H
#define EPOLL_H

#include "../_Imports.h"

typedef struct epoll_event epoll_ev;

extern int n_fds, epollfd;
extern epoll_ev ev, evs[MAX];

extern void epoll_inis();
extern void epoll_load_fds();

/// @brief Sets the File Descriptor ( fd ) Into Non-Blocking. Recommended By Linux Manual. ( Actual Code Gotten From StackOverFlow ).
/// @param fd File Descriptor.
extern int SetNonBlocking(int fd);

#endif