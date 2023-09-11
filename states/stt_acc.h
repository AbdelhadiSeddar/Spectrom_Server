
#ifndef STT_ACC_H
#define STT_ACC_H

///
/// Connection States.
///
/// Codes : 3[][]
///
///

#define STT_ACC_YES "300"  //    Account Connected Successfully
#define STT_ACC_BAN "301"  //    Account Banned
#define STT_ACC_SUS "302"  //    Account Suspended
#define STT_ACC_DIS "303"  //    Account Disabled
#define STT_ACC_2FA "304"  //    Account Requiring 2FA ( 2-Factor Authentification )
#define STT_ACC_ALR "305"  //    Account Already Connected
#define STT_ACC_NCON "306" //    Account Not connected to any account

#define STT_ACC_INVU "310" //   Invalid Username
#define STT_ACC_INVP "311" //   Invalid Password
#define STT_ACC_INV2 "312" //   Invalid 2FA Code
#define STT_ACC_INVR "313" //   Invalid Request
#define STT_ACC_INVF "314" //   Invalid Format
#define STT_ACC_UNMU "315" //   Unavailable Username (Taken)


#define STT_ACC_RQST_CONN "320" // Client Requesting Login
#define STT_ACC_RQST_FUNM "321" // Client Requesting Username Recovery
#define STT_ACC_RQST_FPWD "322" // Client Requesting Password Recovery
#define STT_ACC_RQST_VUNM "323" // Client Requesting Username Availability.
#define STT_ACC_RQST_VPWD "324" // Client Requesting Password Validity

#endif