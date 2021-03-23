########################################################################
# Makefile for KeyMapEdit
########################################################################

# Project name

projname = KeyMapEdit

# Tools

cc       = cl
link     = link

# Flags

cflags   = -c -W3 -Ox -D_X86_=1 -DWIN32
lflags   = -subsystem:windows -entry:WinMainCRTStartup
# cflags   = -c -W3 -Od -Zi -D_X86_=1 -DWIN32
# lflags   = -subsystem:windows -entry:WinMainCRTStartup -debug:full -debugtype:cv

# Objects

objs     = KeyMapEdit.obj CMainWnd.obj CKeyDetector.obj CKeymapControl.obj \
           CKeymapFile.obj CKeymapObjects.obj Constants.obj dlgAbout.obj \
           dlgComment.obj dlgKeyDef.obj dlgSection.obj rhsfont.obj rhsreg.obj \
           WinEventsWin32.obj XBMC_keytable.obj \
           tinystr.obj tinyxml.obj tinyxmlerror.obj tinyxmlparser.obj

# Libraries

libs     = kernel32.lib user32.lib gdi32.lib \
           comdlg32.lib shell32.lib advapi32.lib comctl32.lib

# Targets

all: $(projname).exe

$(projname).exe: $(objs) $(projname).res
    $(link) $(lflags) -out:$(projname).exe $(objs) $(projname).res $(libs)

$(projname).res: $(projname).rc
    rc -r -DWIN32 $(projname).rc

KeyMapEdit.obj: KeyMapEdit.cpp
   $(cc) $(cflags) KeyMapEdit.cpp -FoKeyMapEdit.obj

CMainWnd.obj: CMainWnd.cpp
   $(cc) $(cflags) CMainWnd.cpp -FoCMainWnd.obj

CKeyDetector.obj: CKeyDetector.cpp
   $(cc) $(cflags) CKeyDetector.cpp -FoCKeyDetector.obj

CKeymapControl.obj: CKeymapControl.cpp
   $(cc) $(cflags) CKeymapControl.cpp -FoCKeymapControl.obj

CKeymapFile.obj: CKeymapFile.cpp
   $(cc) $(cflags) CKeymapFile.cpp -FoCKeymapFile.obj

CKeymapObjects.obj: CKeymapObjects.cpp
   $(cc) $(cflags) CKeymapObjects.cpp -FoCKeymapObjects.obj

Constants.obj: Constants.cpp
   $(cc) $(cflags) Constants.cpp -FoConstants.obj

dlgAbout.obj: dlgAbout.cpp
   $(cc) $(cflags) dlgAbout.cpp -FodlgAbout.obj

dlgComment.obj: dlgComment.cpp
   $(cc) $(cflags) dlgComment.cpp -FodlgComment.obj

dlgKeyDef.obj: dlgKeyDef.cpp
   $(cc) $(cflags) dlgKeyDef.cpp -FodlgKeyDef.obj

dlgSection.obj: dlgSection.cpp
   $(cc) $(cflags) dlgSection.cpp -FodlgSection.obj

rhsfont.obj: rhsfont.cpp
   $(cc) $(cflags) rhsfont.cpp -Forhsfont.obj

rhsreg.obj: rhsreg.cpp
   $(cc) $(cflags) rhsreg.cpp -Forhsreg.obj


WinEventsWin32.obj: XBMC\WinEventsWin32.cpp
   $(cc) $(cflags) XBMC\WinEventsWin32.cpp -FoWinEventsWin32.obj

XBMC_keytable.obj: XBMC\XBMC_keytable.cpp
   $(cc) $(cflags) XBMC\XBMC_keytable.cpp -FoXBMC_keytable.obj


tinystr.obj: tinyxml\tinystr.cpp
   $(cc) $(cflags) tinyxml\tinystr.cpp -Fotinystr.obj

tinyxml.obj: tinyxml\tinyxml.cpp
   $(cc) $(cflags) tinyxml\tinyxml.cpp -Fotinyxml.obj

tinyxmlerror.obj: tinyxml\tinyxmlerror.cpp
   $(cc) $(cflags) tinyxml\tinyxmlerror.cpp -Fotinyxmlerror.obj

tinyxmlparser.obj: tinyxml\tinyxmlparser.cpp
   $(cc) $(cflags) tinyxml\tinyxmlparser.cpp -Fotinyxmlparser.obj

