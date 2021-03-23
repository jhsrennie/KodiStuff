//**********************************************************************
// CDlgAbout
// =========
// About dialog box
//**********************************************************************

#ifndef STRICT
#define STRICT
#endif

#include <windows.h>
#include "dlgAbout.h"
#include "resource.h"


//**********************************************************************
// Some function prototypes
//**********************************************************************

BOOL CALLBACK CDlgAboutProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);


//**********************************************************************
// CDlgAbout
// ----------
//**********************************************************************

CDlgAbout::CDlgAbout(void)
{
}


CDlgAbout::~CDlgAbout(void)
{
}


//**********************************************************************
// DoModal
// -------
// Returns FALSE if cancelled, TRUE if OK'd
//**********************************************************************

BOOL CDlgAbout::DoModal(HINSTANCE hInstance, HWND hWnd)
{ int i;

  m_hInstance = hInstance;

  i = DialogBoxParam(hInstance, "dlgAbout", hWnd, (DLGPROC) CDlgAboutProc, (LPARAM) this);

  if (i == 0)
    return(FALSE);
  else
    return(TRUE);
}


//**********************************************************************
// CDlgAbout::OnInit
// -----------------
// Initialise the dialog box
//**********************************************************************

BOOL CDlgAbout::OnInit(HWND hDlg)
{

// Save the dialog handle

  m_hDlg = hDlg;

  return(TRUE);
}


//**********************************************************************
// CDlgAbout::OnOK
// ---------------
// OK button pressed.
// Return TRUE to allow closure, FALSE to prevent box closing.
//**********************************************************************

BOOL CDlgAbout::OnOK(void)
{
  return(TRUE);
}


//**********************************************************************
// CDlgAbout::OnCancel
// -------------------
// Cancel button pressed.
// Return TRUE to allow closure, FALSE to prevent box closing.
//**********************************************************************

BOOL CDlgAbout::OnCancel(void)
{
  return(TRUE);
}


//**********************************************************************
// CDlgAboutProc
// -------------
// Dialog box message handler
//**********************************************************************

BOOL CALLBACK CDlgAboutProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{ CDlgAbout* us;

  switch (message)
  { case WM_INITDIALOG:
      us = (CDlgAbout*) lParam;
      SetWindowLong(hDlg, DWL_USER, (LONG) us);
      us->OnInit(hDlg);
      return(TRUE);

    case WM_COMMAND:
      us = (CDlgAbout*) GetWindowLong(hDlg, DWL_USER);

      switch (LOWORD(wParam))
      { case IDCANCEL:
          if (us->OnCancel())
            EndDialog(hDlg, FALSE);
          return(TRUE);

        case IDOK:
          if (us->OnOK())
            EndDialog(hDlg, TRUE);
          return(TRUE);
      }
      break;
  }
  return(FALSE);
}


