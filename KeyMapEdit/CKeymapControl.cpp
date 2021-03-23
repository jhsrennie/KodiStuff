//**********************************************************************
// CKeymapControl
// ==============
//**********************************************************************

#ifndef STRICT
#define STRICT
#endif

#include <windows.h>
#include "KeyMapEdit.h"
#include "CKeymapControl.h"
#include "CKeymapObjects.h"
#include "tinyxml/tinyxml.h"


//**********************************************************************
// CKeymapControl
// --------------
//**********************************************************************

CKeymapControl::CKeymapControl(void)
{
  m_hInstance = NULL;
  m_hListWnd  = NULL;
  m_WndID     = 0;
  strcpy_s(m_LastError, LEN_LASTERROR+1, "");
}


CKeymapControl::~CKeymapControl(void)
{
}


//**********************************************************************
// CKeymapControl::Open
// --------------------
// Create the list control
//**********************************************************************

BOOL CKeymapControl::Open(HINSTANCE hInstance, HWND hParentWnd, RECT* r, DWORD WndID)
{

// Save the parent details

  m_hInstance = hInstance;
  m_hParentWnd = hParentWnd;
  m_WndID = WndID;

// Create the window

  m_hListWnd = CreateWindow("LISTBOX", "",
                            WS_CHILD | WS_VISIBLE | WS_VSCROLL
                            | LBS_USETABSTOPS | LBS_NOTIFY
                            | LBS_NOINTEGRALHEIGHT | LBS_WANTKEYBOARDINPUT,
                            r->left, r->top, r->right, r->bottom,
                            m_hParentWnd,
                            (HMENU) m_WndID,
                            m_hInstance,
                            NULL);

  SendMessage(m_hListWnd, WM_SETFONT, (WPARAM) GetStockObject(ANSI_VAR_FONT), 0);

// Return indicating success

  return true;
}


//**********************************************************************
// CKeymapControl::Resize
// ----------------------
// Resize the list control
//**********************************************************************

BOOL CKeymapControl::Resize(RECT* r)
{

  MoveWindow(m_hListWnd, r->left, r->top, r->right, r->bottom, TRUE);

// Return indicating success

  return TRUE;
}


//**********************************************************************
// CKeymapControl::NewKeymap
// -------------------------
// Populate the list control with a new empty keymap
//**********************************************************************

BOOL CKeymapControl::NewKeymap(void)
{ CKeymapComment comment;
  CKeymapSection section;

// Clear any current content and add a new file with just a <global>
// section

  ClearList();
  
  comment.SetComment("Template XBMC keyboard file");
  InsertComment(comment);

  section.SetSection("global");
  AppendSection(section);

// Return indicating success

  return TRUE;
}


//**********************************************************************
// CKeymapControl::InsertComment
// -----------------------------
// Insert a comment before the current selection, or at the end of the
// list if there is no selection.
//**********************************************************************

BOOL CKeymapControl::InsertComment(CKeymapComment& Comment)
{ int position, firstsection, insection;
  char comment[MAX_LENITEMSTRING+1];

// Check if we are in a section

  firstsection = FindFirstSection();
  position = (int) SendMessage(m_hListWnd, LB_GETCURSEL, 0, 0);

  if (firstsection < 0)
  { insection = FALSE;
  }
  else
  { if (position == LB_ERR)
      insection = TRUE;
    else
      insection = position > firstsection ? TRUE : FALSE;
  }

// Format the comment

  if (insection)
    sprintf_s(comment, MAX_LENITEMSTRING+1, "\t# %s", Comment.m_Comment);
  else
    sprintf_s(comment, MAX_LENITEMSTRING+1, "# %s", Comment.m_Comment);

// Insert the comment

  if (position == LB_ERR)
    SendMessage(m_hListWnd, LB_ADDSTRING, 0, (LPARAM) comment);
  else
    SendMessage(m_hListWnd, LB_INSERTSTRING, (WPARAM) position, (LPARAM) comment);

// Return indicating success

  return TRUE;
}


