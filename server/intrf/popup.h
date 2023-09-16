#ifndef POPUP_H
#define POPUP_H

extern int __POPUP_STATUS;

#define __POPUP_STATUS_NONE 0
#define __POPUP_STATUS_ERR -1
#define __POPUP_STATUS_INFO 1

#define __POPUP_ERR_CODE_EMPT 0
#define __POPUP_ERR_CODE_INVALID 1
#define __POPUP_ERR_CODE_MISSING_ARG 2
#define __POPUP_ERR_CODE_INVALID_ARG 3
#define __POPUP_ERR_CODE_INVALID_PATH 4

#define __POPUP_INFO_CODE_SUCCESS 0
#define __POPUP_INFO_CODE_LOGWRITTEN 1
#define __POPUP_INFO_CODE_CLEARED 2

extern int DefinePopup(int POPUP_STATUS, int POPUP_CODE, ...);
extern void create_POPUP_WIN(int __POPUP_TYPE);

#define DefineError(ERROR_CODE, ...) DefinePopup(__POPUP_STATUS_ERR, ERROR_CODE, ##__VA_ARGS__)
#define DefineInfo(INFO_CODE, ...) DefinePopup(__POPUP_STATUS_INFO, INFO_CODE, ##__VA_ARGS__)

#define create_POPUP_WIN_ERR() create_POPUP_WIN(__POPUP_STATUS_ERR)
#define create_POPUP_WIN_INFO() create_POPUP_WIN(__POPUP_STATUS_INFO)

extern int ShowPopup();
extern void HidePopup();

#endif