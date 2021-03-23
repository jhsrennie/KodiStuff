//**********************************************************************
// CKeymapObjects
// ==============
// Various objects used in keymaps.
// These are collected into one file because they're all pretty simple
//**********************************************************************

#ifndef _INC_CKEYMAPOBJECTS
#define _INC_CKEYMAPOBJECTS

#include "Constants.h"


//**********************************************************************
// CKeymapComment
// --------------
//**********************************************************************

class CKeymapComment
{

// Methods

  public:
    CKeymapComment(void);

    BOOL SetComment(const char* Comment);

// Variables

  public:
    char m_Comment[MAX_LENKEYMAPCOMMENT+1];
};


//**********************************************************************
// CKeymapSection
// --------------
//**********************************************************************

class CKeymapSection
{

// Methods

  public:
    CKeymapSection(void);

    BOOL SetSection(const char* Section);
    const char* GetSection(void);

// Variables

  public:
    int m_SectionID;
};


//**********************************************************************
// CKeymapKeyDef
// -------------
//**********************************************************************

class CKeymapKeyDef
{

// Methods

  public:
    CKeymapKeyDef(void);

    BOOL SetKeyName(const char* Keyname);
    BOOL SetID(int KeyID);
    BOOL SetModifiers(const char* Modifiers);
    BOOL SetAction(const char* Action);
    const char* GetKeyName(void);
    
    BOOL ToXML(char* XMLStr, int XMLStrLen);

// Variables

  public:
    int m_KeyCode, // VK_XXX
        m_KeyID;   // ID for <key id="nnn" mappings

    BOOL m_Ctrl,
         m_Shift,
         m_Alt,
         m_Win;

    char m_Action[MAX_LENKEYDEFACTION+1];
};


//**********************************************************************
// End of CKeymapComment
//**********************************************************************

#endif // _INC_CKEYMAPOBJECTS