BOOL CKeymapControl::UpdateComment(CKeymapComment& Comment, int ItemID)
{ int firstsection, insection;
  char comment[MAX_LENITEMSTRING+1];

// Check the requested item is a comment

  if (GetItemType(ItemID) != TYPE_COMMENT)
    return FALSE;

// Check if we are in a section

  firstsection = FindFirstSection();

  if (firstsection < 0)
    insection = FALSE;
  else 
    insection = ItemID > firstsection ? TRUE : FALSE;

// Format the comment

  if (insection)
    sprintf_s(comment, MAX_LENITEMSTRING+1, "\t# %s", Comment.m_Comment);
  else
    sprintf_s(comment, MAX_LENITEMSTRING+1, "# %s", Comment.m_Comment);

// Update the comment

  SendMessage(m_hListWnd, LB_DELETESTRING, (WPARAM) ItemID, 0);
  SendMessage(m_hListWnd, LB_INSERTSTRING, (WPARAM) ItemID, (LPARAM) comment);

// Return indicating success

  return TRUE;
}


//**********************************************************************
// CKeymapControl::AppendSection
// -----------------------------
// Append a section after the current selection, or at the end of the
// list if there is no selection.
//**********************************************************************

BOOL CKeymapControl::AppendSection(CKeymapSection& Section)
{ int position, item_type;

// Get the current selection then work down the list to find the next
// section or the end of the list.

  position = (int) SendMessage(m_hListWnd, LB_GETCURSEL, 0, 0);
  if (position != LB_ERR)
  { for (position++; ; position++)
    { item_type = GetItemType(position);

      // If we've hit the end of the list set the position to CB_ERR and break
      if (item_type == TYPE_NONE || item_type == TYPE_ERROR)
      { position = LB_ERR;
        break;
      }

      // If we've hit a section break; we'll insert before this section
      if (item_type == TYPE_SECTION)
        break;

      position++;
    }
  }

// If the current position is LB_ERR append to the list, else insert the
// section at the current position.

  if (position == LB_ERR)
    SendMessage(m_hListWnd, LB_ADDSTRING, 0, (LPARAM) Section.GetSection());
  else
    SendMessage(m_hListWnd, LB_INSERTSTRING, (WPARAM) position, (LPARAM) Section.GetSection());

// Return indicating success

  return TRUE;
}


BOOL CKeymapControl::UpdateSection(CKeymapSection& Section, int ItemID)
{

// Check the requested item is a section

  if (GetItemType(ItemID) != TYPE_SECTION)
    return FALSE;

// Update the section

  SendMessage(m_hListWnd, LB_DELETESTRING, (WPARAM) ItemID, 0);
  SendMessage(m_hListWnd, LB_INSERTSTRING, (WPARAM) ItemID, (LPARAM) Section.GetSection());

// Return indicating success

  return TRUE;
}


//**********************************************************************
// CKeymapControl::CanAppendKeyDef
// -------------------------------
// Check if we can append a key definition after the current selection
//**********************************************************************

BOOL CKeymapControl::CanAppendKeyDef(void)
{ int position, firstsection, item_type;

// Get the position of the first section

  for (firstsection = 0; ; firstsection++)
  { item_type = GetItemType(firstsection);

    // If we've hit the end of the list just return because there are no
    // sections to add the key to
    if (item_type == TYPE_NONE || item_type == TYPE_ERROR)
    { strcpy_s(m_LastError, LEN_LASTERROR+1, "There are no sections. You need to create a section before you can append keys to it.");
      return FALSE;
    }

    // If we've hit a section break; we'll insert before this section
    if (item_type == TYPE_SECTION)
      break;
  }

// The insertion position is the current selection + 1. Note that this
// cannot be above the first section.

  position = (int) SendMessage(m_hListWnd, LB_GETCURSEL, 0, 0);

  if (position != LB_ERR)
  { position++;
    if (position <= firstsection)
    { strcpy_s(m_LastError, LEN_LASTERROR+1, "Cannot append a key definition at the selected position");
      return FALSE;
    }
  }

// Return indicating that a key can be appended

  return TRUE;
}

//**********************************************************************
// CKeymapControl::AppendKeyDef
// ----------------------------
// Append a key definition after the current selection, or at the end of
// the list if there is no selection.
//**********************************************************************

