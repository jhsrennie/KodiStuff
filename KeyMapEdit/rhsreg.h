//**********************************************************************
// CRhsRegistry
// ============
//
// A class to simplify registry access
//
// John Rennie
// jrennie@cix.compulink.co.uk
// 4th January 1998
//**********************************************************************

#ifndef _INC_CRHSREGISTRY
#define _INC_CRHSREGISTRY

#define LEN_REGISTRYPATH 255


//**********************************************************************
// CRhsRegistry
// ------------
//**********************************************************************

class CRhsRegistry
{

// Methods

public:
  CRhsRegistry(void);
  CRhsRegistry(const char* Key, BOOL HKeyLocalMachine = FALSE);
  ~CRhsRegistry(void);

  BOOL SetKey(const char* Key, BOOL HKeyLocalMachine = FALSE);
  BOOL GetKey(char* Key, int Len, BOOL* HKeyLocalMachine = NULL);

  BOOL  WriteString(const char* Key, const char* String);
  BOOL  WriteInt(const char* Key, int Value);
  const char* GetString(const char* Key, const char* Default, int Len);
  int   GetInt(const char* Key, int Default);

// Variables

protected:
  BOOL m_HKeyLocalMachine;
  char m_Key[LEN_REGISTRYPATH+1];

};


//**********************************************************************
// End of CRhsRegistry
//**********************************************************************

#endif // _INC_CRHSREGISTRY

