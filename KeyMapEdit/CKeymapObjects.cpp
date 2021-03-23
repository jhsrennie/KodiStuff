//**********************************************************************
// CKeymapControl
// ==============
//**********************************************************************

#ifndef STRICT
#define STRICT
#endif

#include <windows.h>
#include <stdio.h>
#include "CKeymapObjects.h"


//**********************************************************************
// CKeymapComment
// --------------
//**********************************************************************

CKeymapComment::CKeymapComment(void)
{
  strcpy_s(m_Comment, MAX_LENKEYMAPCOMMENT, "");
}


//**********************************************************************
// CKeymapComment::SetComment
// --------------------------
// Set the comment to the supplied string
//**********************************************************************

BOOL CKeymapComment::SetComment(const char* Comment)
{
  strcpy_s(m_Comment, MAX_LENKEYMAPCOMMENT, Comment);

  return TRUE;
}


//**********************************************************************
// CKeymapSection
// --------------
//**********************************************************************

CKeymapSection::CKeymapSection(void)
{
  m_SectionID = -1;
}


//**********************************************************************
// CKeymapSection::SetSection
// --------------------------
// Initialise the object from the section name.
//**********************************************************************

BOOL CKeymapSection::SetSection(const char* Section)
{ int i, j;
  char sectionname[MAX_LENKEYMAPSECTIONNAME+1];

// Trim leading and trailing spaces and lowercase the section name

  for (i = 0; Section[i] == ' '; i++);

  for (j = 0; Section[i] != '\0'; i++, j++)
  { if (j == MAX_LENKEYMAPSECTIONNAME)
      break;
    sectionname[j] = Section[i];
  }
  sectionname[j] = '\0';

  for (j-- ; j >= 0; j--)
  { if (sectionname[j] != ' ')
      break;
    sectionname[j] = '\0';
  }

  AnsiLower(sectionname);

// Find the section name

  m_SectionID = -1;

  for (i = 0; i < NUM_SECTIONNAMES; i++)
  { if (strcmp(sectionname, SectionName[i]) == 0)
    { m_SectionID = i;
      break;
    }
  }

// Return indicating whether we found a valid section name

  return m_SectionID >= 0 ? TRUE : FALSE;
}


//**********************************************************************
// CKeymapSection::GetSection
// --------------------------
// Get the section name
// This is taken from the SectionName array
//**********************************************************************

const char* CKeymapSection::GetSection(void)
{

// This shouldn't ever happen but I hate GPFs so I'll check for it

  if (m_SectionID < 0 || m_SectionID >= NUM_SECTIONNAMES)
    return "InvalidSectionName";

// Return the section name

  return SectionName[m_SectionID];
}


//**********************************************************************
// CKeymapKeyDef
// --------------
//**********************************************************************

CKeymapKeyDef::CKeymapKeyDef(void)
{
  m_KeyCode = -1;
  m_KeyID   = -1;
  m_Ctrl = m_Shift = m_Alt = m_Win = FALSE;
  strcpy_s(m_Action, MAX_LENKEYDEFACTION+1, "");
}


//**********************************************************************
// CKeymapKeyDef::SetKeyName
// -------------------------
// Set the key code from the key name
// Return FALSE if it is not a recognised key name
//**********************************************************************

BOOL CKeymapKeyDef::SetKeyName(const char* Key)
{ int i, j;
  char keyname[MAX_LENKEYMAPKEYNAME+1];

// Trim leading and trailing spaces and lowercase the key name

  for (i = 0; Key[i] == ' '; i++);

  for (j = 0; Key[i] != '\0'; i++, j++)
  { if (j == MAX_LENKEYMAPSECTIONNAME)
      break;
    keyname[j] = Key[i];
  }
  keyname[j] = '\0';

  for (j-- ; j >= 0; j--)
  { if (keyname[j] != ' ')
      break;
    keyname[j] = '\0';
  }

  AnsiLower(keyname);

// Find the section name

  m_KeyCode = -1;

  for (i = 0; i < NUM_KEYNAMES; i++)
  { if (strcmp(keyname, KeyName[i].keyname) == 0)
    { m_KeyCode = i;
      break;
    }
  }

// Return indicating whether we found a valid section name

  return m_KeyCode >= 0 ? TRUE : FALSE;
}