BOOL CKeymapControl::AppendKeyDef(CKeymapKeyDef& KeyDef)
{ int position, firstsection, item_type;
  char keydef[MAX_LENITEMSTRING+1];

// Get the position of the first section

  for (firstsection = 0; ; firstsection++)
  { item_type = GetItemType(firstsection);

    // If we've hit the end of the list just return because there are no
    // sections to add the key to
    if (item_type == TYPE_NONE || item_type == TYPE_ERROR)
      return FALSE;

    // If we've hit a section break; we'll insert before this section
    if (item_type == TYPE_SECTION)
      break;
  }

// The insertion position is the current selection + 1. Note that this
// cannot be above the first section.

  position = (int) SendMessage(m_hListWnd, LB_GETCURSEL, 0, 0);

  if (position != LB_ERR)
  { position++;
    if (position <= firstsection)
    { strcpy_s(m_LastError, LEN_LASTERROR+1, "Cannot append a key definition at the selected position");
      return FALSE;
    }

    // Check we haven't gone off the end of the list
    if (GetItemType(firstsection) == TYPE_NONE)
      position = LB_ERR;
  }

// Format the key definition

  if (!FormatKeyDef(KeyDef, keydef, MAX_LENITEMSTRING+1))
    return FALSE;

// Insert the comment

  if (position == LB_ERR)
    SendMessage(m_hListWnd, LB_ADDSTRING, 0, (LPARAM) keydef);
  else
    SendMessage(m_hListWnd, LB_INSERTSTRING, (WPARAM) position, (LPARAM) keydef);

// Return indicating success

  return TRUE;
}


BOOL CKeymapControl::UpdateKeyDef(CKeymapKeyDef& KeyDef, int ItemID)
{ char keydef[MAX_LENITEMSTRING+1];

// Check the requested item is a comment

  if (GetItemType(ItemID) != TYPE_KEYDEF)
    return FALSE;

// Format the key definition

  if (!FormatKeyDef(KeyDef, keydef, MAX_LENITEMSTRING+1))
    return FALSE;

// Update the comment

  SendMessage(m_hListWnd, LB_DELETESTRING, (WPARAM) ItemID, 0);
  SendMessage(m_hListWnd, LB_INSERTSTRING, (WPARAM) ItemID, (LPARAM) keydef);

// Return indicating success

  return TRUE;
}


//**********************************************************************
// CKeymapControl::FormatKeyDef
// ----------------------------
// Return a text representation of the key definition that we can put in
// the list.
//**********************************************************************

BOOL CKeymapControl::FormatKeyDef(CKeymapKeyDef& KeyDef, char* KeyStr, int KeyStrLen)
{ int i;
  char keyname[256];

// Build the key name in the form "ctrl-shift-alt-X"

  strcpy_s(KeyStr, KeyStrLen, "\t");

  if (KeyDef.m_Ctrl)
    strcat_s(KeyStr, KeyStrLen, "ctrl-");

  if (KeyDef.m_Shift)
    strcat_s(KeyStr, KeyStrLen, "shift-");

  if (KeyDef.m_Alt)
    strcat_s(KeyStr, KeyStrLen, "alt-");

  if (KeyDef.m_Win)
    strcat_s(KeyStr, KeyStrLen, "windows-");

  strcpy_s(keyname, 256, KeyDef.GetKeyName());
  strcat_s(KeyStr, KeyStrLen, keyname);

// If the key name is "key" we need the ID

  if (strcmp(keyname, "key") == 0)
  { i = strlen(KeyStr);
    sprintf_s(KeyStr+i, KeyStrLen-i, "=%d", KeyDef.m_KeyID);
  }

// Finally add the action

  strcat_s(KeyStr, KeyStrLen, ": ");
  strcat_s(KeyStr, KeyStrLen, KeyDef.m_Action);

// Return indicating success

  return TRUE;
}


//**********************************************************************
// CKeymapControl::ClearList
// -------------------------
// Clear the list contents
//**********************************************************************

BOOL CKeymapControl::ClearList(void)
{ DWORD d;

  d = SendMessage(m_hListWnd, LB_GETCOUNT, 0, 0);

  while (d > 0)
  { d--;
    SendMessage(m_hListWnd, LB_DELETESTRING, d, 0);
  }

  return true;
}


//**********************************************************************
// CKeymapControl::GetSelectedItem
// -------------------------------
// This returns an id that can be used to identify an item (at least
// until the list changes). In fact the id we use is just the list
// offset.
// The value -1 indicates no item is selected.
//**********************************************************************

int CKeymapControl::GetSelectedItem(void)
{ int cursel;

  cursel = (int) SendMessage(m_hListWnd, LB_GETCURSEL, 0, 0);
  if (cursel == LB_ERR)
    cursel = -1;

  return cursel;
}


