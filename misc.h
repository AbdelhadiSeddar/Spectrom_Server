#ifndef MISC_H
#define MISC_H

extern void RESET_THREAD(void);

extern int snd(int sockfd, void *buf, size_t len, int flags);
extern int rcv(int *sockfd, void *buf, size_t len, int flags);

typedef struct tm TM;
extern TM GT();

/// @brief Gets The Size of the Message To send in a 4 Byte String.
/// @param string Message.
/// @param Re_Size Size Returned in form of a string.
extern void FByteSize(char *string, char *Re_Size);

/// @brief Gets the Size thats written in a form of Bytes Into an Int
/// @param FBSize Size on string.
/// @return Size in int.
extern int FBSizeToInt(char *FBSize);
#define StringToInt(StringInt) FBSizeToInt(StringInt)

extern void tprint();
extern void tprintf(char *string);
extern void teprintf(char *string);
extern void tcprintf(char *string);

extern void twprinw(WINDOW *WIN);
extern void tsprint(char *dest);
extern void tprintw(char *string);
extern void tcprintw(char *string);

/// @brief Check if res is a Negative Number. ( < 0 )
/// @param res Result
/// @param MsgIfErr Messeg to Be Displayed if an error is encountered.
extern void checkerr(int res, char *MsgIfErr);

/// @brief Lower case a string
/// @param res Resulting String
/// @param str Original String
extern void strtolower(char *res, const char *str);
/// @brief Lower case a string
/// @param strtolow String to Lowercase
extern void strtolower_s(char *strtolow);

extern char *r_newline(char *str);

extern void fscan(char *string);

extern int strcmpi(const char *str1, const char *str2);

/// @brief Checks if a Char is an allowed Character
/// @param c Character to check
/// @return  1 => Allowed Char |[]| 0 => Non-Allowed Char
extern int IsInAllowedChars(char c);
/// @brief Checks if a Char represents a number
/// @param c Character to check
/// @return 1 => valid Number |[]| 0 => Not a valid Number
extern int IsANumber(char c);
/// @brief Checks if a Char is a valid Character
/// @param c Character to check
/// @return  1 => valid Char |[]| 0 => Not a valid Char
extern int IsValidChar(char c);


#endif
