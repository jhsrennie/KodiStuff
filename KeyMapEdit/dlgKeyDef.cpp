//**********************************************************************
// CDlgKeyDef
// =========
// About dialog box
//**********************************************************************

#ifndef STRICT
#define STRICT
#endif

#include <windows.h>
#include <stdio.h>
#include "KeyMapEdit.h"
#include "dlgKeyDef.h"
#include "resource.h"


//**********************************************************************
// Some function prototypes
//**********************************************************************

BOOL CALLBACK CDlgKeyDefProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);


//**********************************************************************
// CDlgKeyDef
// ----------
//**********************************************************************

CDlgKeyDef::CDlgKeyDef(void)
{
  strcpy_s(m_Title, 256, "");
}


//**********************************************************************
// CDlgKeyDef::SetTitle
// --------------------
// Set the dialog title e.g. "Append key definition" or
// "Edit key definition"
//**********************************************************************

BOOL CDlgKeyDef::SetTitle(const char* Title)
{
  strcpy_s(m_Title, 256, Title);
  return TRUE;
}


//**********************************************************************
// DoModal
// -------
// Returns FALSE if cancelled, TRUE if OK'd
//**********************************************************************

BOOL CDlgKeyDef::DoModal(HINSTANCE hInstance, HWND hWnd)
{ int i;

  m_hInstance = hInstance;

  i = DialogBoxParam(hInstance, "dlgKeyDef", hWnd, (DLGPROC) CDlgKeyDefProc, (LPARAM) this);

  if (i == 0)
    return FALSE;
  else
    return TRUE;
}


//**********************************************************************
// CDlgKeyDef::OnInit
// -----------------
// Initialise the dialog box
//**********************************************************************

BOOL CDlgKeyDef::OnInit(HWND hDlg)
{ int cursel, keycode, i;
  char s[256];

// Save the dialog handle

  m_hDlg = hDlg;

// Set the dialog title

  SetWindowText(m_hDlg, m_Title);

// Add key names to the list and select the key in m_KeyDef

  cursel = 0;

  if (m_KeyDef.m_KeyCode >= 0 && m_KeyDef.m_KeyCode < NUM_KEYNAMES)
    keycode = KeyName[m_KeyDef.m_KeyCode].keycode;
  else
    keycode = 0;

  for (i = 0; i < NUM_KEYNAMES; i++)
  { SendDlgItemMessage(m_hDlg, IDD_KEYDEF_KEY, CB_ADDSTRING, 0, (LPARAM) KeyName[i].keyname);
    if (KeyName[i].keycode == keycode)
      cursel = i;
  }

  SendDlgItemMessage(m_hDlg, IDD_KEYDEF_KEY, CB_SETCURSEL, cursel, 0);

// Add action names to the list and select the action in m_KeyDef

  for (i = 0; i < NUM_ACTIONS; i++)
    SendDlgItemMessage(m_hDlg, IDD_KEYDEF_ACTION, CB_ADDSTRING, 0, (LPARAM) Action[i]);

  SetDlgItemText(m_hDlg, IDD_KEYDEF_ACTION, m_KeyDef.m_Action);

// Set the key ID if the key code is zero

  SendDlgItemMessage(m_hDlg, IDD_COMMENT_COMMENT, EM_SETLIMITTEXT, 15, 0);

  if (m_KeyDef.m_KeyCode == 0)
  { sprintf_s(s, 256, "%i", m_KeyDef.m_KeyID);
    SetDlgItemText(m_hDlg, IDD_KEYDEF_ID, s);
  }

// Set the flags

  if (m_KeyDef.m_Ctrl)
    CheckDlgButton(m_hDlg, IDD_KEYDEF_CTRL, BST_CHECKED);

  if (m_KeyDef.m_Shift)
    CheckDlgButton(m_hDlg, IDD_KEYDEF_SHIFT, BST_CHECKED);

  if (m_KeyDef.m_Alt)
    CheckDlgButton(m_hDlg, IDD_KEYDEF_ALT, BST_CHECKED);

  if (m_KeyDef.m_Win)
    CheckDlgButton(m_hDlg, IDD_KEYDEF_WIN, BST_CHECKED);

// Return indicating success

  return TRUE;
}


//**********************************************************************
// CDlgKeyDef::OnOK
// ---------------
// OK button pressed.
// Return TRUE to allow closure, FALSE to prevent box closing.
//**********************************************************************

BOOL CDlgKeyDef::OnOK(void)
{ int i;
  char keyid[16]; // max length of IDD_KEYDEF_ID is 15

// Get the selected key name

  i = SendDlgItemMessage(m_hDlg, IDD_KEYDEF_KEY, CB_GETCURSEL, 0, 0);
  if (i == CB_ERR)
    return FALSE;
  m_KeyDef.m_KeyCode = i;

// If the key code is zero, i.e. <key id="">, get the ID

  if (m_KeyDef.m_KeyCode != 0)
  { m_KeyDef.m_KeyID = -1;
  }
  else
  { GetDlgItemText(m_hDlg, IDD_KEYDEF_ID, keyid, 15);
    if (!strtoint(keyid, &i))
    { winprintf("The key id, \"%s\", is not a valid integer", keyid);
      return FALSE;
    }
    if (i < 0)
    { winprintf("The key id, \"%d\", must be greater than zero", i);
      return FALSE;
    }
    m_KeyDef.m_KeyID = i;
  }

// Get the action. We just read the text and return it verbatim.

  GetDlgItemText(m_hDlg, IDD_KEYDEF_ACTION, m_KeyDef.m_Action, MAX_LENKEYDEFACTION);

// Get the flags

  if (IsDlgButtonChecked(m_hDlg, IDD_KEYDEF_CTRL) == BST_CHECKED)
    m_KeyDef.m_Ctrl = TRUE;
  else
    m_KeyDef.m_Ctrl = FALSE;

  if (IsDlgButtonChecked(m_hDlg, IDD_KEYDEF_SHIFT) == BST_CHECKED)
    m_KeyDef.m_Shift = TRUE;
  else
    m_KeyDef.m_Shift = FALSE;

  if (IsDlgButtonChecked(m_hDlg, IDD_KEYDEF_ALT) == BST_CHECKED)
    m_KeyDef.m_Alt = TRUE;
  else
    m_KeyDef.m_Alt = FALSE;

  if (IsDlgButtonChecked(m_hDlg, IDD_KEYDEF_WIN) == BST_CHECKED)
    m_KeyDef.m_Win = TRUE;
  else
    m_KeyDef.m_Win = FALSE;

// Return indicating success

  return TRUE;
}


//**********************************************************************
// CDlgKeyDef::OnCancel
// -------------------
// Cancel button pressed.
// Return TRUE to allow closure, FALSE to prevent box closing.
//**********************************************************************

BOOL CDlgKeyDef::OnCancel(void)
{
  return TRUE;
}


//**********************************************************************
// CDlgKeyDefProc
// -------------
// Dialog box message handler
//**********************************************************************

BOOL CALLBACK CDlgKeyDefProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{ CDlgKeyDef* us;

  switch (message)
  { case WM_INITDIALOG:
      us = (CDlgKeyDef*) lParam;
      SetWindowLong(hDlg, DWL_USER, (LONG) us);
      us->OnInit(hDlg);
      return TRUE;

    case WM_COMMAND:
      us = (CDlgKeyDef*) GetWindowLong(hDlg, DWL_USER);

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


