//**********************************************************************
// CRhsMainWnd
// ===========
// Implemntation of main window
//**********************************************************************

#ifndef STRICT
#define STRICT
#endif

#include <windows.h>
#include "KeyMapEdit.h"
#include "CMainWnd.h"
#include "CKeymapControl.h"
#include "CKeymapFile.h"
#include "CKeyDetector.h"
#include "dlgKeyDef.h"
#include "dlgSection.h"
#include "dlgComment.h"
#include "dlgAbout.h"
#include "rhsfont.h"
#include "rhsreg.h"
#include "resource.h"


//**********************************************************************
// Function prototypes
//**********************************************************************

long CALLBACK CRhsMainWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);


//**********************************************************************
// CRhsMainWnd::CRhsMainWnd
// ------------------------
//**********************************************************************

CRhsMainWnd::CRhsMainWnd(void)
{
  m_hInstance = NULL;
  m_hWnd      = NULL;
  m_Registry  = NULL;

  m_KeyDetectOn = FALSE;

  strcpy_s(m_FileName, MAX_PATH+1, "");
  m_HasChanged = FALSE;
}


CRhsMainWnd::~CRhsMainWnd(void)
{
  if (m_hWnd)
    DestroyWindow(m_hWnd);

  if (m_Registry)
    delete m_Registry;
}


//**********************************************************************
// CRhsMainWnd::Open
// -----------------
//**********************************************************************

BOOL CRhsMainWnd::Open(HINSTANCE hInstance, char* Title, int Left, int Top, int Width, int Depth, char* lpCmdLine)
{ WNDCLASSEX wce;
  WNDCLASS wc;
  RECT r;
  CRhsFont font;

// If the window has already been opened then just resize it

  if (m_hWnd)
  { MoveWindow(m_hWnd, Left, Top, Width, Depth, TRUE);
    return(TRUE);
  }

// Save the instance handle

  m_hInstance = hInstance;

// Try registering using an extended class first

  wce.cbSize        = sizeof(WNDCLASSEX);
  wce.style         = 0;
  wce.lpfnWndProc   = CRhsMainWndProc;
  wce.cbClsExtra    = 0;
  wce.cbWndExtra    = 4;
  wce.hInstance     = m_hInstance;
  wce.hIcon         = LoadIcon(m_hInstance, "KeyMapEditIcon");
  wce.hCursor       = LoadCursor(NULL, IDC_ARROW);
  wce.hbrBackground = (HBRUSH) (COLOR_WINDOW + 1);
  wce.lpszMenuName  = "KeyMapEditMenu";
  wce.lpszClassName = "CRhsMainWndClass";
  wce.hIconSm       = (HICON) LoadImage(m_hInstance, "KeyMapEditIconSmall", IMAGE_ICON, 16, 16, 0);

  if (!RegisterClassEx(&wce))
  {

// If RegisterEx fails then fall back to the older form

    wc.style         = 0;
    wc.lpfnWndProc   = CRhsMainWndProc;
    wc.cbClsExtra    = 0;
    wc.cbWndExtra    = 4;
    wc.hInstance     = m_hInstance;
    wc.hIcon         = LoadIcon(m_hInstance, "KeyMapEditIcon");
    wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH) (COLOR_WINDOW + 1);
    wc.lpszMenuName  = "KeyMapEditMenu";
    wc.lpszClassName = "CRhsMainWndClass";

    RegisterClass(&wc);
  }

// Create the registry object

  m_Registry = new CRhsRegistry("Software\\Rhs\\KeyMapEdit");

// Check if default size is required

  r.left   = Left  == CW_USEDEFAULT ? m_Registry->GetInt("Left",  CW_USEDEFAULT) : Left;
  r.top    = Top   == CW_USEDEFAULT ? m_Registry->GetInt("Top",   CW_USEDEFAULT) : Top;
  r.right  = Width == CW_USEDEFAULT ? m_Registry->GetInt("Width", CW_USEDEFAULT) : Width;
  r.bottom = Depth == CW_USEDEFAULT ? m_Registry->GetInt("Depth", CW_USEDEFAULT) : Depth;

