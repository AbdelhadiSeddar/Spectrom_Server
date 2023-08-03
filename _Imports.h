#pragma region STANDARD
#include <stdlib.h>
#include <ncurses.h>
#include <menu.h>
#include <features.h>
#include <string.h>
#include <stdarg.h>
#include <unistd.h>
#include <assert.h>
#include <pthread.h>
#include <fcntl.h>
#include <errno.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/epoll.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <time.h>
#pragma endregion

#include "cmd/cmd.h"
#include "cmd/help.h"
#include "cmd/cnsle.h"
#include "cmd/popup.h"

#include "server/inis.h"
#include "server/epoll.h"
#include "server/intrf.h"

#include "client/clt_defs.h"
#include "client/clt_cntrl.h"
#include "client/clt_accs.h"

#include "states/stt_acc.h"
#include "states/stt_clt.h"
#include "states/stt_conn.h"

#include "debug/debug.h"

#include "main_defs.h"
#include "misc.h"
