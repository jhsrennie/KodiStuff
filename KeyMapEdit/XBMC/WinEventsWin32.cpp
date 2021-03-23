//**********************************************************************
// WinEventsWin32.cpp
// ==================
// This is an edited version of the XBMC WinEventsWin32.cpp file
//**********************************************************************

#include <windows.h>
#include "XBMC_keyboard.h"
#include "XBMC_vkeys.h"

#define XBMC_arraysize(array)	(sizeof(array)/sizeof(array[0]))

#define EXTKEYPAD(keypad) ((scancode & 0x100)?(mvke):(keypad))

#define uint8_t unsigned char
#define uint16_t unsigned short
#define uint32_t unsigned int
#define uint64_t unsigned long long

static BOOL VK_keymapInitialised = FALSE;
static XBMCKey VK_keymap[XBMCK_LAST];
static HKL hLayoutUS = NULL;

int XBMC_TranslateUNICODE = 1;

void DIB_InitOSKeymap()
{
  char current_layout[KL_NAMELENGTH];

  GetKeyboardLayoutName(current_layout);

  hLayoutUS = LoadKeyboardLayout("00000409", KLF_NOTELLSHELL);
  if (!hLayoutUS)
    hLayoutUS = GetKeyboardLayout(0);

  LoadKeyboardLayout(current_layout, KLF_ACTIVATE);

  /* Map the VK keysyms */
  for (int i = 0; i < XBMC_arraysize(VK_keymap); ++i)
    VK_keymap[i] = XBMCK_UNKNOWN;

  VK_keymap[VK_BACK] = XBMCK_BACKSPACE;
  VK_keymap[VK_TAB] = XBMCK_TAB;
  VK_keymap[VK_CLEAR] = XBMCK_CLEAR;
  VK_keymap[VK_RETURN] = XBMCK_RETURN;
  VK_keymap[VK_PAUSE] = XBMCK_PAUSE;
  VK_keymap[VK_ESCAPE] = XBMCK_ESCAPE;
  VK_keymap[VK_SPACE] = XBMCK_SPACE;
  VK_keymap[VK_APOSTROPHE] = XBMCK_QUOTE;
  VK_keymap[VK_COMMA] = XBMCK_COMMA;
  VK_keymap[VK_MINUS] = XBMCK_MINUS;
  VK_keymap[VK_PERIOD] = XBMCK_PERIOD;
  VK_keymap[VK_SLASH] = XBMCK_SLASH;
  VK_keymap[VK_0] = XBMCK_0;
  VK_keymap[VK_1] = XBMCK_1;
  VK_keymap[VK_2] = XBMCK_2;
  VK_keymap[VK_3] = XBMCK_3;
  VK_keymap[VK_4] = XBMCK_4;
  VK_keymap[VK_5] = XBMCK_5;
  VK_keymap[VK_6] = XBMCK_6;
  VK_keymap[VK_7] = XBMCK_7;
  VK_keymap[VK_8] = XBMCK_8;
  VK_keymap[VK_9] = XBMCK_9;
  VK_keymap[VK_SEMICOLON] = XBMCK_SEMICOLON;
  VK_keymap[VK_EQUALS] = XBMCK_EQUALS;
  VK_keymap[VK_LBRACKET] = XBMCK_LEFTBRACKET;
  VK_keymap[VK_BACKSLASH] = XBMCK_BACKSLASH;
  VK_keymap[VK_OEM_102] = XBMCK_BACKSLASH;
  VK_keymap[VK_RBRACKET] = XBMCK_RIGHTBRACKET;
  VK_keymap[VK_GRAVE] = XBMCK_BACKQUOTE;
  VK_keymap[VK_BACKTICK] = XBMCK_BACKQUOTE;
  VK_keymap[VK_A] = XBMCK_a;
  VK_keymap[VK_B] = XBMCK_b;
  VK_keymap[VK_C] = XBMCK_c;
  VK_keymap[VK_D] = XBMCK_d;
  VK_keymap[VK_E] = XBMCK_e;
  VK_keymap[VK_F] = XBMCK_f;
  VK_keymap[VK_G] = XBMCK_g;
  VK_keymap[VK_H] = XBMCK_h;
  VK_keymap[VK_I] = XBMCK_i;
  VK_keymap[VK_J] = XBMCK_j;
  VK_keymap[VK_K] = XBMCK_k;
  VK_keymap[VK_L] = XBMCK_l;
  VK_keymap[VK_M] = XBMCK_m;
  VK_keymap[VK_N] = XBMCK_n;
  VK_keymap[VK_O] = XBMCK_o;
  VK_keymap[VK_P] = XBMCK_p;
  VK_keymap[VK_Q] = XBMCK_q;
  VK_keymap[VK_R] = XBMCK_r;
  VK_keymap[VK_S] = XBMCK_s;
  VK_keymap[VK_T] = XBMCK_t;
  VK_keymap[VK_U] = XBMCK_u;
  VK_keymap[VK_V] = XBMCK_v;
  VK_keymap[VK_W] = XBMCK_w;
  VK_keymap[VK_X] = XBMCK_x;
  VK_keymap[VK_Y] = XBMCK_y;
  VK_keymap[VK_Z] = XBMCK_z;
  VK_keymap[VK_DELETE] = XBMCK_DELETE;

  VK_keymap[VK_NUMPAD0] = XBMCK_KP0;
  VK_keymap[VK_NUMPAD1] = XBMCK_KP1;
  VK_keymap[VK_NUMPAD2] = XBMCK_KP2;
  VK_keymap[VK_NUMPAD3] = XBMCK_KP3;
  VK_keymap[VK_NUMPAD4] = XBMCK_KP4;
  VK_keymap[VK_NUMPAD5] = XBMCK_KP5;
  VK_keymap[VK_NUMPAD6] = XBMCK_KP6;
  VK_keymap[VK_NUMPAD7] = XBMCK_KP7;
  VK_keymap[VK_NUMPAD8] = XBMCK_KP8;
  VK_keymap[VK_NUMPAD9] = XBMCK_KP9;
  VK_keymap[VK_DECIMAL] = XBMCK_KP_PERIOD;
  VK_keymap[VK_DIVIDE] = XBMCK_KP_DIVIDE;
  VK_keymap[VK_MULTIPLY] = XBMCK_KP_MULTIPLY;
  VK_keymap[VK_SUBTRACT] = XBMCK_KP_MINUS;
  VK_keymap[VK_ADD] = XBMCK_KP_PLUS;

  VK_keymap[VK_UP] = XBMCK_UP;
  VK_keymap[VK_DOWN] = XBMCK_DOWN;
  VK_keymap[VK_RIGHT] = XBMCK_RIGHT;
  VK_keymap[VK_LEFT] = XBMCK_LEFT;
  VK_keymap[VK_INSERT] = XBMCK_INSERT;
  VK_keymap[VK_HOME] = XBMCK_HOME;
  VK_keymap[VK_END] = XBMCK_END;
  VK_keymap[VK_PRIOR] = XBMCK_PAGEUP;
  VK_keymap[VK_NEXT] = XBMCK_PAGEDOWN;

  VK_keymap[VK_F1] = XBMCK_F1;
  VK_keymap[VK_F2] = XBMCK_F2;
  VK_keymap[VK_F3] = XBMCK_F3;
  VK_keymap[VK_F4] = XBMCK_F4;
  VK_keymap[VK_F5] = XBMCK_F5;
  VK_keymap[VK_F6] = XBMCK_F6;
  VK_keymap[VK_F7] = XBMCK_F7;
  VK_keymap[VK_F8] = XBMCK_F8;
  VK_keymap[VK_F9] = XBMCK_F9;
  VK_keymap[VK_F10] = XBMCK_F10;
  VK_keymap[VK_F11] = XBMCK_F11;
  VK_keymap[VK_F12] = XBMCK_F12;
  VK_keymap[VK_F13] = XBMCK_F13;
  VK_keymap[VK_F14] = XBMCK_F14;
  VK_keymap[VK_F15] = XBMCK_F15;

  VK_keymap[VK_NUMLOCK] = XBMCK_NUMLOCK;
  VK_keymap[VK_CAPITAL] = XBMCK_CAPSLOCK;
  VK_keymap[VK_SCROLL] = XBMCK_SCROLLOCK;
  VK_keymap[VK_RSHIFT] = XBMCK_RSHIFT;
  VK_keymap[VK_LSHIFT] = XBMCK_LSHIFT;
  VK_keymap[VK_RCONTROL] = XBMCK_RCTRL;
  VK_keymap[VK_LCONTROL] = XBMCK_LCTRL;
  VK_keymap[VK_RMENU] = XBMCK_RALT;
  VK_keymap[VK_LMENU] = XBMCK_LALT;
  VK_keymap[VK_RWIN] = XBMCK_RSUPER;
  VK_keymap[VK_LWIN] = XBMCK_LSUPER;

  VK_keymap[VK_HELP] = XBMCK_HELP;
#ifdef VK_PRINT
  VK_keymap[VK_PRINT] = XBMCK_PRINT;
#endif
  VK_keymap[VK_SNAPSHOT] = XBMCK_PRINT;
  VK_keymap[VK_CANCEL] = XBMCK_BREAK;
  VK_keymap[VK_APPS] = XBMCK_MENU;

    VK_keymap[VK_BROWSER_BACK]        = XBMCK_BROWSER_BACK;
    VK_keymap[VK_BROWSER_FORWARD]     = XBMCK_BROWSER_FORWARD;
    VK_keymap[VK_BROWSER_REFRESH]     = XBMCK_BROWSER_REFRESH;
    VK_keymap[VK_BROWSER_STOP]        = XBMCK_BROWSER_STOP;
    VK_keymap[VK_BROWSER_SEARCH]      = XBMCK_BROWSER_SEARCH;
    VK_keymap[VK_BROWSER_FAVORITES]   = XBMCK_BROWSER_FAVORITES;
    VK_keymap[VK_BROWSER_HOME]        = XBMCK_BROWSER_HOME;
    VK_keymap[VK_VOLUME_MUTE]         = XBMCK_VOLUME_MUTE;
    VK_keymap[VK_VOLUME_DOWN]         = XBMCK_VOLUME_DOWN;
    VK_keymap[VK_VOLUME_UP]           = XBMCK_VOLUME_UP;
    VK_keymap[VK_MEDIA_NEXT_TRACK]    = XBMCK_MEDIA_NEXT_TRACK;
    VK_keymap[VK_MEDIA_PREV_TRACK]    = XBMCK_MEDIA_PREV_TRACK;
    VK_keymap[VK_MEDIA_STOP]          = XBMCK_MEDIA_STOP;
    VK_keymap[VK_MEDIA_PLAY_PAUSE]    = XBMCK_MEDIA_PLAY_PAUSE;
    VK_keymap[VK_LAUNCH_MAIL]         = XBMCK_LAUNCH_MAIL;
    VK_keymap[VK_LAUNCH_MEDIA_SELECT] = XBMCK_LAUNCH_MEDIA_SELECT;
    VK_keymap[VK_LAUNCH_APP1]         = XBMCK_LAUNCH_APP1;
    VK_keymap[VK_LAUNCH_APP2]         = XBMCK_LAUNCH_APP2;
}

