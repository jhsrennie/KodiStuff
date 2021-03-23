//**********************************************************************
// Constants.h
// ===========
// Various constants
//**********************************************************************

#ifndef _INC_CONSTANTS
#define _INC_CONSTANTS

// Types of items in the key map

#define TYPE_ERROR   -1
#define TYPE_NONE    0
#define TYPE_COMMENT 1
#define TYPE_SECTION 2
#define TYPE_KEYDEF  3

// Buffer lengths

#define MAX_LENKEYMAPCOMMENT     127
#define MAX_LENKEYMAPSECTIONNAME 127
#define MAX_LENKEYMAPKEYNAME     127
#define MAX_LENKEYDEFACTION      127

// Section names

#define NUM_SECTIONNAMES 115
extern const char* SectionName[NUM_SECTIONNAMES];

// Key names

typedef struct
{ const char* keyname;
  int keycode;
} XBMCKEYNAME;

#define NUM_KEYNAMES 151
extern XBMCKEYNAME KeyName[NUM_KEYNAMES];

// Actions

#define NUM_ACTIONS 256
extern const char* Action[NUM_ACTIONS];

#endif // _INC_CONSTANTS
