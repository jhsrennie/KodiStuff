//**********************************************************************
// Constants.cpp
// =============
// Various constants
//**********************************************************************

#include <windows.h>
#include "Constants.h"
#include "XBMC/XBMC_vkeys.h"

// Section names
// The "global" section is always 0
// The rest of the sections are in alphabetical order

const char* SectionName[NUM_SECTIONNAMES] =
{
  "global",
  "accesspoints",
  "addonbrowser",
  "addoninformation",
  "addonsettings",
  "appearancesettings",
  "busydialog",
  "contentsettings",
  "contextmenu",
  "extendedprogressdialog",
  "favourites",
  "filebrowser",
  "filemanager",
  "files",
  "filestackingdialog",
  "fullscreeninfo",
  "fullscreenlivetv",
  "fullscreenvideo",
  "gamepadinput",
  "guicalibration",
  "home",
  "infodialog",
  "karaoke",
  "karaokelargeselector",
  "karaokeselector",
  "locksettings",
  "loginscreen",
  "mediafilter",
  "mediasource",
  "movieinformation",
  "music",
  "musicfiles",
  "musicinformation",
  "musiclibrary",
  "musicosd",
  "musicoverlay",
  "musicplaylist",
  "musicplaylisteditor",
  "musicsettings",
  "mutebug",
  "networksettings",
  "networksetup",
  "numericinput",
  "okdialog",
  "osdaudiosettings",
  "osdvideosettings",
  "peripherals",
  "peripheralsettings",
  "pictureinfo",
  "pictures",
  "picturessettings",
  "playercontrols",
  "profiles",
  "profilesettings",
  "programs",
  "programssettings",
  "progressdialog",
  "pvr",
  "pvrchannelmanager",
  "pvrchannelscan",
  "pvrgroupmanager",
  "pvrguideinfo",
  "pvrguidesearch",
  "pvrosdchannels",
  "pvrosdcutter",
  "pvrosddirector",
  "pvrosdguide",
  "pvrosdteletext",
  "pvrrecordinginfo",
  "pvrsettings",
  "pvrtimersetting",
  "pvrupdateprogress",
  "screencalibration",
  "screensaver",
  "scripts",
  "seekbar",
  "selectdialog",
  "servicesettings",
  "settings",
  "shutdownmenu",
  "skinsettings",
  "sliderdialog",
  "slideshow",
  "smartplaylisteditor",
  "smartplaylistrule",
  "songinformation",
  "startup",
  "startwindow",
  "submenu",
  "systeminfo",
  "systemsettings",
  "teletext",
  "testpattern",
  "textviewer",
  "tv",
  "tvsettings",
  "video",
  "videobookmarks",
  "videofiles",
  "videolibrary",
  "videomenu",
  "videoosd",
  "videooverlay",
  "videoplaylist",
  "videos",
  "videossettings",
  "videotimeseek",
  "virtualkeyboard",
  "visualisation",
  "visualisationpresetlist",
  "visualisationsettings",
  "volumebar",
  "weather",
  "weathersettings",
  "yesnodialog"
};


// Key names
// The "key" name is always 0
// The rest of the keys are in alphabetical order

