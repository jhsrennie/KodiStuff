//**********************************************************************
// CKeyDetector
// ============
// Class to check a keypress and convert it to a KeyDef
//**********************************************************************

#ifndef STRICT
#define STRICT
#endif

#include <windows.h>
#include "CKeymapObjects.h"
#include "CKeyDetector.h"

// XBMC code
#include "XBMC/XBMC.h"


//**********************************************************************
// CKeyDetector
// ------------
//**********************************************************************

CKeyDetector::CKeyDetector(void)
{
}


//**********************************************************************
// DetectKey
// ---------
// Check the supplied Windows message and if it's a keypress convert
// it to a KeyDef
//**********************************************************************

BOOL CKeyDetector::DetectKey(MSG* Msg, CKeymapKeyDef& KeyDef)
{ int i;
  uint8_t vkey = 0;
  XBMC_keysym keysym;
  XBMCKEYTABLE keytable;

// We are only interested in WK_KEYDOWN and WM_SYSKEYDOWN messages.

  if (Msg->message != WM_KEYDOWN && Msg->message != WM_SYSKEYDOWN)
    return FALSE;

// Ignore modifiers

  switch (Msg->wParam)
  { case VK_CONTROL:
    case VK_SHIFT:
    case VK_MENU:
    case VK_LWIN:
    case VK_RWIN:
      return FALSE;
  }

// Convert the virtual key code into an XBMC key code

  TranslateKey(Msg->wParam, HIWORD(Msg->lParam), &keysym, 1);

  if (KeyTableLookupSymAndUnicode(keysym.sym, keysym.unicode, &keytable))
  {
    vkey = keytable.vkey;
  }
  else if (KeyTableLookupUnicode(keysym.unicode, &keytable))
  {
    vkey = keytable.vkey;
  }
  else if (KeyTableLookupSym(keysym.sym, &keytable))
  {
    vkey = keytable.vkey;
  }

  if (vkey == 0)
    return FALSE;

// Now convert the vkey to an offset in the Keyname array

  for (i = 0; i < NUM_KEYNAMES; i++)
  { if (KeyName[i].keycode == vkey)
    { KeyDef.m_KeyCode = i;
      break;
    }
  }

// Get the keyboard modifiers

  KeyDef.m_Ctrl  = GetKeyState(VK_CONTROL) < 0 ? TRUE : FALSE;
  KeyDef.m_Shift = GetKeyState(VK_SHIFT)   < 0 ? TRUE : FALSE;
  KeyDef.m_Alt   = GetKeyState(VK_MENU)    < 0 ? TRUE : FALSE;
  KeyDef.m_Win   = GetKeyState(VK_LWIN)    < 0 ? TRUE : FALSE;

// Ignore shift unless it's combined with another modifier

  if (KeyDef.m_Shift && !(KeyDef.m_Ctrl || KeyDef.m_Alt || KeyDef.m_Win))
    KeyDef.m_Shift = FALSE;

// Return indicateing we detected a keypress
  
  return TRUE;
}