// Create the window

  m_hWnd = CreateWindow("CRhsMainWndClass",
                        Title,
                        WS_OVERLAPPEDWINDOW,
                        r.left, r.top, r.right, r.bottom,
                        NULL,
                        NULL,
                        m_hInstance,
                        NULL
                       );

  if (!m_hWnd)
  { delete m_Registry;
    m_Registry = NULL;
    return(FALSE);
  }

  FitOnScreen(TRUE, TRUE);

  ShowWindow(m_hWnd, SW_SHOWNORMAL);
  UpdateWindow(m_hWnd);

// Save our object in the parent windows extra data

  SetWindowLong(m_hWnd, 0, (LONG) this);

// Create the XML control

  m_Keymap = new CKeymapControl;

  GetClientRect(m_hWnd, &r);
  m_Keymap->Open(m_hInstance, m_hWnd, &r, IDC_KEYMAPCONTROL);

  font.ReadFont(m_Registry);
  m_Keymap->SetFont(font.LogFont());

  m_Keymap->SetFocus();

// Start with a new empty file

  OnFileNew();

// If a XML file was supplied open it

  if (strlen(lpCmdLine) > 0)
  { OpenFile(lpCmdLine);
  }

// If no file name was supplied attempt to open the local keyboard.xml

  else
  { GetEnvironmentVariable("APPDATA", m_FileName, MAX_PATH);
    strcat_s(m_FileName, MAX_PATH+1, "\\Kodi\\userdata\\keymaps\\keyboard.xml");

    if (GetFileAttributes(m_FileName) != 0xFFFFFFFF)
    { OpenFile(m_FileName);
    }

// If no keyboard.xml exists prompt to create one

    else
    { if (winprintfYesNo("There is no keyboard.xml in your userdata folder, do you wish to create one?") != IDNO)
        OnFileSave();
    }
  }

// Return indicating success

  return(TRUE);
}


//**********************************************************************
// CRhsMainWnd::OnFileNew
// ======================
// Create a new file
// Always returns 0
//**********************************************************************

long CRhsMainWnd::OnFileNew(void)
{ char s[256];

// Check if we need to save the current data

  if (AskToSave() == IDCANCEL)
    return 0;

// Create the new file

  if (!m_Keymap->NewKeymap())
    return 0;

  strcpy_s(m_FileName, MAX_PATH+1, "");
  wsprintf(s, "Untitled - %s", String_IDS_TITLE);
  SetWindowText(m_hWnd, s);

  m_HasChanged = FALSE;

// All done

  return 0;
}


//**********************************************************************
// CRhsMainWnd::OnFileOpen
// =======================
// Open a file
// Always returns 0
//**********************************************************************

long CRhsMainWnd::OnFileOpen(void)
{ int i;
  OPENFILENAME ofn;
  char filename[MAX_PATH+1], filetitle[MAX_PATH+1], xmldir[MAX_PATH+1];

// Check if we need to save the current data

  if (AskToSave() == IDCANCEL)
    return 0;

// The initial directory is %APPDATA%\XBMC\userdata\keymaps

  GetEnvironmentVariable("APPDATA", xmldir, MAX_PATH);
  strcat_s(xmldir, MAX_PATH+1, "\\Kodi\\userdata\\keymaps");

  strcpy_s(filename, MAX_PATH+1, xmldir);
  strcat_s(filename, MAX_PATH+1, "\\*.xml");

  for (i = strlen(filename) - 1; i > 0; i--)
    if (filename[i] == '\\')
      break;
  strcpy_s(filetitle, MAX_PATH+1, filename + i);

  ofn.lStructSize       = sizeof(OPENFILENAME);
  ofn.hwndOwner         = m_hWnd;
  ofn.hInstance         = m_hInstance;
  ofn.lpstrFilter       = "XML files (*.xml)\0*.xml\0All files (*.*)\0*.*\0";
  ofn.lpstrCustomFilter = NULL;
  ofn.nFilterIndex      = 1;
  ofn.lpstrFile         = filename;
  ofn.nMaxFile          = MAX_PATH;
  ofn.lpstrFileTitle    = filetitle;
  ofn.nMaxFileTitle     = MAX_PATH;
  ofn.lpstrInitialDir   = xmldir;
  ofn.lpstrTitle        = "Open XML file";
  ofn.Flags             = OFN_FILEMUSTEXIST;
  ofn.lpstrDefExt       = "xml";

  if (!GetOpenFileName(&ofn))
    return 0;

// Got the name so open the file

  OpenFile(filename);

// All done

  return 0;
}


