#include "_Imports.h"
#include "main_defs.h"

int __SCRN_STATUS = __SCRN_SHOWN;
pthread_mutex_t __SCRN_MUTEX;

void __SCRN_OFF(void)
{
    __SCRN_STATUS = __SCRN_NOTSHOWN;
    pthread_mutex_lock(&__SCRN_MUTEX);
}
void __SCRN_ON(void)
{
    __SCRN_STATUS = __SCRN_SHOWN;
    pthread_mutex_unlock(&__SCRN_MUTEX);
}