//**********************************************************************
// CKeymapControl::GetItemType
// ---------------------------
// Get the type of the requested item id
//**********************************************************************

int CKeymapControl::GetItemType(int ItemID)
{ int element_type;
  char s[256];

// Get the item text

  if (SendMessage(m_hListWnd, LB_GETTEXT, (WPARAM) ItemID, (LPARAM) s) == LB_ERR)
    return TYPE_NONE;

// Work out what type the current selection is.
// Lines starting with "# " or "\t# " are comments

  if (s[0] == '#' && s[1] == ' ')
  { element_type = TYPE_COMMENT;
  }
  else if (s[0] == '\t' && s[1] == '#' && s[2] == ' ')
  { element_type = TYPE_COMMENT;
  }

// Lines starting with a tab then not # are keydefs

  else if (s[0] == '\t' && s[1] != '#')
  { element_type = TYPE_KEYDEF;
  }

// Lines starting with anything other than # and tab are sections

  else
  { element_type = TYPE_SECTION;
  }

// Return the element type

  return element_type;

}


//**********************************************************************
// CKeymapControl::FindFirstSection
// --------------------------------
// Return the index of the first section, or -1 if there are no sections
//**********************************************************************

int CKeymapControl::FindFirstSection(void)
{ int firstsection, item_type;

// Get the position of the first section

  for (firstsection = 0; ; firstsection++)
  { item_type = GetItemType(firstsection);

// If we've hit the end of the list just return -1 because there are
// no sections

    if (item_type == TYPE_NONE || item_type == TYPE_ERROR)
      return -1;

// If we've hit a section return the section index

    if (item_type == TYPE_SECTION)
      return firstsection;
  }

// We shouldn't get here, but if we do then return -1

  return -1;
}


//**********************************************************************
// CKeymapControl::GetComment
// --------------------------
// Return the requested comment.
// Return FALSE if the requested item is not a comment.
//**********************************************************************

BOOL CKeymapControl::GetComment(CKeymapComment& Comment, int ItemID)
{ BOOL insection;
  char s[MAX_LENITEMSTRING+1];

// Get the comment text

  if (SendMessage(m_hListWnd, LB_GETTEXT, (WPARAM) ItemID, (LPARAM) s) == LB_ERR)
    return FALSE;

// Lines starting "# " or "\t# " are comments

  if (s[0] == '#' && s[1] == ' ')
    insection = FALSE;
  else if (s[0] == '\t' && s[1] == '#' && s[2] == ' ')
    insection = TRUE;
  else
    return FALSE;

// Return the comment

  if (insection)
    Comment.SetComment(s+3);
  else
    Comment.SetComment(s+2);

  return TRUE;
}


//**********************************************************************
// CKeymapControl::GetSection
// --------------------------
// Return the requested section.
// Return FALSE if the requested item is not a section.
//**********************************************************************

BOOL CKeymapControl::GetSection(CKeymapSection& Section, int ItemID)
{ char s[MAX_LENITEMSTRING+1];

// Get the comment text

  if (SendMessage(m_hListWnd, LB_GETTEXT, (WPARAM) ItemID, (LPARAM) s) == LB_ERR)
    return FALSE;

// Lines that don't start "# " or tab are sections

  if (s[0] == '#' || s[0] == '\t')
    return FALSE;

// Set the section

  if (!Section.SetSection(s))
    return FALSE;

// Return indicating success

  return TRUE;
}


//**********************************************************************
// CKeymapControl::GetKeyDef
// -------------------------
// Return the requested key definition.
// Return FALSE if the requested item is not a key definition.
//**********************************************************************

