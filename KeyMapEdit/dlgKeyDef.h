//**********************************************************************
// CDlgKeyDef
// ===========
// Dialog box to add/edit key definitions
//**********************************************************************

#ifndef _INC_CDLGKEYDEF
#define _INC_CDLGKEYDEF

#include "CKeymapObjects.h"


//**********************************************************************
// CDlgKeyDef
// ----------
//**********************************************************************

class CDlgKeyDef
{

// Methods

  public:
    CDlgKeyDef(void);

    BOOL SetTitle(const char* Title);
    BOOL DoModal(HINSTANCE hInstance, HWND hWnd);

    BOOL OnInit(HWND hDlg);
    BOOL OnCancel(void);
    BOOL OnOK(void);

// Variables

  public:
    CKeymapKeyDef m_KeyDef;
    char m_Title[256];

  private:
    HINSTANCE m_hInstance;
    HWND m_hDlg;
};


//**********************************************************************
// End of CDlgKeyDef
//**********************************************************************

#endif // ifndef _INC_CDLGKEYDEF

