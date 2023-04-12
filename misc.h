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
extern void tsprintf(char *string);
extern void teprintf(char *string);
extern void tcprintf(char *string);

/// @brief Check if res is a Negative Number. ( < 0 )
/// @param res Result
/// @param MsgIfErr Messeg to Be Displayed if an error is encountered.
extern void checkerr(int res, char *MsgIfErr);

/// @brief Lower case a string
/// @param res Resulting String 
/// @param str Original String
extern void strtolower(char* res,const char* str);
/// @brief Lower case a string
/// @param strtolow String to Lowercase
extern void strtolower_s(char* strtolow);

extern char* r_newline(char* str);

extern void fscan(char *string);

extern int strcmpi (const char * str1, const char * str2 );





typedef char* COLOR;
//Regular text
#define R_BLK "\e[0;30m"
#define R_RED "\e[0;31m"
#define R_GRN "\e[0;32m"
#define R_YEL "\e[0;33m"
#define R_BLU "\e[0;34m"
#define R_MAG "\e[0;35m"
#define R_CYN "\e[0;36m"
#define R_WHT "\e[0;37m"

//Regular bold text
#define B_BLK "\e[1;30m"
#define B_RED "\e[1;31m"
#define B_GRN "\e[1;32m"
#define B_YEL "\e[1;33m"
#define B_BLU "\e[1;34m"
#define B_MAG "\e[1;35m"
#define B_CYN "\e[1;36m"
#define B_WHT "\e[1;37m"

//Regular underline text
#define U_BLK "\e[4;30m"
#define U_RED "\e[4;31m"
#define U_GRN "\e[4;32m"
#define U_YEL "\e[4;33m"
#define U_BLU "\e[4;34m"
#define U_MAG "\e[4;35m"
#define U_CYN "\e[4;36m"
#define U_WHT "\e[4;37m"

//Regular background
#define BCK_BLK "\e[40m"
#define BCK_RED "\e[41m"
#define BCK_GRN "\e[42m"
#define BCK_YEL "\e[43m"
#define BCK_BLU "\e[44m"
#define BCK_MAG "\e[45m"
#define BCK_CYN "\e[46m"
#define BCK_WHT "\e[47m"

//High intensty background 
#define HBCK_BLK "\e[0;100m"
#define HBCK_RED "\e[0;101m"
#define HBCK_GRN "\e[0;102m"
#define HBCK_YEL "\e[0;103m"
#define HBCK_BLU "\e[0;104m"
#define HBCK_MAG "\e[0;105m"
#define HBCK_CYN "\e[0;106m"
#define HBCK_WHT "\e[0;107m"

//High intensty text
#define H_BLK "\e[0;90m"
#define H_RED "\e[0;91m"
#define H_GRN "\e[0;92m"
#define H_YEL "\e[0;93m"
#define H_BLU "\e[0;94m"
#define H_MAG "\e[0;95m"
#define H_CYN "\e[0;96m"
#define H_WHT "\e[0;97m"

//Bold high intensity text
#define B_HBLK "\e[1;90m"
#define B_HRED "\e[1;91m"
#define B_HGRN "\e[1;92m"
#define B_HYEL "\e[1;93m"
#define B_HBLU "\e[1;94m"
#define B_HMAG "\e[1;95m"
#define B_HCYN "\e[1;96m"
#define B_HWHT "\e[1;97m"

//Reset
#define reset "\e[0m"
#define CRESET "\e[0m"
#define COLOR_RESET "\e[0m"

extern void ChangeColor(COLOR Color);

#endif