//**********************************************************************
// CRhsMainWnd::OnFileSave
// =======================
// Save the current file
// Return 0:        File saved
//        IDCANCEL: Error saving file
//**********************************************************************

long CRhsMainWnd::OnFileSave(void)
{ CKeymapFile keymapfile;

// If there is no current file name we need to get a file name

  if (strlen(m_FileName) == 0)
    return(OnFileSaveAs());

// Save to the current file

  if (!keymapfile.SaveKeymap(m_FileName, m_Keymap))
  { winprintf("Error saving file: %s\n%s", m_FileName, keymapfile.GetLastError());
    return 0;
  }

  m_HasChanged = FALSE;

// All done

  return 0;
}


//**********************************************************************
// CRhsMainWnd::OnFileSaveAs
// =========================
// Save the current file with a new name
// Return 0:        File saved
//        IDCANCEL: Error saving file
//**********************************************************************

long CRhsMainWnd::OnFileSaveAs(void)
{ int i;
  OPENFILENAME ofn;
  CKeymapFile keymapfile;
  char filename[MAX_PATH+1], filetitle[MAX_PATH+1];

// Get the new file name

  if (strlen(m_FileName) > 0)
  { strcpy_s(filename, MAX_PATH+1, m_FileName);
  }
  else
  { GetEnvironmentVariable("APPDATA", filename, MAX_PATH);
    strcat_s(filename, MAX_PATH+1, "\\Kodi\\userdata\\keymaps\\keyboard.xml");
  }

  for (i = strlen(filename) - 1; i > 0; i--)
    if (filename[i] == '\\')
      break;
  strcpy_s(filetitle, MAX_PATH+1, filename + i);

  ofn.lStructSize       = sizeof(OPENFILENAME);
  ofn.hwndOwner         = m_hWnd;
  ofn.hInstance         = m_hInstance;
  ofn.lpstrFilter       = "XML files (*.xml)\0*.xml\0All files (*.*)\0*.*\0";
  ofn.lpstrCustomFilter = NULL;
  ofn.nFilterIndex      = 1;
  ofn.lpstrFile         = filename;
  ofn.nMaxFile          = MAX_PATH;
  ofn.lpstrFileTitle    = filetitle;
  ofn.nMaxFileTitle     = MAX_PATH;
  ofn.lpstrInitialDir   = NULL;
  ofn.lpstrTitle        = "Save XML file";
  ofn.Flags             = OFN_PATHMUSTEXIST | OFN_OVERWRITEPROMPT;
  ofn.lpstrDefExt       = "xml";

  if (!GetSaveFileName(&ofn))
    return(IDCANCEL);

// Got the name so save the file

  if (!keymapfile.SaveKeymap(filename, m_Keymap))
  { winprintf("Error saving file: %s\r\n%s", filename, keymapfile.GetLastError());
    return 0;
  }
  m_HasChanged = FALSE;

// Update the file name

  strcpy_s(m_FileName, MAX_PATH+1, filename);
  wsprintf(filename, "%s - %s", filetitle, String_IDS_TITLE);
  SetWindowText(m_hWnd, filename);

// All done

  return 0;
}


//**********************************************************************
// CRhsMainWnd::OnFileExit
// -----------------------
// User has selected the menu item File/Exit
//**********************************************************************

long CRhsMainWnd::OnFileExit(void)
{

// Check if we need to save the current data

  if (AskToSave() == IDCANCEL)
    return 0;

// Destroy the main window. This will cause the application to exit.

  DestroyWindow(m_hWnd);

  return 0;
}


//**********************************************************************
// CRhsMainWnd::OnFileAbout
// ------------------------
// User has selected the menu item File/About
//**********************************************************************

long CRhsMainWnd::OnFileAbout(void)
{
  CDlgAbout* dlg = new CDlgAbout;
  dlg->DoModal(m_hInstance, m_hWnd);
  delete dlg;

  return 0;
}


//**********************************************************************
// CRhsMainWnd::OnEditFont
// -----------------------
// User has selected the menu item Edit/Font
//**********************************************************************

long CRhsMainWnd::OnEditFont(void)
{ CRhsFont font;

  font.ReadFont(m_Registry);

  if (font.ChooseFont(m_hWnd, "Choose font"))
  { font.SaveFont(m_Registry);
    m_Keymap->SetFont(font.LogFont());
  }

  return 0;
}


