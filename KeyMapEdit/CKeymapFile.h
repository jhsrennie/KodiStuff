//**********************************************************************
// CKeymapFile
// ==============
//**********************************************************************

#ifndef _INC_CKEYMAPFILE
#define _INC_CKEYMAPFILE


//**********************************************************************
// Forward declarations
// --------------------
//**********************************************************************

#include <stdio.h>

class TiXmlNode;

class CKeymapComment;
class CKeymapSection;
class CKeymapKeyDef;


//**********************************************************************
// CKeymapFile
// ----------
//**********************************************************************

class CKeymapFile
{

// Methods

  public:
    CKeymapFile(void);
    ~CKeymapFile(void);

    BOOL SaveKeymap(char* KeymapFile, CKeymapControl* KeymapControl);
    BOOL SaveKeymapSection(FILE* KeymapFile, int* ItemID, CKeymapControl* KeymapControl);

    BOOL ReadKeymap(char* KeymapFile, CKeymapControl* KeymapControl);
    BOOL ReadKeymapSection(TiXmlNode* Section, CKeymapControl* KeymapControl);
    BOOL ReadKeymapKeyDef(TiXmlNode* KeyDef, CKeymapControl* KeymapControl);

    const char* GetLastError(void);

// Variables

  private:

#define LEN_LASTERROR 255
    char m_LastError[LEN_LASTERROR+1];
};

#endif