XBMCKEYNAME KeyName[NUM_KEYNAMES] =
{
  {"key", 0x00}

, { "a" , XBMCVK_A }
, { "b" , XBMCVK_B }
, { "c" , XBMCVK_C }
, { "d" , XBMCVK_D }
, { "e" , XBMCVK_E }
, { "f" , XBMCVK_F }
, { "g" , XBMCVK_G }
, { "h" , XBMCVK_H }
, { "i" , XBMCVK_I }
, { "j" , XBMCVK_J }
, { "k" , XBMCVK_K }
, { "l" , XBMCVK_L }
, { "m" , XBMCVK_M }
, { "n" , XBMCVK_N }
, { "o" , XBMCVK_O }
, { "p" , XBMCVK_P }
, { "q" , XBMCVK_Q }
, { "r" , XBMCVK_R }
, { "s" , XBMCVK_S }
, { "t" , XBMCVK_T }
, { "u" , XBMCVK_U }
, { "v" , XBMCVK_V }
, { "w" , XBMCVK_W }
, { "x" , XBMCVK_X }
, { "y" , XBMCVK_Y }
, { "z" , XBMCVK_Z }

, { "zero" , XBMCVK_0 }
, { "one" , XBMCVK_1 }
, { "two" , XBMCVK_2 }
, { "three" , XBMCVK_3 }
, { "four" , XBMCVK_4 }
, { "five" , XBMCVK_5 }
, { "six" , XBMCVK_6 }
, { "seven" , XBMCVK_7 }
, { "eight" , XBMCVK_8 }
, { "nine" , XBMCVK_9 }

, { "ampersand" , XBMCVK_AMPERSAND }
, { "asterisk" , XBMCVK_ASTERISK }
, { "at" , XBMCVK_AT }
, { "backslash" , XBMCVK_BACKSLASH }
, { "backspace" , XBMCVK_BACK }
, { "browser_back" , XBMCVK_BROWSER_BACK }
, { "browser_favorites" , XBMCVK_BROWSER_FAVORITES }
, { "browser_forward" , XBMCVK_BROWSER_FORWARD }
, { "browser_home" , XBMCVK_BROWSER_HOME }
, { "browser_refresh" , XBMCVK_BROWSER_REFRESH }
, { "browser_search" , XBMCVK_BROWSER_SEARCH }
, { "browser_stop" , XBMCVK_BROWSER_STOP }
, { "capslock" , XBMCVK_CAPSLOCK }
, { "caret" , XBMCVK_CARET }
, { "closebrace" , XBMCVK_RIGHTBRACE }
, { "closesquarebracket" , XBMCVK_RIGHTBRACKET }
, { "colon" , XBMCVK_COLON }
, { "comma" , XBMCVK_COMMA }
, { "delete" , XBMCVK_DELETE }
, { "dollar" , XBMCVK_DOLLAR }
, { "doublequote" , XBMCVK_QUOTEDBL }
, { "down" , XBMCVK_DOWN }
, { "end" , XBMCVK_END }
, { "enter", XBMCVK_NUMPADENTER }
, { "equals" , XBMCVK_EQUALS }
, { "esc" , XBMCVK_ESCAPE } // Allowed abbreviation for "escape"
, { "escape" , XBMCVK_ESCAPE }
, { "exclaim" , XBMCVK_EXCLAIM }
, { "f1", XBMCVK_F1 }
, { "f10", XBMCVK_F10 }
, { "f11", XBMCVK_F11 }
, { "f12", XBMCVK_F12 }
, { "f13", XBMCVK_F13 }
, { "f14", XBMCVK_F14 }
, { "f15", XBMCVK_F15 }
, { "f2", XBMCVK_F2 }
, { "f3", XBMCVK_F3 }
, { "f4", XBMCVK_F4 }
, { "f5", XBMCVK_F5 }
, { "f6", XBMCVK_F6 }
, { "f7", XBMCVK_F7 }
, { "f8", XBMCVK_F8 }
, { "f9", XBMCVK_F9 }
, { "forwardslash" , XBMCVK_SLASH }
, { "greaterthan" , XBMCVK_GREATER }
, { "hash" , XBMCVK_HASH }
, { "home" , XBMCVK_HOME }
, { "insert" , XBMCVK_INSERT }
, { "launch_app1_pc_icon" , XBMCVK_LAUNCH_APP1 }
, { "launch_app2_pc_icon" , XBMCVK_LAUNCH_APP2 }
, { "launch_file_browser" , XBMCVK_LAUNCH_FILE_BROWSER }
, { "launch_mail" , XBMCVK_LAUNCH_MAIL }
, { "launch_media_center" , XBMCVK_LAUNCH_MEDIA_CENTER }
, { "launch_media_select" , XBMCVK_LAUNCH_MEDIA_SELECT }
, { "left" , XBMCVK_LEFT }
, { "leftalt" , XBMCVK_LMENU }
, { "leftbracket" , XBMCVK_LEFTPAREN }
, { "leftctrl" , XBMCVK_LCONTROL }
, { "leftquote" , XBMCVK_BACKQUOTE }
, { "leftshift" , XBMCVK_LSHIFT }
, { "leftwindows" , XBMCVK_LWIN }
, { "lessthan" , XBMCVK_LESS }
, { "menu" , XBMCVK_MENU }
, { "minus" , XBMCVK_MINUS }
, { "next_track" , XBMCVK_MEDIA_NEXT_TRACK }
, { "numlock" , XBMCVK_NUMLOCK }
, { "numpaddivide", XBMCVK_NUMPADDIVIDE }
, { "numpadeight", XBMCVK_NUMPAD8 }
, { "numpadfive", XBMCVK_NUMPAD5 }
, { "numpadfour", XBMCVK_NUMPAD4 }
, { "numpadminus", XBMCVK_NUMPADMINUS }
, { "numpadnine", XBMCVK_NUMPAD9 }
, { "numpadone", XBMCVK_NUMPAD1 }
, { "numpadperiod", XBMCVK_NUMPADPERIOD }
, { "numpadplus", XBMCVK_NUMPADPLUS }
, { "numpadseven", XBMCVK_NUMPAD7 }
, { "numpadsix", XBMCVK_NUMPAD6 }
, { "numpadthree", XBMCVK_NUMPAD3 }
, { "numpadtimes", XBMCVK_NUMPADTIMES }
, { "numpadtwo", XBMCVK_NUMPAD2 }
, { "numpadzero", XBMCVK_NUMPAD0 }
, { "openbrace" , XBMCVK_LEFTBRACE }
, { "opensquarebracket" , XBMCVK_LEFTBRACKET }
, { "pagedown" , XBMCVK_PAGEDOWN }
, { "pageup" , XBMCVK_PAGEUP }
, { "pause" , XBMCVK_PAUSE }
, { "percent" , XBMCVK_PERCENT }
, { "period" , XBMCVK_PERIOD }
, { "pipe" , XBMCVK_PIPE }
, { "play_pause" , XBMCVK_MEDIA_PLAY_PAUSE }
, { "plus" , XBMCVK_PLUS }
, { "power" , XBMCVK_POWER }
, { "prev_track" , XBMCVK_MEDIA_PREV_TRACK }
, { "printscreen" , XBMCVK_PRINTSCREEN }
, { "questionmark" , XBMCVK_QUESTION }
, { "quote" , XBMCVK_QUOTE }
, { "return" , XBMCVK_RETURN }
, { "right" , XBMCVK_RIGHT }
, { "rightbracket" , XBMCVK_RIGHTPAREN }
, { "rightctrl" , XBMCVK_RCONTROL }
, { "rightshift" , XBMCVK_RSHIFT }
, { "rightwindows" , XBMCVK_RWIN }
, { "scrolllock" , XBMCVK_SCROLLLOCK }
, { "semicolon" , XBMCVK_SEMICOLON }
, { "sleep" , XBMCVK_SLEEP }
, { "space" , XBMCVK_SPACE }
, { "stop" , XBMCVK_MEDIA_STOP }
, { "tab" , XBMCVK_TAB }
, { "tilde" , XBMCVK_TILDE }
, { "underline" , XBMCVK_UNDERSCORE }
, { "up" , XBMCVK_UP }
, { "volume_down" , XBMCVK_VOLUME_DOWN }
, { "volume_mute" , XBMCVK_VOLUME_MUTE }
, { "volume_up" , XBMCVK_VOLUME_UP }
};