//**********************************************************************
// CRhsMainWnd::OnKeymapDetect
// ---------------------------
// User has selected the menu item Keymap/Detect keypress
//**********************************************************************

long CRhsMainWnd::OnKeymapDetect(void)
{ char wintext[256];

// Check we can append a key here

  if (!m_Keymap->CanAppendKeyDef())
  { winprintf(m_Keymap->GetLastError());
    return 0;
  }

// Update the window title to show we are waiting for a keypress

  GetWindowText(m_hWnd, wintext, 255);
  strcat_s(wintext, 256, " - Waiting for keypress");
  SetWindowText(m_hWnd, wintext);

// Turn key detecting on

  m_KeyDetectOn = TRUE;

  return 0;
}


//**********************************************************************
// CRhsMainWnd::OnKeyDetected
// --------------------------
// Message sent when the key detection has detected a key
//**********************************************************************

long CRhsMainWnd::OnKeyDetected(CKeymapKeyDef* KeyDef)
{ CDlgKeyDef dlg;
  char *s;
  char wintext[256];

// Remove "Waiting for a keypress" from the Window title

  GetWindowText(m_hWnd, wintext, 255);
  s = strstr(wintext, " - Waiting for keypress");
  if (s)
  { *s = '\0';
    SetWindowText(m_hWnd, wintext);
  }

// Check we can append a key here

  if (!m_Keymap->CanAppendKeyDef())
  { winprintf(m_Keymap->GetLastError());
    return 0;
  }

// Initialise the dialog with the key we detected

  dlg.m_KeyDef.m_KeyCode = KeyDef->m_KeyCode;
  dlg.m_KeyDef.m_KeyID   = KeyDef->m_KeyID;
  dlg.m_KeyDef.m_Ctrl    = KeyDef->m_Ctrl;
  dlg.m_KeyDef.m_Shift   = KeyDef->m_Shift;
  dlg.m_KeyDef.m_Alt     = KeyDef->m_Alt;
  dlg.m_KeyDef.m_Win     = KeyDef->m_Win;

// Display the dialog

  dlg.SetTitle("Append detected key");

  if (dlg.DoModal(m_hInstance, m_hWnd))
  { if (m_Keymap->AppendKeyDef(dlg.m_KeyDef))
    { m_HasChanged = TRUE;
    }
    else
    { winprintf(m_Keymap->GetLastError());
    }
  }

  return 0;
}


//**********************************************************************
// CRhsMainWnd::OnKeymapAppendKeyDef
// ---------------------------------
// User has selected the menu item Keymap/Append keydef
//**********************************************************************

long CRhsMainWnd::OnKeymapAppendKeyDef(void)
{ CDlgKeyDef dlg;

// Check we can append a key here

  if (!m_Keymap->CanAppendKeyDef())
  { winprintf(m_Keymap->GetLastError());
    return 0;
  }

// Display the dialog

  dlg.SetTitle("Append key definition");

  if (dlg.DoModal(m_hInstance, m_hWnd))
  { if (m_Keymap->AppendKeyDef(dlg.m_KeyDef))
    { m_HasChanged = TRUE;
    }
    else
    { winprintf(m_Keymap->GetLastError());
    }
  }

  return 0;
}


//**********************************************************************
// CRhsMainWnd::OnKeymapAppendSection
// ----------------------------------
// User has selected the menu item Keymap/Append section
//**********************************************************************

long CRhsMainWnd::OnKeymapAppendSection(void)
{ int item_type, item_id, i;
  CDlgSection dlg;

// Find all the sections currently in the key map

  for (i = 0; i < NUM_SECTIONNAMES; i++)
    dlg.m_ShowSection[i] = 1;

  for (item_id = 0; ; item_id++)
  { item_type = m_Keymap->GetItemType(item_id);
    if (item_type == TYPE_NONE || item_type == TYPE_ERROR)
      break;

    if (item_type == TYPE_SECTION)
      if (m_Keymap->GetSection(dlg.m_Section, item_id))
        dlg.m_ShowSection[dlg.m_Section.m_SectionID] = 0;
  }

// Make sure we can add at least one section

  for (i = 0; i < NUM_SECTIONNAMES; i++)
    if (dlg.m_ShowSection[i] != 0)
      break;

  if (i == NUM_SECTIONNAMES)
  { winprintf("All the sections are already present so you can't add another section.");
    return FALSE;
  }

// Display the dialog

  dlg.SetTitle("Append section");

  if (dlg.DoModal(m_hInstance, m_hWnd))
    if (m_Keymap->AppendSection(dlg.m_Section))
      m_HasChanged = TRUE;

  return 0;
}


