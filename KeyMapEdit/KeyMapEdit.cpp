//*********************************************************************
// Basic Windows application
//*********************************************************************

#ifndef STRICT
#define STRICT
#endif

#include <windows.h>
#include <stdio.h>
#include <stdarg.h>
#include "KeyMapEdit.h"
#include "CMainWnd.h"
#include "resource.h"


//*********************************************************************
// Prototypes
//*********************************************************************

static BOOL InitInstance(HINSTANCE, LPSTR, int);


//*********************************************************************
// Global variables
//*********************************************************************

HINSTANCE   hMainInst;
CRhsMainWnd MainWnd;

HACCEL hKMAccel = NULL;


//*********************************************************************
// Entry point from Windows supervisor
//*********************************************************************

int PASCAL WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{ MSG msg;
  HWND hWnd;

// If a previous instance is running re-activate it and exit

  if ((hWnd = FindWindow(String_IDS_MAINCLASSNAME, NULL)))
  { hWnd = GetLastActivePopup(hWnd);
    if (IsIconic(hWnd))
      ShowWindow(hWnd, SW_RESTORE);
    BringWindowToTop(hWnd);
    SetForegroundWindow(hWnd);
    return(0);
  }

// Initialise application

  if (!InitInstance(hInstance, lpCmdLine, nCmdShow))
    return(0);

// Enter message loop

  while (GetMessage(&msg, NULL, 0, 0))
  { // Give the main window a chance to detect the keypress if it wants to
    MainWnd.DetectKey(&msg);

    if (!TranslateAccelerator(MainWnd.hWnd(), hKMAccel, &msg))
    { TranslateMessage(&msg);
      DispatchMessage(&msg);
    }
  }

  return(msg.wParam);
}


//*********************************************************************
// Instance initialisation routine
//*********************************************************************

static BOOL InitInstance(HINSTANCE hInstance, LPSTR lpCmdLine, int nCmdShow)
{

  hMainInst = hInstance;

// Create the main window

  if (!MainWnd.Open(hInstance, String_IDS_TITLE, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, lpCmdLine))
  { winprintf("Cannot create main window");
    return(FALSE);
  }

// Load the accelerator

  hKMAccel = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDA_MAIN));

  return(TRUE);
}


//*********************************************************************
// winprintf
// ---------
//*********************************************************************

int winprintf(const char *Format, ...)
{ char s[256];
  va_list ap;

  va_start(ap, Format);
  vsprintf_s(s, 256, Format, ap);
  va_end(ap);

  return(MessageBox(GetFocus(), s, String_IDS_TITLE, MB_OK | MB_ICONEXCLAMATION));
}


int winprintfYesNo(const char *Format, ...)
{ char s[256];
  va_list ap;

  va_start(ap, Format);
  vsprintf_s(s, 256, Format, ap);
  va_end(ap);

  return(MessageBox(GetFocus(), s, "KeyMapEdit", MB_YESNO | MB_ICONEXCLAMATION));
}


int winprintfYesNoCancel(const char *Format, ...)
{ char s[256];
  va_list ap;

  va_start(ap, Format);
  vsprintf_s(s, 256, Format, ap);
  va_end(ap);

  return(MessageBox(GetFocus(), s, "KeyMapEdit", MB_YESNOCANCEL | MB_ICONEXCLAMATION));
}


//**********************************************************************
// strtoint
// --------
// Convert string to int
//**********************************************************************

BOOL strtoint(const char* s, int* i)
{ const char* start;
  char* end;

  for (start = s; *start == ' ' || *start == '\t'; start++);
  *i = (int) strtol(start, &end, 10);

  return(end > start ? TRUE : FALSE);
}


//**********************************************************************
// GetLastErrorMessage
// -------------------
// Return a string describing the last Win32 error
//**********************************************************************

const char* GetLastErrorMessage(void)
{ DWORD d;
  static char errmsg[512];

  d = GetLastError();

  strcpy_s(errmsg, 512, "<unknown error>");
  FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM, 0, d, 0, errmsg, 511, NULL);
  return(errmsg);
}


