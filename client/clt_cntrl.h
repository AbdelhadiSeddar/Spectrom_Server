#ifndef CLT_CNTRL_H
#define CLT_CNTRL_H

// Not Yet Fixed
/*
char* GETIP();
*/
extern int clts;

extern void *srvr_accept_clt(void *);
extern void *srvr_clt_handle(void *);
extern void clt_handling(ST_T, clt_lnk *);

extern int clt_accept(clt_inf **);

extern int CLT_CNTRL_LOGI(clt_lnk *);
extern int CLT_CNTRL_REGS(clt_lnk *);
extern int CLT_CNTRL_LOGO(clt_lnk *);
extern int CLT_CNTRL_DISC(clt_lnk *);
extern int CLT_CNTRL_RCN(clt_lnk);


#endif