static int XBMC_MapVirtualKey(int scancode, int vkey)
{
  int mvke = MapVirtualKeyEx(scancode & 0xFF, 1, NULL);

  switch(vkey)
  { /* These are always correct */
    case VK_DIVIDE:
    case VK_MULTIPLY:
    case VK_SUBTRACT:
    case VK_ADD:
    case VK_LWIN:
    case VK_RWIN:
    case VK_APPS:
    /* These are already handled */
    case VK_LCONTROL:
    case VK_RCONTROL:
    case VK_LSHIFT:
    case VK_RSHIFT:
    case VK_LMENU:
    case VK_RMENU:
    case VK_SNAPSHOT:
    case VK_PAUSE:
      return vkey;
  }
  switch(mvke)
  { /* Distinguish between keypad and extended keys */
    case VK_INSERT: return EXTKEYPAD(VK_NUMPAD0);
    case VK_DELETE: return EXTKEYPAD(VK_DECIMAL);
    case VK_END:    return EXTKEYPAD(VK_NUMPAD1);
    case VK_DOWN:   return EXTKEYPAD(VK_NUMPAD2);
    case VK_NEXT:   return EXTKEYPAD(VK_NUMPAD3);
    case VK_LEFT:   return EXTKEYPAD(VK_NUMPAD4);
    case VK_CLEAR:  return EXTKEYPAD(VK_NUMPAD5);
    case VK_RIGHT:  return EXTKEYPAD(VK_NUMPAD6);
    case VK_HOME:   return EXTKEYPAD(VK_NUMPAD7);
    case VK_UP:     return EXTKEYPAD(VK_NUMPAD8);
    case VK_PRIOR:  return EXTKEYPAD(VK_NUMPAD9);
  }
  return mvke ? mvke : vkey;
}

