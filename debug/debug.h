#ifndef DEBUG_h
#define DEBUG_H

#define __CNSLE_LOG_CMD 0
#define __CNSLE_LOG_SYS 1

#define debug_cmd_cnsle_log() debug_cnsle_log_c(__CNSLE_LOG_CMD);
#define debug_sys_cnsle_log() debug_cnsle_log_c(__CNSLE_LOG_SYS);

extern void debug_clt_list();
extern void debug_cnsle_log_c(int);

#endif