//**********************************************************************
// CRhsMainWnd::OnKeymapInsertComment
// ----------------------------------
// User has selected the menu item Keymap/Insert comment
//**********************************************************************

long CRhsMainWnd::OnKeymapInsertComment(void)
{ CDlgComment dlg;

  dlg.SetTitle("Insert comment");
  dlg.m_Comment.SetComment("");

  if (dlg.DoModal(m_hInstance, m_hWnd))
    if (m_Keymap->InsertComment(dlg.m_Comment))
      m_HasChanged = TRUE;

  return 0;
}


//**********************************************************************
// CRhsMainWnd::OnKeymapEdit
// -------------------------
// User has selected the menu item Keymap/Edit
//**********************************************************************

long CRhsMainWnd::OnKeymapEdit(void)
{ int element_id, element_type;

  element_id = m_Keymap->GetSelectedItem();
  element_type = m_Keymap->GetItemType(element_id);

// The item we are editing is a key definition

  if (element_type == TYPE_KEYDEF)
  { CDlgKeyDef dlg;

    m_Keymap->GetKeyDef(dlg.m_KeyDef, element_id);

    dlg.SetTitle("Edit key definition");

    if (dlg.DoModal(m_hInstance, m_hWnd))
      if (m_Keymap->UpdateKeyDef(dlg.m_KeyDef, element_id))
        m_HasChanged = TRUE;
  }

// The item we are editing is a section

  if (element_type == TYPE_SECTION)
  { int item_id, item_type, i;
    CDlgSection dlg;

    // Find all the sections currently in the key map
    for (i = 0; i < NUM_SECTIONNAMES; i++)
      dlg.m_ShowSection[i] = 1;

    for (item_id = 0; ; item_id++)
    { item_type = m_Keymap->GetItemType(item_id);
      if (item_type == TYPE_NONE || item_type == TYPE_ERROR)
        break;

      if (item_type == TYPE_SECTION)
        if (m_Keymap->GetSection(dlg.m_Section, item_id))
          dlg.m_ShowSection[dlg.m_Section.m_SectionID] = 0;
    }

    // Make sure we can add at least one section
    for (i = 0; i < NUM_SECTIONNAMES; i++)
      if (dlg.m_ShowSection[i] != 0)
        break;

    if (i == NUM_SECTIONNAMES)
    { winprintf("All the sections are already present so you can't change this section type.");
      return FALSE;
    }

    // Display the dialog
    m_Keymap->GetSection(dlg.m_Section, element_id);

    dlg.SetTitle("Edit section");

    if (dlg.DoModal(m_hInstance, m_hWnd))
      if (m_Keymap->UpdateSection(dlg.m_Section, element_id))
        m_HasChanged = TRUE;
  }

// The item we are editing is a comment

  if (element_type == TYPE_COMMENT)
  { CDlgComment dlg;

    m_Keymap->GetComment(dlg.m_Comment, element_id);

    dlg.SetTitle("Edit comment");

    if (dlg.DoModal(m_hInstance, m_hWnd))
      if (m_Keymap->UpdateComment(dlg.m_Comment, element_id))
        m_HasChanged = TRUE;
  }

// Finished

  return 0;
}


//**********************************************************************
// CRhsMainWnd::OnKeymapDelete
// ---------------------------
// User has selected the menu item Keymap/Edit
//**********************************************************************

long CRhsMainWnd::OnKeymapDelete(void)
{ int element_id, element_type, i;

// Get the selected item; if no item is selected do nothing

  element_id = m_Keymap->GetSelectedItem();
  if (element_id < 0)
    return 0;

// Prompt the user

  element_type = m_Keymap->GetItemType(element_id);

  if (element_type == TYPE_COMMENT)
    i = winprintfYesNo("Are you sure you want to delete the selected comment?");
  else if (element_type == TYPE_SECTION)
    i = winprintfYesNo("Are you sure you want to delete the selected section? This will remove all key definitions in the section.");
  else if (element_type == TYPE_KEYDEF)
    i = winprintfYesNo("Are you sure you want to delete the selected key definition?");
  else
    return 0;

  if (i != IDYES)
    return 0;

// Delete the item

  if (m_Keymap->DeleteItem(element_id))
    m_HasChanged = TRUE;

  return 0;
}

