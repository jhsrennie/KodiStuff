//**********************************************************************
// CDlgSection
// =========
// About dialog box
//**********************************************************************

#ifndef STRICT
#define STRICT
#endif

#include <windows.h>
#include "dlgSection.h"
#include "resource.h"


//**********************************************************************
// Some function prototypes
//**********************************************************************

BOOL CALLBACK CDlgSectionProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);


//**********************************************************************
// CDlgSection
// ----------
//**********************************************************************

CDlgSection::CDlgSection(void)
{ int i;

  for (i = 0; i < NUM_SECTIONNAMES; i++)
    m_ShowSection[i] = 1;

  strcpy_s(m_Title, 256, "");
}


//**********************************************************************
// CDlgSection::SetTitle
// --------------------
// Set the dialog title e.g. "Append key definition" or
// "Edit key definition"
//**********************************************************************

BOOL CDlgSection::SetTitle(const char* Title)
{
  strcpy_s(m_Title, 256, Title);
  return TRUE;
}


//**********************************************************************
// DoModal
// -------
// Returns FALSE if cancelled, TRUE if OK'd
//**********************************************************************

BOOL CDlgSection::DoModal(HINSTANCE hInstance, HWND hWnd)
{ int i;

  m_hInstance = hInstance;

  i = DialogBoxParam(hInstance, "dlgSection", hWnd, (DLGPROC) CDlgSectionProc, (LPARAM) this);

  if (i == 0)
    return FALSE;
  else
    return TRUE;
}


//**********************************************************************
// CDlgSection::OnInit
// -----------------
// Initialise the dialog box
//**********************************************************************

BOOL CDlgSection::OnInit(HWND hDlg)
{ int i;

// Save the dialog handle

  m_hDlg = hDlg;

// Set the dialog title

  SetWindowText(m_hDlg, m_Title);

// Add section names to the list if the corresponding m_ShowSection value
// is non-zero.

  for (i = 0; i < NUM_SECTIONNAMES; i++)
    if (m_ShowSection[i] != 0)
      SendDlgItemMessage(m_hDlg, IDD_SECTION_SECTION, CB_ADDSTRING, 0, (LPARAM) SectionName[i]);

  SendDlgItemMessage(m_hDlg, IDD_SECTION_SECTION, CB_SETCURSEL, 0, 0);

// Return indicating success

  return TRUE;
}


//**********************************************************************
// CDlgSection::OnOK
// ---------------
// OK button pressed.
// Return TRUE to allow closure, FALSE to prevent box closing.
//**********************************************************************

BOOL CDlgSection::OnOK(void)
{ int i;
  char section[MAX_LENKEYMAPSECTIONNAME+1];

// Get the selected section name

  i = SendDlgItemMessage(m_hDlg, IDD_SECTION_SECTION, CB_GETCURSEL, 0, 0);
  if (i == CB_ERR)
    return FALSE;

  SendDlgItemMessage(m_hDlg, IDD_SECTION_SECTION, CB_GETLBTEXT, (WPARAM) i, (LPARAM) section);
  m_Section.SetSection(section);

// Return indicating success

  return TRUE;
}


//**********************************************************************
// CDlgSection::OnCancel
// -------------------
// Cancel button pressed.
// Return TRUE to allow closure, FALSE to prevent box closing.
//**********************************************************************

BOOL CDlgSection::OnCancel(void)
{
  return TRUE;
}


//**********************************************************************
// CDlgSectionProc
// -------------
// Dialog box message handler
//**********************************************************************

BOOL CALLBACK CDlgSectionProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{ CDlgSection* us;

  switch (message)
  { case WM_INITDIALOG:
      us = (CDlgSection*) lParam;
      SetWindowLong(hDlg, DWL_USER, (LONG) us);
      us->OnInit(hDlg);
      return TRUE;

    case WM_COMMAND:
      us = (CDlgSection*) GetWindowLong(hDlg, DWL_USER);

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


