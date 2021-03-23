//**********************************************************************
// CKeymapFile
// ==============
//**********************************************************************

#ifndef STRICT
#define STRICT
#endif

#include <windows.h>
#include "KeyMapEdit.h"
#include "CKeymapControl.h"
#include "CKeymapFile.h"
#include "CKeymapObjects.h"
#include "tinyxml/tinyxml.h"


//**********************************************************************
// CKeymapFile
// --------------
//**********************************************************************

CKeymapFile::CKeymapFile(void)
{
  strcpy_s(m_LastError, LEN_LASTERROR+1, "");
}


CKeymapFile::~CKeymapFile(void)
{
}


//**********************************************************************
// CKeymapFile::SaveKeymap
// --------------------------
// Save the keymap to the specified file
//**********************************************************************

BOOL CKeymapFile::SaveKeymap(char* KeymapFile, CKeymapControl* KeymapControl)
{ int item_type, item_id;
  BOOL end_of_keymap, header_written;
  FILE* f;
  CKeymapComment comment;

// Open the keymap file

  if (fopen_s(&f, KeymapFile, "w") != 0)
  { strcpy_s(m_LastError, LEN_LASTERROR+1, GetLastErrorMessage());
    return FALSE;
  }

// Now retrieve the data from the CKeymapControl and write it as XML

  end_of_keymap = header_written = FALSE;

  for (item_id = 0; !end_of_keymap; item_id++)
  { item_type = KeymapControl->GetItemType(item_id);

    switch (item_type)
    {

// Check if we've reached the end of the list

      case TYPE_NONE:
      case TYPE_ERROR:
        end_of_keymap = TRUE;
        break;

// If we found a section call SaveKeymapSection to write the section
// and all the keydefs in it.

      case TYPE_SECTION:
        // Don't write the opening <keymap> until just before the first
        // section i.e. after opening comments.
        if (!header_written)
        { fprintf(f, "<keymap>\n");
          header_written = TRUE;
        }
        SaveKeymapSection(f, &item_id, KeymapControl);
        break;

// Comments are simple to write. This code will only be executed for
// comments at the start of the file i.e. before the first section.

      case TYPE_COMMENT:
        KeymapControl->GetComment(comment, item_id);
        fprintf(f, "<!--%s-->\n", comment.m_Comment);
        break;

// There are no other cases to consider. KeyDefs will only appear inside
// a section and they'll be written by SaveKeymapSection.

    }
  }

// Close the file

  fprintf(f, "</keymap>\n");
  fclose(f);

// Return indicating success

  return TRUE;
}


//**********************************************************************
// CKeymapFile::SaveKeymapSection
// ------------------------------
// Save the keymap section to the specified file
//**********************************************************************

BOOL CKeymapFile::SaveKeymapSection(FILE* KeymapFile, int* ItemID, CKeymapControl* KeymapControl)
{ int item_type, item_id;
  BOOL end_of_section;
  CKeymapSection section;
  CKeymapComment comment;
  CKeymapKeyDef  keydef;
  char s[256];

// Write the section

  item_id = *ItemID;

  KeymapControl->GetSection(section, item_id);

  fprintf(KeymapFile, "  <%s>\n", section.GetSection());
  fprintf(KeymapFile, "    <keyboard>\n");

// Now go through the keymap till we hit the next section or the end of
// the keymap.

  end_of_section = FALSE;

  for (item_id++; !end_of_section; item_id++)
  { item_type = KeymapControl->GetItemType(item_id);

    switch (item_type)
    {

// Check if we've reached the end of the list

      case TYPE_NONE:
      case TYPE_ERROR:
        end_of_section = TRUE;
        break;

// If we found a section that ends this section

      case TYPE_SECTION:
        end_of_section = TRUE;
        break;

// Comments are simple to write

      case TYPE_COMMENT:
        KeymapControl->GetComment(comment, item_id);
        fprintf(KeymapFile, "      <!--%s-->\n", comment.m_Comment);
        break;

// Write the keydef

      case TYPE_KEYDEF:
        KeymapControl->GetKeyDef(keydef, item_id);
        keydef.ToXML(s, 256);
        fprintf(KeymapFile, "      %s\n", s);
        break;
    }
  }

// Set the item id to the line before the section (or end of list) that
// ended the current section.

  *ItemID = item_id - 2;

// Close this section

  fprintf(KeymapFile, "    </keyboard>\n");
  fprintf(KeymapFile, "  </%s>\n", section.GetSection());

// Return indicating success

  return TRUE;
}