//**********************************************************************
// CRhsMainWnd::DetectKey
// ======================
//**********************************************************************

void CRhsMainWnd::DetectKey(MSG* Msg)
{ static CKeymapKeyDef keydef;

// If we aren't in key detection mode return immediately

  if (!m_KeyDetectOn)
  { return;
  }

// Attempt to detect the keypress

  else
  { CKeyDetector keydetector;

    if (keydetector.DetectKey(Msg, keydef))
    { m_KeyDetectOn = FALSE;
      PostMessage(m_hWnd, WM_COMMAND, IDM_KEYMAP_KEYDETECTED, (LPARAM) &keydef);
    }
  }
}


//**********************************************************************
// CRhsMainWnd::AskToSave
// ----------------------
// If the data has changed prompt the user to save the file
//**********************************************************************

int CRhsMainWnd::AskToSave(void)
{ int i;

// Save only if the file has changed

  if (!m_HasChanged)
    return(IDOK);

// Check we want to save

  i = winprintfYesNoCancel("Do you want to save the current file?");
  if (i == IDCANCEL || i == IDNO)
    return(i);

// Save the file

  i = OnFileSave();

  if (i != 0)
    return(IDCANCEL);

// Return indicating the file was saved

  return(IDOK);
}


//**********************************************************************
// CRhsMainWnd::OpenFile
// =====================
//**********************************************************************

BOOL CRhsMainWnd::OpenFile(char* FileName)
{ int i;
  CKeymapFile keymapfile;
  char s[MAX_PATH+1];

// Strip leading and trailing quotes from the filename

  if (FileName[0] == '"')
    strcpy_s(s, MAX_PATH+1, FileName+1);
  else
    strcpy_s(s, MAX_PATH+1, FileName);

  i = strlen(s);
  if (i == 0)
    return FALSE;

  if (s[i-1] == '"')
    s[i-1] = '\0';

// Got the name so open the file

  if (!keymapfile.ReadKeymap(s, m_Keymap))
  { winprintf("Error reading file: %s\n%s", s, keymapfile.GetLastError());
    return 0;
  }

// Save the file name and clear the "changed" flag

  strcpy_s(m_FileName, MAX_PATH+1, s);
  m_HasChanged = FALSE;

// Update the window title
// We just want the file name not the path

  for (i = 0; s[i] != '\0'; i++);
  while (s[--i] != '\\')
    if (i == 0)
      break;
  if (s[i] == '\\')
    i++;

  sprintf_s(s, MAX_PATH+1, "%s - %s", s + i, String_IDS_TITLE);
  SetWindowText(m_hWnd, s);

// All done

  return TRUE;
}


//**********************************************************************
// CRhsMainWnd::OnCommand
// ----------------------
// Handle WM_COMMAND messages
//**********************************************************************

long CRhsMainWnd::OnCommand(WORD wNotifyCode, WORD wID, HWND hwndCtl)
{

// Process the message

  switch (wID)
  {

// Create a new file

    case IDM_FILE_NEW:
      OnFileNew();
      return 0;

// Open a file

    case IDM_FILE_OPEN:
      OnFileOpen();
      return 0;

// Save the file

    case IDM_FILE_SAVE:
      OnFileSave();
      return 0;

// Save the file with a new name

    case IDM_FILE_SAVEAS:
      OnFileSaveAs();
      return 0;

// Exit

    case IDM_FILE_EXIT:
      OnFileExit();
      return 0;

// Set the font

    case IDM_EDIT_FONT:
      OnEditFont();
      return 0;

// Traditional about box

    case IDM_FILE_ABOUT:
      OnFileAbout();
      return 0;

// Detect a keypress

    case IDM_KEYMAP_DETECT:
      OnKeymapDetect();
      return 0;

// A keypress has been detected

    case IDM_KEYMAP_KEYDETECTED:
      OnKeyDetected((CKeymapKeyDef*) hwndCtl);
      return 0;

// Append a new key definition

    case IDM_KEYMAP_APPENDKEY:
      OnKeymapAppendKeyDef();
      return 0;

// Append a new section

    case IDM_KEYMAP_APPENDSECTION:
      OnKeymapAppendSection();
      return 0;

// Insert a new comment

    case IDM_KEYMAP_INSERTCOMMENT:
      OnKeymapInsertComment();
      return 0;

// Edit an item

    case IDM_KEYMAP_EDIT:
      OnKeymapEdit();
      return 0;

// Delete an item

    case IDM_KEYMAP_DELETE:
      OnKeymapDelete();
      return 0;

// Messages from the keymap control

    case IDC_KEYMAPCONTROL:
      if (wNotifyCode == LBN_DBLCLK)
        PostMessage(m_hWnd, WM_COMMAND, IDM_KEYMAP_EDIT, 0);
      return 0;
  }

// Ignore any other messages

  return 0;
}


