#ifndef MISC_H
#define MISC_H

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

extern void tprint();
extern void tprintf(char *string);
extern void teprintf(char *string);
extern void tcprintf(char *string);

extern void twprint();
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

/// @brief Check Client's Username.
/// @param Username ** Return The Username IF Existant
/// @param ID
/// @return  1 => Allowed Char |[]| 0 => Non-Allowed Char
int IsInAllowedChars(char c);

#endif