//**********************************************************************
// CKeymapFile::ReadKeymap
// -----------------------
// Read a keymap file and load it into the keymap control
//**********************************************************************

BOOL CKeymapFile::ReadKeymap(char* XMLFile, CKeymapControl* KeymapControl)
{ int element_type;
  TiXmlNode* keymap;
  TiXmlNode* section;
  CKeymapComment comment;
  char section_name[MAX_LENKEYMAPSECTIONNAME+1];

// Create a new TinyXML document and attempt to load it

  TiXmlDocument xmldoc(XMLFile);
	
	if (!xmldoc.LoadFile())
	{ sprintf_s(m_LastError, LEN_LASTERROR+1, "Line %d, column %d: %s", xmldoc.ErrorRow(), xmldoc.ErrorCol(), xmldoc.ErrorDesc());
	  return false;
	}

// We have a valid document so clear the current control contents

  KeymapControl->ClearList();

// Read any comments at the beginning of the file

  for (keymap = xmldoc.FirstChild(); keymap != 0; keymap = keymap->NextSibling())
  { element_type = keymap->Type();
    if (element_type != TiXmlNode::TINYXML_COMMENT)
      break;

    comment.SetComment(keymap->Value());
    KeymapControl->InsertComment(comment);
  }

  if (keymap == 0)
    return TRUE;

// We should be at the first node, which should be <keymap>

  strcpy_s(section_name, MAX_LENKEYMAPSECTIONNAME+1, keymap->Value());
  AnsiLower(section_name);
  
  if (strcmp(section_name, "keymap") != 0)
  { sprintf_s(m_LastError, LEN_LASTERROR+1, "The keymap file must start with <keymap>. The file %s starts with <%s>.", XMLFile, section_name);
    return FALSE;
  }

// At this point keymap is the top level node so we need to get the
// section nodes from it

  for (section = keymap->FirstChild(); section != 0; section = section->NextSibling())
  { element_type = section->Type();

    switch (element_type)
    { case TiXmlNode::TINYXML_COMMENT:
        comment.SetComment(keymap->Value());
        KeymapControl->InsertComment(comment);
        break;

      case TiXmlNode::TINYXML_ELEMENT:
        if (!ReadKeymapSection(section, KeymapControl))
          return FALSE;
        break;
    }
  }

// Return indicating success

  return true;
}


//**********************************************************************
// CKeymapFile::ReadKeymapSection
// ---------------------------------
// Read a keymap section
//**********************************************************************

BOOL CKeymapFile::ReadKeymapSection(TiXmlNode* Section, CKeymapControl* KeymapControl)
{ int element_type;
  TiXmlNode* subsection;
  TiXmlNode* keydef;
  CKeymapSection section;
  CKeymapComment comment;
  char sectionname[MAX_LENKEYMAPSECTIONNAME+1],
       subsectionname[MAX_LENKEYMAPSECTIONNAME+1];

// Add the section name to the list

  strcpy_s(sectionname, MAX_LENKEYMAPSECTIONNAME+1, Section->Value());
  AnsiLower(sectionname);

  if (!section.SetSection(sectionname))
  { sprintf_s(m_LastError, LEN_LASTERROR+1, "Unknown section name \"%s\".", sectionname);
    return FALSE;
  }

  KeymapControl->AppendSection(section);

// Find the first child section: this must be <keyboard>. Note there may
// be comments before the <keyboard> node.

  for (subsection = Section->FirstChild(); subsection != 0; subsection = subsection->NextSibling())
  { element_type = subsection->Type();

    if (element_type == TiXmlNode::TINYXML_COMMENT)
    { comment.SetComment(subsection->Value());
      KeymapControl->InsertComment(comment);
    }

    else if (element_type == TiXmlNode::TINYXML_ELEMENT)
    { strcpy_s(subsectionname, MAX_LENKEYMAPSECTIONNAME+1, subsection->Value());
      AnsiLower(subsectionname);

      if (strcmp(subsectionname, "keyboard") != 0)
      { sprintf_s(m_LastError, LEN_LASTERROR+1, "Uexpected node <%s> in the section <%s>. The first node in the section must be <keyboard>.", subsectionname, sectionname);
        return FALSE;
      }
      
      break;
    }
  }

  if (subsection == 0)
  { sprintf_s(m_LastError, LEN_LASTERROR+1, "Cannot find a <keyboard> node in the section <%s>", sectionname);
    return FALSE;
  }

// At this point subsection is the <keyboard> section so we want the
// keydefs from it

  for (keydef = subsection->FirstChild(); keydef != 0; keydef = keydef->NextSibling())
  { element_type = keydef->Type();

    if (element_type == TiXmlNode::TINYXML_COMMENT)
    { comment.SetComment(keydef->Value());
      KeymapControl->InsertComment(comment);
    }

    else if (element_type == TiXmlNode::TINYXML_ELEMENT)
    { if (!ReadKeymapKeyDef(keydef, KeymapControl))
        return FALSE;
    }
  }

// Return indicating success

  return true;
}


