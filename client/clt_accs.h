#ifndef CLT_ACCS_H
#include "clt_defs.h"
#define CLT_ACCS_H

/////////////////////////////////////   Checks  /////////////////////////////////////

//Check Username
// Returns:
// 0 -> Existant
// 1 -> Non-existant
// Note: You can store the username's ID in
// the second parameter else just put NULL
extern int clt_check_usrnm(char* Username, int* ID);

//Check Password
// Returns:
// -1-> Username Non-existant
// 0 -> Correct
// 1 -> Non-existant
extern int clt_check_pswd(char* Username, char* Password);

//Check For ID existance
// Returns:
// 0 -> Existant
// 1 -> Non-existant
// Note: You can store the ID's username in
// the second parameter else just put NULL
extern int clt_check_id(int ID, char* Username);

//Full check on command
// Returns:
// -1-> Fail || Username
// 0 -> Succes
// 1 -> Fail || Password
// Note: You can store the username's ID in
// the third parameter else just put NULL
extern int clt_check(int sock, char* Username, char* Password, int* ID);


/////////////////////////////////////   Logging /////////////////////////////////////



extern int clt_log_in(int Index, char* Username, int ID, char* UUID);
extern int clt_log_out(int Index);

/////////////////////////////////////   




#endif