BOOL CKeymapControl::GetKeyDef(CKeymapKeyDef& KeyDef, int ItemID)
{ int i;
  char keytext[MAX_LENITEMSTRING+1],
       keyname[MAX_LENITEMSTRING+1],
       keyid[MAX_LENITEMSTRING+1];

// Get the keydef text

  if (SendMessage(m_hListWnd, LB_GETTEXT, (WPARAM) ItemID, (LPARAM) keytext) == LB_ERR)
    return FALSE;

// Key definitions start with a tab and not #

  if (keytext[0] != '\t')
    return FALSE;
  if (keytext[1] == '#')
    return FALSE;

  strcpy_s(keytext, MAX_LENITEMSTRING+1, keytext+1);

// Get the modifiers; these are always in the order ctrl, shift, alt, win

  KeyDef.m_Ctrl = KeyDef.m_Shift = KeyDef.m_Alt = KeyDef.m_Win = FALSE;

  if (strncmp(keytext, "ctrl-", 5) == 0)
  { KeyDef.m_Ctrl = TRUE;
    strcpy_s(keytext, MAX_LENITEMSTRING+1, keytext+5);
  }

  if (strncmp(keytext, "shift-", 6) == 0)
  { KeyDef.m_Shift = TRUE;
    strcpy_s(keytext, MAX_LENITEMSTRING+1, keytext+6);
  }

  if (strncmp(keytext, "alt-", 4) == 0)
  { KeyDef.m_Alt = TRUE;
    strcpy_s(keytext, MAX_LENITEMSTRING+1, keytext+4);
  }

  if (strncmp(keytext, "win-", 4) == 0)
  { KeyDef.m_Win = TRUE;
    strcpy_s(keytext, MAX_LENITEMSTRING+1, keytext+4);
  }

// Now get the key

  KeyDef.m_KeyID = -1;

  for (i = 0; keytext[i] != ':' && keytext[i] != '='; i++)
    keyname[i] = keytext[i];
  keyname[i] = '\0';
  strcpy_s(keytext, MAX_LENITEMSTRING+1, keytext + i);

  if (!KeyDef.SetKeyName(keyname))
    return FALSE;

// If the keyname is "key" there must be an =NNN string

  strcpy_s(keyid, MAX_LENITEMSTRING+1, "");

  if (strcmp(keyname, "key") == 0)
  { for (i = 1; keytext[i] != ':'; i++)
      keyid[i-1] = keytext[i];
    keyid[i-1] = '\0';
    strcpy_s(keytext, MAX_LENITEMSTRING+1, keytext + i);

    if (!strtoint(keyid, &i))
      return FALSE;
    if (i < 0)
      return FALSE;
    KeyDef.m_KeyID = i;
  }

// The remaining text is ": action"

  for (i = 0; keytext[i] == ':' || keytext[i] == ' '; i++);
  strcpy_s(KeyDef.m_Action, MAX_LENKEYDEFACTION, keytext + i);

// Return indicating success

  return TRUE;
}


//**********************************************************************
// CKeymapControl::DeleteItem
// --------------------------
// Delete the requested item
//**********************************************************************

BOOL CKeymapControl::DeleteItem(int ItemID)
{ int element_type;

// Get the item type

  element_type = GetItemType(ItemID);
  if (element_type < 0)
    return FALSE;

// Comments and KeyDefs can just be deleted

  if (element_type == TYPE_COMMENT || element_type == TYPE_KEYDEF)
  { SendMessage(m_hListWnd, LB_DELETESTRING, (WPARAM) ItemID, 0);
  }

// When deleting a section you need to delete everything in that section

  else if (element_type == TYPE_SECTION)
  { SendMessage(m_hListWnd, LB_DELETESTRING, (WPARAM) ItemID, 0);

    for (;;)
    { element_type = GetItemType(ItemID);
      if (element_type != TYPE_COMMENT && element_type != TYPE_KEYDEF)
        break;

      SendMessage(m_hListWnd, LB_DELETESTRING, (WPARAM) ItemID, 0);
    }
  }

// Unrecognised item

  else
  { return FALSE;
  }

// Return indicating success

  return TRUE;
}


//**********************************************************************
// CKeymapControl::SetFont
// -----------------------
// Set the list control font
//**********************************************************************

BOOL CKeymapControl::SetFont(const LOGFONT* LogFont)
{ static HFONT hf = NULL;

  if (hf)
    DeleteObject(hf);
  hf = CreateFontIndirect(LogFont);

  SendMessage(m_hListWnd, WM_SETFONT, (WPARAM) hf, MAKELPARAM(TRUE, 0));

  return TRUE;
}


//**********************************************************************
// CKeymapControl::SetFocus
// ------------------------
// Set the focus to the list control
//**********************************************************************

void CKeymapControl::SetFocus(void)
{
  ::SetFocus(m_hListWnd);
}


//**********************************************************************
// CKeymapControl::GetLastError
// ----------------------------
// Retrieve the last error from the control
//**********************************************************************

const char* CKeymapControl::GetLastError(void)
{
  return m_LastError;
}


