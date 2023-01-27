#ifndef CLT_CNTRL_H
#define CLT_CNTRL_H
// Not Yet Fixed
/*
char* GETIP();
*/

extern void *srvr_accept_clt(void *arg);
extern void *srvr_clt_handle(void *arg);
extern void clt_handling(void *clt);

extern int CLT_CNTRL_LOGI(clt_lnk *client);
extern int CLT_CNTRL_REGS(clt_lnk *client);
extern int CLT_CNTRL_LOGO(clt_lnk *client);
#endif