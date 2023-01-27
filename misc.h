#include "_Imports.h"
#ifndef MISC_H
#define MISC_H

typedef struct tm TM;
TM GT();

/// @brief Gets The Size of the Message To send in a 4 Byte String.
/// @param string Message.
/// @param Re_Size Size Returned in form of a string.
void FByteSize(char *string, char *Re_Size);

/// @brief Gets the Size thats written in a form of Bytes Into an Int
/// @param FBSize Size on string.
/// @return Size in int.
int FBSizeToInt(char *FBSize);

void tprintf(char *string);
void tsprintf(char *string);
void teprintf(char *string);

/// @brief Check if res is a Negative Number. ( < 0 )
/// @param res Result
/// @param MsgIfErr Messeg to Be Displayed if an error is encountered.
void checkerr(int res, char *MsgIfErr);

void fscan(char *string);

#endif