// Actions
// Simple actions first, then functions

const char* Action[NUM_ACTIONS] =
{
  "noop",
  "analogfastforward",
  "analogmove",
  "analogrewind",
  "analogseekback",
  "analogseekforward",
  "aspectratio",
  "audiodelay",
  "audiodelayminus",
  "audiodelayplus",
  "audionextlanguage",
  "audiotoggledigital",
  "back",
  "backspace",
  "bigstepback",
  "bigstepforward",
  "blue",
  "channeldown",
  "channelup",
  "close",
  "codecinfo",
  "contextmenu",
  "copy",
  "cursorleft",
  "cursorright",
  "decreasepar",
  "decreaserating",
  "decreasevisrating",
  "delete",
  "doubleclick",
  "down",
  "enter",
  "fastforward",
  "filter",
  "filterclear",
  "filtersms2",
  "filtersms3",
  "filtersms4",
  "filtersms5",
  "filtersms6",
  "filtersms7",
  "filtersms8",
  "filtersms9",
  "firstpage",
  "fullscreen",
  "green",
  "guiprofile",
  "hidesubmenu",
  "highlight",
  "increasepar",
  "increaserating",
  "increasevisrating",
  "info",
  "jumpsms2",
  "jumpsms3",
  "jumpsms4",
  "jumpsms5",
  "jumpsms6",
  "jumpsms7",
  "jumpsms8",
  "jumpsms9",
  "lastpage",
  "left",
  "leftclick",
  "lockpreset",
  "middleclick",
  "mousedrag",
  "mousemove",
  "move",
  "moveitemdown",
  "moveitemup",
  "mplayerosd",
  "mute",
  "nextcalibration",
  "nextchannelgroup",
  "nextletter",
  "nextpicture",
  "nextpreset",
  "nextresolution",
  "nextscene",
  "nextsubtitle",
  "number0",
  "number1",
  "number2",
  "number3",
  "number4",
  "number5",
  "number6",
  "number7",
  "number8",
  "number9",
  "osd",
  "osddown",
  "osdleft",
  "osdright",
  "osdselect",
  "osdup",
  "osdvalueminus",
  "osdvalueplus",
  "pagedown",
  "pageup",
  "parentdir",
  "parentfolder",
  "pause",
  "play",
  "playlist",
  "playpause",
  "presetlist",
  "previouschannelgroup",
  "previousmenu",
  "previouspicture",
  "previouspreset",
  "previousscene",
  "prevletter",
  "queue",
  "randompreset",
  "red",
  "reloadkeymaps",
  "rename",
  "resetcalibration",
  "rewind",
  "right",
  "rightclick",
  "rotate",
  "rotateccw",
  "scanitem",
  "screenshot",
  "scrolldown",
  "scrollup",
  "select",
  "shift",
  "showpreset",
  "showsubtitles",
  "showtime",
  "showvideomenu",
  "skipnext",
  "skipprevious",
  "smallstepback",
  "stepback",
  "stepforward",
  "stop",
  "subtitlealign",
  "subtitledelay",
  "subtitledelayminus",
  "subtitledelayplus",
  "subtitleshiftdown",
  "subtitleshiftup",
  "symbols",
  "togglefullscreen",
  "togglewatched",
  "up",
  "verticalshiftdown",
  "verticalshiftup",
  "volampdown",
  "volampup",
  "volumedown",
  "volumeup",
  "wheeldown",
  "wheelup",
  "yellow",
  "zoomin",
  "zoomlevel1",
  "zoomlevel2",
  "zoomlevel3",
  "zoomlevel4",
  "zoomlevel5",
  "zoomlevel6",
  "zoomlevel7",
  "zoomlevel8",
  "zoomlevel9",
  "zoomnormal",
  "zoomout",
  "Action",
  "ActivateWindow(window[,dir,return])",
  "Addon.Default.OpenSettings",
  "AlarmClock(name,command,time[,silent])",
  "CancelAlarm(name)",
  "CleanLibrary(database)",
  "ClearProperty",
  "Container.NextSortMethod",
  "Container.NextViewMode",
  "Container.PreviousSortMethod",
  "Container.PreviousViewMode",
  "Container.Refresh",
  "Container.SetSortMethod",
  "Container.SetViewMode",
  "Container.SetViewMode(id)",
  "Container.SortDirection",
  "Container.Update",
  "Control.Message(id,message,[windowid])",
  "Control.Move(id,offset)",
  "Control.SetFocus(id,position)",
  "Credits",
  "Dialog.Close(dialog[,force])",
  "EjectTray()",
  "Example:",
  "exportlibrary(music|video,false,filepath)",
  "exportlibrary(music|video,true,thumbs,overwrite,actorthumbs)",
  "Extract",
  "Hibernate",
  "LastFM.Ban",
  "LastFM.Love",
  "LCD.Resume",
  "LCD.Suspend",
  "LIRC.Send(command)",
  "LIRC.Start",
  "LIRC.Stop",
  "LoadProfile(profilename,['prompt'])",
  "Mastermode",
  "Minimize",
  "Mute",
  "Notification(header,message[,time,image])",
  "PlayDVD",
  "PlayerControl(command)",
  "Playlist.Clear",
  "Playlist.PlayOffset",
  "PlayMedia(media[,1])",
  "PlayWith()",
  "Powerdown",
  "Quit",
  "Reboot",
  "RecursiveSlideShow(dir)",
  "RefreshRSS",
  "ReloadSkin()",
  "ReplaceWindow(window,dir)",
  "Resolution",
  "RestartApp",
  "RipCD",
  "RunAppleScript(script[,args]*)",
  "RunPlugin(plugin)",
  "RunScript(script[,args]*)",
  "SendClick(windowid,id)",
  "SetProperty(key,value)",
  "SetVolume(percent)",
  "ShutDown",
  "Skin.Reset(setting)",
  "Skin.ResetSettings",
  "Skin.SetAddon(string,type)",
  "Skin.SetBool(setting)",
  "Skin.SetFile(string,mask,folderpath)",
  "Skin.SetImage(string[,value])",
  "Skin.SetLargeImage(string[,value])",
  "Skin.SetNumeric(numeric[,value])",
  "Skin.SetPath(string[,value])",
  "Skin.SetString(string[,value])",
  "Skin.Theme",
  "Skin.ToggleSetting(setting)",
  "SlideShow(dir",
  "Suspend",
  "System.Exec",
  "System.ExecWait",
  "System.LogOff",
  "TakeScreenshot",
  "UpdateAddonRepos",
  "UpdateLibrary(database,[path])",
  "WakeOnLan(mac)"
};


