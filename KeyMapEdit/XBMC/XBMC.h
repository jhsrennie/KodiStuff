//**********************************************************************
// XBMC.h
// ======
// This includes all the headers needed to make the XBMC stuff work
//**********************************************************************

#include "XBMC_keyboard.h"
#include "XBMC_vkeys.h"
#include "XBMC_keytable.h"

// From WinEventsWin32.cpp

XBMC_keysym *TranslateKey(WPARAM vkey, UINT scancode, XBMC_keysym *keysym, int pressed);


