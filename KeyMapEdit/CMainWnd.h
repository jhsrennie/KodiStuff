//**********************************************************************
// CRhsMainWnd
// ===========
// Implementation of main window
//**********************************************************************

#ifndef _INC_RHSMAINWND
#define _INC_RHSMAINWND


//**********************************************************************
// Constants
//**********************************************************************

// ID for the keymap control
#define IDC_KEYMAPCONTROL 200


//**********************************************************************
// Forward declarations
//**********************************************************************

class CKeymapControl;
class CKeymapKeyDef;
class CRhsRegistry;


//**********************************************************************
// CRhsMainWnd
// -----------
//**********************************************************************

class CRhsMainWnd
{

// Methods

  public:
    CRhsMainWnd(void);
    ~CRhsMainWnd(void);

    BOOL Open(HINSTANCE hInstance, char* Title, int Left, int Top, int Width, int Depth, char* lpCmdLine);

    long OnFileNew(void);
    long OnFileOpen(void);
    long OnFileSave(void);
    long OnFileSaveAs(void);
    long OnFileExit(void);
    long OnFileAbout(void);

    long OnEditFont(void);

    long OnKeymapDetect(void);
    long OnKeyDetected(CKeymapKeyDef* KeyDef);
    long OnKeymapAppendKeyDef(void);
    long OnKeymapAppendSection(void);
    long OnKeymapInsertComment(void);
    long OnKeymapEdit(void);
    long OnKeymapDelete(void);

    void DetectKey(MSG* Msg);

    int AskToSave(void);
    BOOL OpenFile(char* FileName);

    long OnCommand(WORD wNotifyCode, WORD wID, HWND hwndCtl);
    long OnInitMenuPopup(HMENU hMenu);

    BOOL FitOnScreen(BOOL Origin, BOOL Size);
    long OnSize(UINT fwSizeType);
    long OnMove(void);
    long OnPaint(HDC hDC);
    long OnDestroy(void);
    long OnMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

    inline HWND hWnd(void) { return m_hWnd; }

// Variables

  private:
    HINSTANCE       m_hInstance;
    HWND            m_hWnd;
    CKeymapControl* m_Keymap;
    CRhsRegistry*   m_Registry;

    // TRUE means we are detecting a keystroke
    BOOL m_KeyDetectOn;

    char m_FileName[MAX_PATH+1];
    BOOL m_HasChanged;

};


//**********************************************************************
// End of CRhsMainWnd
//**********************************************************************

#endif // ifndef _INC_RHSMAINWND

