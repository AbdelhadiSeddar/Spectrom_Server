#ifndef ALERTBOX_H
#define ALERTBOX_H

typedef enum alertbox_t
{
    Confirm,
    Info,
    InfoTitled,
    HelpNotFound
} alertbox_type;

/// @brief Shows an "AlertBox" Which shows a sceparate window than TARGET_WIN Used to get input from User but without modifying TARGET_WIN.
/// @param type Currently There are 2 Types [ Confirm ( Shows Ok or Cancel ) | Info ( Shows Ok )]
/// @param 2ndArgument Used Currently for "Info", and is supposed to hold the Inner text value.
/// @return Depending on Type [ Confirm ( Shows Ok or Cancel and returns 1 or 0 respectively) | Info ( Shows Ok and retuns 1 )]
extern int alertbox(alertbox_type type, ...);

#endif