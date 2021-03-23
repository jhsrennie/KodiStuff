//**********************************************************************
// CDlgComment
// =========
// About dialog box
//**********************************************************************

#ifndef STRICT
#define STRICT
#endif

#include <windows.h>
#include "dlgComment.h"
#include "resource.h"


//**********************************************************************
// Some function prototypes
//**********************************************************************

BOOL CALLBACK CDlgCommentProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);


//**********************************************************************
// CDlgComment
// ----------
//**********************************************************************

CDlgComment::CDlgComment(void)
{
  m_Comment.SetComment("");
  strcpy_s(m_Title, 256, "");
}


CDlgComment::~CDlgComment(void)
{
}


//**********************************************************************
// CDlgComment::SetTitle
// --------------------
// Set the dialog title e.g. "Append key definition" or
// "Edit key definition"
//**********************************************************************

BOOL CDlgComment::SetTitle(const char* Title)
{
  strcpy_s(m_Title, 256, Title);
  return TRUE;
}


//**********************************************************************
// DoModal
// -------
// Returns FALSE if cancelled, TRUE if OK'd
//**********************************************************************

BOOL CDlgComment::DoModal(HINSTANCE hInstance, HWND hWnd)
{ int i;

  m_hInstance = hInstance;

  i = DialogBoxParam(hInstance, "dlgComment", hWnd, (DLGPROC) CDlgCommentProc, (LPARAM) this);

  if (i == 0)
    return FALSE;
  else
    return TRUE;
}


//**********************************************************************
// CDlgComment::OnInit
// -----------------
// Initialise the dialog box
//**********************************************************************

BOOL CDlgComment::OnInit(HWND hDlg)
{

// Save the dialog handle

  m_hDlg = hDlg;

// Set the dialog title and comment text

  SetWindowText(m_hDlg, m_Title);

  SendDlgItemMessage(m_hDlg, IDD_COMMENT_COMMENT, EM_SETLIMITTEXT, MAX_LENKEYMAPCOMMENT, 0);
  SetDlgItemText(m_hDlg, IDD_COMMENT_COMMENT, m_Comment.m_Comment);

// Return indicating success

  return TRUE;
}


//**********************************************************************
// CDlgComment::OnOK
// ---------------
// OK button pressed.
// Return TRUE to allow closure, FALSE to prevent box closing.
//**********************************************************************

BOOL CDlgComment::OnOK(void)
{

// Get the comment text

  GetDlgItemText(m_hDlg, IDD_COMMENT_COMMENT, m_Comment.m_Comment, MAX_LENKEYMAPCOMMENT);

// Return indicating success

  return TRUE;
}


//**********************************************************************
// CDlgComment::OnCancel
// -------------------
// Cancel button pressed.
// Return TRUE to allow closure, FALSE to prevent box closing.
//**********************************************************************

BOOL CDlgComment::OnCancel(void)
{
  return TRUE;
}


//**********************************************************************
// CDlgCommentProc
// -------------
// Dialog box message handler
//**********************************************************************

BOOL CALLBACK CDlgCommentProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{ CDlgComment* us;

  switch (message)
  { case WM_INITDIALOG:
      us = (CDlgComment*) lParam;
      SetWindowLong(hDlg, DWL_USER, (LONG) us);
      us->OnInit(hDlg);
      return TRUE;

    case WM_COMMAND:
      us = (CDlgComment*) GetWindowLong(hDlg, DWL_USER);

      switch (LOWORD(wParam))
      { case IDCANCEL:
          if (us->OnCancel())
            EndDialog(hDlg, FALSE);
          return TRUE;

        case IDOK:
          if (us->OnOK())
            EndDialog(hDlg, TRUE);
          return TRUE;
      }
      break;
  }
  return FALSE;
}


