#ifndef MAIN_DEFS_H
#define MAIN_DEFS_H

#define PATH_TO_STORE_CLIENTS "/ftp/dev/clients/"
#define _PATH_LOG "bin/Spectrom_server.log"
#define MAX_QUEUE 100
#define MAX_THREADS 150
#define MAXEVENTS 2048
#define PORT 9114

#define UNIT_SEPARATOR (char)31


#define __SCRN_SHOWN 1
#define __SCRN_NOTSHOWN 0
extern int __SCRN_STATUS;
extern pthread_mutex_t __SCRN_MUTEX;
extern pthread_t __SCRN_CONTROLLER;

extern void __SCRN_OFF(void);
extern void __SCRN_ON(void);
#endif

