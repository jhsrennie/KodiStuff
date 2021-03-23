//**********************************************************************
// Strings
//**********************************************************************

#define String_IDS_MAINCLASSNAME "RhsKeyMapEditWClass"
#define String_IDS_TITLE         "KeyMapEdit"


//**********************************************************************
// Function prototypes
//**********************************************************************

int winprintf(const char *Format, ...);
int winprintfYesNo(const char *Format, ...);
int winprintfYesNoCancel(const char *Format, ...);

BOOL strtoint(const char* s, int* i);

const char* GetLastErrorMessage(void);

