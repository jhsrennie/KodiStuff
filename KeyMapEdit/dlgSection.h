//**********************************************************************
// CDlgSection
// ===========
// Dialog box to add/edit comments
//**********************************************************************

#ifndef _INC_CDLGSECTION
#define _INC_CDLGSECTION

#include "CKeymapObjects.h"


//**********************************************************************
// CDlgSection
// ----------
//**********************************************************************

class CDlgSection
{

// Methods

  public:
    CDlgSection(void);

    BOOL SetTitle(const char* Title);
    BOOL DoModal(HINSTANCE hInstance, HWND hWnd);

    BOOL OnInit(HWND hDlg);
    BOOL OnCancel(void);
    BOOL OnOK(void);

// Variables

  public:
    CKeymapSection m_Section;
    int  m_ShowSection[NUM_SECTIONNAMES];
    char m_Title[256];

  private:
    HINSTANCE m_hInstance;
    HWND m_hDlg;
};


//**********************************************************************
// End of CDlgSection
//**********************************************************************

#endif // ifndef _INC_CDLGSECTION