//**********************************************************************
// CRhsMainWnd::OnInitMenuPopup(HMENU hMenu)
// -----------------------------------------
// Enable menu items as appropriate
//**********************************************************************

long CRhsMainWnd::OnInitMenuPopup(HMENU hMenu)
{ int item_id;

// Enable Save only if we have a filename and the data has changed

  if (strlen(m_FileName) > 0 && m_HasChanged)
    EnableMenuItem(hMenu, IDM_FILE_SAVE, MF_BYCOMMAND | MF_ENABLED);
  else
    EnableMenuItem(hMenu, IDM_FILE_SAVE, MF_BYCOMMAND | MF_GRAYED);

// Enable Append keydef only if allowed

  if (m_Keymap->CanAppendKeyDef())
  { EnableMenuItem(hMenu, IDM_KEYMAP_DETECT, MF_BYCOMMAND | MF_ENABLED);
    EnableMenuItem(hMenu, IDM_KEYMAP_APPENDKEY, MF_BYCOMMAND | MF_ENABLED);
  }
  else
  { EnableMenuItem(hMenu, IDM_KEYMAP_DETECT, MF_BYCOMMAND | MF_GRAYED);
    EnableMenuItem(hMenu, IDM_KEYMAP_APPENDKEY, MF_BYCOMMAND | MF_GRAYED);
  }

// Enable Edit and Delete only if there is a selection

  item_id = m_Keymap->GetSelectedItem();

  if (item_id >= 0)
  { EnableMenuItem(hMenu, IDM_KEYMAP_EDIT,   MF_BYCOMMAND | MF_ENABLED);
    EnableMenuItem(hMenu, IDM_KEYMAP_DELETE, MF_BYCOMMAND | MF_ENABLED);
  }
  else
  { EnableMenuItem(hMenu, IDM_KEYMAP_EDIT,   MF_BYCOMMAND | MF_GRAYED);
    EnableMenuItem(hMenu, IDM_KEYMAP_DELETE, MF_BYCOMMAND | MF_GRAYED);
  }

// Check the Detect key item if we're waiting for a keypress

  if (m_KeyDetectOn)
    CheckMenuItem(hMenu, IDM_KEYMAP_DETECT, MF_BYCOMMAND | MF_CHECKED);
  else
    CheckMenuItem(hMenu, IDM_KEYMAP_DETECT, MF_BYCOMMAND | MF_UNCHECKED);

// Finished

  return 0;
}


//**********************************************************************
// CRhsMainWnd::FitOnScreen
// ------------------------
// Adjust the window size and position so it fits on the desktop
//**********************************************************************

