#ifndef STT_CLT_H
#define STT_CLT_H
///
/// Client States.
///
/// Codes : 1[][]
///
///

#define STT_CLT_RCV_INFO "101" // Client requesting his account's info
#define STT_CLT_RCV_OINF "102" // Client requesting another account's info
#define STT_CLT_RCV_SUNM "103" // Client requesting a search using Username
#define STT_CLT_RCV_SUGU "104" // Client requesting a search using GUID
#define STT_CLT_RCV_LSTM "105" // Client requesting the account's Messages list ordered by last recived
#define STT_CLT_RCV_LSTF "106" // Client requesting the account's Friends list ordered by name (Future feature: Most active with)
#define STT_CLT_RCV_LSTB "107" // Client requesting the account's Blocked list ordered by name
#define STT_CLT_RCV_LSTS "108" // Client requesting the account's Starred/Special list ordered by name (Same future feature as LSTF)
#define STT_CLT_RCV_LSTO "109" // Client requesting the account's Online friends
#define STT_CLT_RCV_LSTD "10A" // Client requesting the account's Online friends that had set themselfs to not be disturbed
#define STT_CLT_RCV_USRS "10B" // ???
#define STT_CLT_RCV_URLB "10C" // Client requesttng the removal of a  user from the account's blocked list
#define STT_CLT_RCV_URLS "10D" // Client requesting the removal of a user form the account's Starred/Special list
#define STT_CLT_RCV_URLF "10E" // Client requesting the removal of a user from the account's Friends list
#define STT_CLT_RCV_UALB "10F" // Client requesting the addition of a user in the account's blocked list
#define STT_CLT_RCV_UALS "10G" // Client requesting the addition of a user in the account's Starred/Special list
#define STT_CLT_RCV_UALF "10H" // Client requesting the addition of a user in the account's Friends list

#define STT_CLT_SND_GUID "110" // Sending a request for the client's GUID
#define STT_CLT_SND_USRN "111" // Sending a request for the client's Username
#define STT_CLT_SND_PSWD "112" // Sending a request for the client's Password
#define STT_CLT_SND_MACA "113" // Sending a request for the client's MAC Adress !! Not Applicable !!
#define STT_CLT_SND_OK "11X"   // Sending That info gathred on previosu step is OK (Correct)
#define STT_CLT_SND_NO "11Y"   // Sending That info gathred on previosu step is NO (Incorrect)

#define STT_CLT_RQST_LOGI "120" // Client Requesting to login
#define STT_CLT_RQST_LOGO "121" // Client Requesting to logout
#define STT_CLT_RQST_REGS "123" // Client Requesting to register an account.
#define STT_CLT_RQST_REMV "124" // Client Requesting to register an account.

#endif