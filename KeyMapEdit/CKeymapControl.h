//**********************************************************************
// CKeymapControl
// ==============
//**********************************************************************

#ifndef _INC_CKeymapControl
#define _INC_CKeymapControl


//**********************************************************************
// Forward declarations
// --------------------
//**********************************************************************

class TiXmlNode;

class CKeymapComment;
class CKeymapSection;
class CKeymapKeyDef;
class CRhsFont;


//**********************************************************************
// CKeymapControl
// ----------
//**********************************************************************

// Maximum length of a string in the list
#define MAX_LENITEMSTRING 255

class CKeymapControl
{

// Methods

  public:
    CKeymapControl(void);
    ~CKeymapControl(void);
    
    BOOL Open(HINSTANCE hInstance, HWND hParentWnd, RECT* r, DWORD WndID);
    BOOL Resize(RECT* r);

    BOOL NewKeymap(void);

    BOOL InsertComment(CKeymapComment& Comment);
    BOOL UpdateComment(CKeymapComment& Comment, int ItemID);
    
    BOOL AppendSection(CKeymapSection& Section);
    BOOL UpdateSection(CKeymapSection& Section, int ItemID);
    
    BOOL CanAppendKeyDef(void);
    BOOL AppendKeyDef(CKeymapKeyDef& KeyDef);
    BOOL UpdateKeyDef(CKeymapKeyDef& KeyDef, int ItemID);
    
    BOOL FormatKeyDef(CKeymapKeyDef& KeyDef, char* KeyStr, int KeyStrLen);

    BOOL ClearList(void);

    int  GetSelectedItem(void);
    int  GetItemType(int ItemID);
    int  FindFirstSection(void);

    BOOL GetComment(CKeymapComment& Comment, int ItemID);
    BOOL GetSection(CKeymapSection& Section, int ItemID);
    BOOL GetKeyDef(CKeymapKeyDef& KeyDef, int ItemID);
    
    BOOL DeleteItem(int ItemID);

    BOOL SetFont(const LOGFONT* LogFont);
    void SetFocus(void);

    const char* GetLastError(void);

// Variables

  private:
    HINSTANCE m_hInstance;
    HWND      m_hListWnd, m_hParentWnd;
    DWORD     m_WndID;

#define LEN_LASTERROR 255
    char m_LastError[LEN_LASTERROR+1];
};

#endif