XBMC_keysym *TranslateKey(WPARAM vkey, UINT scancode, XBMC_keysym *keysym, int pressed)
{ uint16_t mod;
  uint8_t keystate[256];

  // Initialise the keymap if required
  if (!VK_keymapInitialised)
  {
    DIB_InitOSKeymap();
    VK_keymapInitialised = TRUE;
  }

  /* Set the keysym information */
  keysym->scancode = (unsigned char) scancode;
  keysym->unicode = 0;

  if ((vkey == VK_RETURN) && (scancode & 0x100))
  {
    /* No VK_ code for the keypad enter key */
    keysym->sym = XBMCK_KP_ENTER;
  }
  else
  {
    keysym->sym = VK_keymap[XBMC_MapVirtualKey(scancode, vkey)];
  }

  // Attempt to convert the keypress to a UNICODE character
  GetKeyboardState(keystate);

  if ( pressed && XBMC_TranslateUNICODE )
  { uint16_t  wchars[2];

    /* Numlock isn't taken into account in ToUnicode,
    * so we handle it as a special case here */
    if ((keystate[VK_NUMLOCK] & 1) && vkey >= VK_NUMPAD0 && vkey <= VK_NUMPAD9)
    {
      keysym->unicode = vkey - VK_NUMPAD0 + '0';
    }
    else if (ToUnicode((UINT)vkey, scancode, keystate, (LPWSTR)wchars, sizeof(wchars)/sizeof(wchars[0]), 0) > 0)
    {
      keysym->unicode = wchars[0];
    }
  }

  // Set the modifier bitmap

  mod = (uint16_t) XBMCKMOD_NONE;

  // If left control and right alt are down this usually means that
  // AltGr is down
  if ((keystate[VK_LCONTROL] & 0x80) && (keystate[VK_RMENU] & 0x80))
  {
    mod |= XBMCKMOD_MODE;
  }
  else
  {
    if (keystate[VK_LCONTROL] & 0x80) mod |= XBMCKMOD_LCTRL;
    if (keystate[VK_RMENU]    & 0x80) mod |= XBMCKMOD_RALT;
  }

  // Check the remaining modifiers
  if (keystate[VK_LSHIFT]   & 0x80) mod |= XBMCKMOD_LSHIFT;
  if (keystate[VK_RSHIFT]   & 0x80) mod |= XBMCKMOD_RSHIFT;
  if (keystate[VK_RCONTROL] & 0x80) mod |= XBMCKMOD_RCTRL;
  if (keystate[VK_LMENU]    & 0x80) mod |= XBMCKMOD_LALT;
  if (keystate[VK_LWIN]     & 0x80) mod |= XBMCKMOD_LSUPER;
  if (keystate[VK_RWIN]     & 0x80) mod |= XBMCKMOD_LSUPER;
  keysym->mod = (XBMCMod) mod;

  // Return the updated keysym
  return(keysym);
}


