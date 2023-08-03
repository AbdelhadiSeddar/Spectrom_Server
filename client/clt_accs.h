#ifndef CLT_ACCS_H

#define CLT_ACCS_H

/////////////////////////////////////   Checks  /////////////////////////////////////

/// @brief Check Client's Username.
/// @param Username
/// @param ID ** Return ID IF Existant
/// @return  0 => Existant |[]| 1 => Non-Existant
extern int clt_check_usrnm(char *Username, int *ID);

/// @brief Check  Username's password.
/// @param Username
/// @param Password
/// @return  0 => Valid |[]| 1 => Non-Valid
extern int clt_check_pswd(char *Username, char *Password);

/// @brief Check Client's Username.
/// @param Username ** Return The Username IF Existant
/// @param ID
/// @return  0 => Existant |[]| 1 => Non-Existant
extern int clt_check_id(int ID, char *Username);

/// @brief Full Check on W/ Username + Password.
/// @param Username
/// @param Password
/// @param ID ** Return ID IF Existant
/// @return -1 => Wrong Un |[]|  0 => Existant |[]| 1 => Wrong Pw
extern int clt_check(int sock, char *Username, char *Password, int *ID);

#endif