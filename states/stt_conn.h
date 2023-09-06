#ifndef STT_CONN_H
#define STT_CONN_H

///
/// Connection States.
///
/// Codes : 0[][]
///
///

#define STT_CONN_ACC "000"  // Accepted incoming connection
#define STT_CONN_CONF "001" // Confirm
#define STT_CONN_BAN "00A"  // SEND BANNED STATUS
#define STT_CONN_KCK "00B"  // SEND KICK STATUS
#define STT_CONN_RCN "00C"  // RECONNECTION STATUS
#define STT_CONN_UPD "00D"  // Server Status : Developpement | Maintenance
#define STT_CONN_MTH "00E"  // Server awaiting connection method Expected STT_CLT_RCV_(LOGI/REGS) ["110" # "111"]
#define STT_CONN_END "00F"  // ENDING INCOMING CONNECTION

#endif