BOOL CRhsMainWnd::FitOnScreen(BOOL Origin, BOOL Size)
{ int width, depth;
  RECT r;

// Check the window exists

  if (!m_hWnd)
    return(FALSE);

// Get some dimensions

  GetWindowRect(m_hWnd, &r);
  width = GetSystemMetrics(SM_CXSCREEN);
  depth = GetSystemMetrics(SM_CYSCREEN);

// If required move the window so its top left corner is on screen

  if (Origin)
  { r.left = r.left >= 0 ? r.left : 0;
    r.top  = r.top >= 0 ? r.top : 0;
    r.left = r.left < width ? r.left : width - 96;
    r.top  = r.top < depth ? r.top : depth - 96;
    SetWindowPos(m_hWnd, NULL, r.left, r.top, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
  }

// If required resize and move the window so it's wholly on screen

  if (Size)
  { r.right  -= r.left;
    r.bottom -= r.top;
    r.right  = r.right <= width ? r.right : width;
    r.bottom = r.bottom <= depth ? r.bottom : depth;
    r.left = r.left + r.right < width ? r.left : width - r.right;
    r.top  = r.top + r.bottom < depth ? r.top  : depth - r.bottom;
    SetWindowPos(m_hWnd, NULL, r.left, r.top, r.right, r.bottom, SWP_NOZORDER);
  }

// Return indicating success

  return(TRUE);
}


//**********************************************************************
// CRhsMainWnd::OnSize
// -------------------
// Handle WM_SIZE
//**********************************************************************

long CRhsMainWnd::OnSize(UINT fwSizeType)
{ RECT r;

// Save the current position in the registry

  if (fwSizeType == SIZE_RESTORED)
  { GetWindowRect(m_hWnd, &r);
    m_Registry->WriteInt("Left",  r.left);
    m_Registry->WriteInt("Top",   r.top);
    m_Registry->WriteInt("Width", r.right - r.left);
    m_Registry->WriteInt("Depth", r.bottom - r.top);
  }

// Resize the XML control

  GetClientRect(m_hWnd, &r);
  m_Keymap->Resize(&r);

// All done

  return 0;
}


//**********************************************************************
// CRhsMainWnd::OnMove
// -------------------
// Handle WM_MOVE
//**********************************************************************

long CRhsMainWnd::OnMove(void)
{ RECT r;

  if (!IsIconic(m_hWnd) && !IsZoomed(m_hWnd))
  { GetWindowRect(m_hWnd, &r);
    m_Registry->WriteInt("Left", r.left);
    m_Registry->WriteInt("Top", r.top);
  }

  return 0;
}


//**********************************************************************
// CRhsMainWnd::OnPaint
// --------------------
// Paint the window contents
//**********************************************************************

long CRhsMainWnd::OnPaint(HDC hDC)
{
  return 0;
}


//**********************************************************************
// CRhsMainWnd::OnDestroy
// ----------------------
// Windows is about to be destroyed
//**********************************************************************

long CRhsMainWnd::OnDestroy(void)
{
  PostQuitMessage(0);
  return 0;
}


//**********************************************************************
// CRhsMainWndProc
// ---------------
// Message handler
//**********************************************************************

long CRhsMainWnd::OnMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{ HDC hdc;
  PAINTSTRUCT ps;

  switch (message)
  {

/*** We have to trap the SC_CLOSE and use it to close the whole app */

    case WM_SYSCOMMAND:
      switch (LOWORD(wParam))
      { case SC_CLOSE:
          PostMessage(hWnd, WM_COMMAND, IDM_FILE_EXIT, 0);
          return 0;

        default:
          return(DefWindowProc(hWnd, message, wParam, lParam));
      }
      break;

// Message from menu or control

    case WM_COMMAND:
      return(OnCommand(HIWORD(wParam), LOWORD(wParam), (HWND) lParam));

/*** Enable/disable menu options */

    case WM_INITMENUPOPUP:
      if ((BOOL) HIWORD(lParam))
        return 0;
      return OnInitMenuPopup((HMENU) wParam);

// Window moved

    case WM_MOVE:
      return(OnMove());

// Window resized

    case WM_SIZE:
      return(OnSize((UINT) wParam));

// Window needs repainting

    case WM_PAINT:
      hdc = BeginPaint(hWnd, &ps);
      OnPaint(hdc);
      EndPaint(hWnd, &ps);
      return 0;

// Pass the focus to the keymap control

    case WM_SETFOCUS:
      m_Keymap->SetFocus();
      return 0;

// Window destroyed

    case WM_DESTROY:
      return(OnDestroy());
  }

// Pass unhandled messages to Windows

  return(DefWindowProc(hWnd, message, wParam, lParam));
}


//**********************************************************************
// CRhsMainWndProc
// ---------------
// Message handler
//**********************************************************************

long CALLBACK CRhsMainWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{ CRhsMainWnd* mainwnd;

// Get the object

  mainwnd = (CRhsMainWnd*) GetWindowLong(hWnd, 0);
  if (!mainwnd)
    return(DefWindowProc(hWnd, message, wParam, lParam));

// Handle the message

  return(mainwnd->OnMessage(hWnd, message, wParam, lParam));
}


