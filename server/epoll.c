#include "../_Imports.h"

int n_fds, epollfd;
epoll_ev ev, *evs;

void epoll_inis()
{
    checkerr((epollfd = epoll_create1(0)), "Error Creating Epoll.");
    checkerr(INIS != 1 ? -1 : 0, "Call the clt_init() before calling this!");
    ev.events = EPOLLIN;
    ev.data.fd = server_sock;
    epoll_unload_fds();
    epoll_add(server_sock, &ev);
    INIS++;
}

void epoll_add(int sock, epoll_ev *ev)
{
    if (epoll_ctl(epollfd, EPOLL_CTL_ADD, sock, ev) < 0)
    {
        switch (errno)
        {
        case EEXIST:
            epoll_del(sock, ev);
            epoll_add(sock, ev);
            break;

        default:
            checkerr(-1, "Could Not add Socket");
            break;
        }
    }
}
void epoll_del(int sock, epoll_ev *ev)
{
    epoll_ctl(epollfd, EPOLL_CTL_DEL, sock, ev);
}
void epoll_load_fds()
{
    do
    {
        n_fds = epoll_pwait(epollfd, evs, MAXEVENTS, 100, NULL);
    } while (n_fds == -1 && errno == EINTR);
}
void epoll_unload_fds()
{
    free(evs);
    evs = malloc(MAXEVENTS * sizeof(epoll_ev));
}

int SetNonBlocking(int fd)
{
    return (fd < 0) ? -1 : fcntl(fd, F_SETFL, fcntl(fd, F_GETFL, 0) | O_NONBLOCK);
}

int SetBlocking(int fd)
{
    return (fd < 0) ? -1 : fcntl(fd, F_SETFL, fcntl(fd, F_GETFL, 0) ^ O_NONBLOCK);
}