#include "../_Imports.h"

int n_fds, epollfd;
epoll_ev ev, evs[MAXEVENTS];

void epoll_inis()
{
    checkerr((epollfd = epoll_create1(0)), "Error Creating Epoll.");
    checkerr(INIS != 1 ? -1 : 0, "Call the clt_init() before calling this!");
    ev.events = EPOLLIN;
    ev.data.fd = server_sock;
    checkerr(epoll_ctl(epollfd, EPOLL_CTL_ADD, server_sock, &ev), "Could Not Add the Server Socket");
    INIS++;
}

void epoll_load_fds()
{
    checkerr((n_fds = epoll_wait(epollfd, evs, MAXEVENTS, 10)), "Could Not get the number of Fds (epoll_wait)");
}

int SetNonBlocking(int fd)
{
    return (fd < 0) ? -1 : fcntl(fd, F_SETFL, fcntl(fd, F_GETFL, 0) | O_NONBLOCK);
}
