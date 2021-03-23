//**********************************************************************
// CDlgComment
// ===========
// Dialog box to add/edit comments
//**********************************************************************

#ifndef _INC_CDLGCOMMENT
#define _INC_CDLGCOMMENT

#include "CKeymapObjects.h"


//**********************************************************************
// CDlgComment
// ----------
//**********************************************************************

class CDlgComment
{

// Methods

  public:
    CDlgComment(void);
    ~CDlgComment(void);

    BOOL SetTitle(const char* Title);
    BOOL DoModal(HINSTANCE hInstance, HWND hWnd);

    BOOL OnInit(HWND hDlg);
    BOOL OnCancel(void);
    BOOL OnOK(void);

// Variables

  public:
    CKeymapComment m_Comment;
    char m_Title[256];

  private:
    HINSTANCE m_hInstance;
    HWND m_hDlg;
};


//**********************************************************************
// End of CDlgComment
//**********************************************************************

#endif // ifndef _INC_CDLGCOMMENT

