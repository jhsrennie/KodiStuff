//**********************************************************************
// CDlgAbout
// ==========
// About dialog box
//**********************************************************************

#ifndef _INC_CDLGABOUT
#define _INC_CDLGABOUT


//**********************************************************************
// CDlgAbout
// ----------
//**********************************************************************

class CDlgAbout
{

// Methods

  public:
    CDlgAbout(void);
    ~CDlgAbout(void);

    BOOL DoModal(HINSTANCE hInstance, HWND hWnd);

    BOOL OnInit(HWND hDlg);
    BOOL OnCancel(void);
    BOOL OnOK(void);

// Variables

  public:

  private:
    HINSTANCE m_hInstance;
    HWND m_hDlg;

};


//**********************************************************************
// End of CDlgAbout
//**********************************************************************

#endif // ifndef _INC_CDLGABOUT