//**********************************************************************
// CKeymapFile::ReadKeymapKeyDef
// --------------------------------
// Read a keymap key definition
//**********************************************************************

BOOL CKeymapFile::ReadKeymapKeyDef(TiXmlNode* KeyDef, CKeymapControl* KeymapControl)
{ int keyid, element_type;
  TiXmlElement* element;
  TiXmlAttribute* attr;
  TiXmlNode* action;
  CKeymapKeyDef keydef;
  char keyname[MAX_LENKEYMAPKEYNAME+1],
       attrname[64], keymod[64];

// Save the key name

  strcpy_s(keyname, MAX_LENKEYMAPKEYNAME+1, KeyDef->Value());
  AnsiLower(keyname);
  
  if (!keydef.SetKeyName(keyname))
  { sprintf_s(m_LastError, LEN_LASTERROR+1, "Unknown key name \"%s\".", keyname);
    return FALSE;
  }

// Go though all the attributes

  strcpy_s(keymod, 64, "");
  keyid = -1;
  element = KeyDef->ToElement();

	for (attr = element->FirstAttribute(); attr; attr = attr->Next())
	{ strcpy_s(attrname, 64, attr->Name());
	  AnsiLower(attrname);

	  // mod="ctrl,shift,alt,win"
	  if (strcmp(attrname, "mod") == 0)
	  { strcpy_s(keymod, 64, attr->Value());
	    keydef.SetModifiers(keymod);
	  }

	  // id="nnn" - only legal if the key name is <key ...>
	  if (strcmp(attrname, "id") == 0)
	  { if (strcmp(keyname, "key") != 0)
	    { sprintf_s(m_LastError, LEN_LASTERROR+1, "Illegal id attribute found in key \"%s\". The id attribute is only allowed if the key name is \"key\".", keyname);
        return FALSE;
	    }

	    if (attr->QueryIntValue(&keyid) != TIXML_SUCCESS)
	    { sprintf_s(m_LastError, LEN_LASTERROR+1, "The id attribute \"%s\"is not a valid integer.", attr->Value());
	      return FALSE;
	    }
	    
	    keydef.SetID(keyid);
	  }
	}

  if (strcmp(keyname, "key") == 0)
	{ if (keyid == -1)
    { sprintf_s(m_LastError, LEN_LASTERROR+1, "Missing id attribute.");
        return FALSE;
    }
  }

// The key action appears as a child node of type TINYXML_TEXT
// There might be no action e.g. <browser_refresh/>

  action = KeyDef->FirstChild();
  if (!action)
  { keydef.SetAction("");
  }
  else
  { element_type = action->Type();
    if (element_type != TiXmlNode::TINYXML_TEXT)
    { strcpy_s(m_LastError, "Unexpected error: ");
      return FALSE;
    }

    keydef.SetAction(action->Value());
  }

// Add the key definition

  KeymapControl->AppendKeyDef(keydef);

// Return indicating success

  return true;
}


//**********************************************************************
// CKeymapFile::GetLastError
// ----------------------------
// Retrieve the last error from the control
//**********************************************************************

const char* CKeymapFile::GetLastError(void)
{
  return m_LastError;
}


