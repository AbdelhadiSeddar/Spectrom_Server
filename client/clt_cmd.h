#ifndef CLT_CMD_H

#define CLT_CMD_H
///
/// Part for connection status messages
///
#define CMD_CONN_ACC "000"  // Accepted incoming connection
#define CMD_CONN_CONF "001" // Confirm
#define CMD_CONN_BAN "00A"  // SEND BANNED STATUS
#define CMD_CONN_KCK "00B"  // SEND KICK STATUS
#define CMD_CONN_RCN "00C"  // FORCE RECONNECTION DUE TO AN ERROR
#define CMD_CONN_UPD "00D"  // Server Status : Developpement | Maintenance
#define CMD_CONN_MTH "00E"  // Server awaiting connection method Expected CMD_CLT_RCV_(LOGI/REGS) ["110" # "111"]
#define CMD_CONN_END "00F"  // ENDING INCOMING CONNECTION

#define CMD_CLT_SND_GUID "010" // Sending a request for the client's GUID
#define CMD_CLT_SND_USRN "011" // Sending a request for the client's Username
#define CMD_CLT_SND_PSWD "012" // Sending a request for the client's Password
#define CMD_CLT_SND_MACA "013" // Sending a request for the client's MAC Adress !! Not Applicable !!

#define CMD_CLT_RCV_INFO "101" // Client requesting his account's info
#define CMD_CLT_RCV_OINF "102" // Client requesting another account's info
#define CMD_CLT_RCV_SUNM "103" // Client requesting a search using Username
#define CMD_CLT_RCV_SUGU "104" // Client requesting a search using GUID
#define CMD_CLT_RCV_LSTM "105" // Client requesting the account's Messages list ordered by last recived
#define CMD_CLT_RCV_LSTF "106" // Client requesting the account's Friends list ordered by name (Future feature: Most active with)
#define CMD_CLT_RCV_LSTB "107" // Client requesting the account's Blocked list ordered by name
#define CMD_CLT_RCV_LSTS "108" // Client requesting the account's Starred/Special list ordered by name (Same future feature as LSTF)
#define CMD_CLT_RCV_LSTO "109" // Client requesting the account's Online friends
#define CMD_CLT_RCV_LSTD "10A" // Client requesting the account's Online friends that had set themselfs to not be disturbed
#define CMD_CLT_RCV_USRS "10B" // ???
#define CMD_CLT_RCV_URLB "10C" // Client requesttng the removal of a  user from the account's blocked list
#define CMD_CLT_RCV_URLS "10D" // Client requesting the removal of a user form the account's Starred/Special list
#define CMD_CLT_RCV_URLF "10E" // Client requesting the removal of a user from the account's Friends list
#define CMD_CLT_RCV_UALB "10F" // Client requesting the addition of a user in the account's blocked list
#define CMD_CLT_RCV_UALS "10G" // Client requesting the addition of a user in the account's Starred/Special list
#define CMD_CLT_RCV_UALF "10H" // Client requesting the addition of a user in the account's Friends list

#define CMD_CLT_RCV_LOGI "110" // Client Attempting to login
#define CMD_CLT_RCV_REGS "111" // Client Attempting to register an account.
#define CMD_CLT_RCV_LOGO "11F" // Client Attempting to logout

#endif