//**********************************************************************
// CKeymapKeyDef::SetID
// --------------------
// Set the key id from the supplied string
//**********************************************************************

BOOL CKeymapKeyDef::SetID(int KeyID)
{

// The only check on the ID is that it's not < 0

  if (KeyID >= 0)
    m_KeyID = KeyID;
  else
    m_KeyID = -1;

// Return indicating whether the key id was valid

  return m_KeyID >= 0 ? TRUE : FALSE;
}


//**********************************************************************
// CKeymapKeyDef::SetModifiers
// ---------------------------
// Set the modifiers from the supplied string
//**********************************************************************

BOOL CKeymapKeyDef::SetModifiers(const char* Modifiers)
{
  char keymod[64];

// Work through the modifiers string setting the modifier flags

  strcpy_s(keymod, 64, Modifiers);
  AnsiLower(keymod);

  m_Ctrl = m_Shift = m_Alt = m_Win = FALSE;

  if (strstr(keymod, "ctrl") || strstr(keymod, "control"))
    m_Ctrl = TRUE;

  if (strstr(keymod, "shift"))
    m_Shift = TRUE;

  if (strstr(keymod, "alt"))
    m_Alt = TRUE;

  if (strstr(keymod, "super") || strstr(keymod, "win"))
    m_Win = TRUE;

// Return indicating whether we found a valid section name

  return m_KeyCode >= 0 ? TRUE : FALSE;
}


//**********************************************************************
// CKeymapKeyDef::SetAction
// ------------------------
// Set the action from the supplied string
//**********************************************************************

BOOL CKeymapKeyDef::SetAction(const char* Action)
{
  strcpy_s(m_Action, MAX_LENKEYDEFACTION+1, Action);
  return TRUE;
}


//**********************************************************************
// CKeymapKeyDef::GetKeyName
// -------------------------
// Get the key name.
// This is taken from the KeyName array
//**********************************************************************

const char* CKeymapKeyDef::GetKeyName(void)
{

// This shouldn't ever happen but I hate GPFs so I'll check for it

  if (m_KeyCode < 0 || m_KeyCode >= NUM_KEYNAMES)
    return "InvalidKeyName";

// Return the key name

  return KeyName[m_KeyCode].keyname;
}


//**********************************************************************
// CKeymapKeyDef::ToXML
// --------------------
// Create an XML representation of the keydef
//**********************************************************************

BOOL CKeymapKeyDef::ToXML(char* XMLStr, int XMLStrLen)
{ int i;
  char keymod[32];

// Build the modifier string

  strcpy_s(keymod, 32, "");

  if (m_Ctrl)
    strcat_s(keymod, 32, "ctrl,");

  if (m_Shift)
    strcat_s(keymod, 32, "shift,");

  if (m_Alt)
    strcat_s(keymod, 32, "alt,");

  if (m_Win)
    strcat_s(keymod, 32, "win,");

  // Trim off the trailing comma
  i = strlen(keymod);
  if (i > 0)
    keymod[i-1] = '\0';

// If the key code is not zero we write the key name

  if (m_KeyCode > 0)
  { if (strlen(keymod) == 0)
      sprintf_s(XMLStr, XMLStrLen, "<%s>%s</%s>", GetKeyName(), m_Action, GetKeyName());
    else
      sprintf_s(XMLStr, XMLStrLen, "<%s mod=\"%s\">%s</%s>", GetKeyName(), keymod, m_Action, GetKeyName());
  }

// Else use the <key id="nnn"> form

  else
  { if (strlen(keymod) == 0)
      sprintf_s(XMLStr, XMLStrLen, "<key id=\"%d\">%s</key>", m_KeyID, m_Action);
    else
      sprintf_s(XMLStr, XMLStrLen, "<key id=\"%d\" mod=\"%s\">%s</key>", m_KeyID, keymod, m_Action);
  }

// Return indicating success

  return TRUE;
}


