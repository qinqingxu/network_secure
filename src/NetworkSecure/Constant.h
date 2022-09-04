#pragma once
#ifndef CONSTATNT_H_FILE
#define CONSTATNT_H_FILE

const char G_VERSION[] = "1.0.1";
const char G_VERSION_CHECK_URL[] = "https://raw.githubusercontent.com/qinqingxu/network_secure/main/version.txt";

const int G_SPLASH_CLOSE_TIMER_ID = 2;
const int G_SPLASH_CLOSE_DURATION = 2000;
const int G_DIALOG_CLOSE_SUCCESS = 0;
const int G_DIALOG_CLOSE_NEED_TO_UPGRADE = 999;

const int G_AUTOSTART_TIMER_ID = 2;
const int G_AUTOSTART_TIME = 1000;

const int G_SCAN_TIMER_ID = 999;

enum LogSeverity
{
	LOG_INFO = 1,
	LOG_WARNING,
	LOG_SUCCESS
};

const COLORREF COLOR_INFO = RGB(128, 128, 128);//Gray
const COLORREF COLOR_WARNING = RGB(128, 0, 0);//Red
const COLORREF COLOR_SUCCESS = RGB(0, 128, 0);//Green

static const char* G_JSON_CONFIG_FILE_NAME = "config.json";


#define NOTIFYICON_TRY WM_USER + 100
const CHAR g_strWindowTitle[] = _T("Network Secure");
const CHAR g_strLaunch[] = _T("Started");
const CHAR g_strISPWarning[] = _T("Your ISP is invalid");
const UINT WM_TASKBARCREATED = ::RegisterWindowMessage(_T("TaskbarCreated"));


#endif
	