/*---------------------------------------------------------------------------*
 | Copyright (C) 2000 Crüger Software
 |
 | 
 | 
 | 
 | 
 | File           : fileview.cpp
 | Written by     : rcl                    Date: august 2000
 | Reviewed by    :                        Date: 
 | Description    : 
 |                : 
 |                :
 *---------------------------------------------------------------------------*/

#ifndef __FILEVIEW_H_
#define __FILEVIEW_H_

/* For g++ compilation */
#ifdef __GNUG__
#pragma interface "fileview.h"
#endif

#include <configit_base.h>
#include <configit_gui.h>
#include "filelist.h"
#include "global.h"

/*****************************************************************************/
/* Defines                                                                   */
/*****************************************************************************/
#define BAR_HEIGHT   17
#define ID_MOUNTPOINTS 6000

/*****************************************************************************/
/* Class definition                                                          */
/*****************************************************************************/
class FileView: public wxPanel
{

public:
  // Constructor / destructor
  FileView(wxWindow *parent, long id, BOOL left);
  ~FileView();
  
  void              SetFocus(BOOL focus);
  void              LoadDirectory(wxString dir_path);
  void              SetDirname(wxString dirname);  
  FileList*         GetFileList();
  
private:
  /* Initialization methods */
  void              Initialize();
  void              CreateWidgets();

  /* Event handlers */
  void              OnDirChanged(FileListEvent& event);
  
  /* Attributes */
  FileList         *m_filelist;
  wxComboBox       *m_mountpoints;
  wxStaticText     *m_dirname;
  wxPanel          *m_dirname_bar;
  wxStaticText     *m_mountname;
  wxStaticText     *m_mountstatus;
  wxStaticText     *m_filesselected;
  wxString          m_currentdirectory;
  BOOL              m_left;


  DECLARE_EVENT_TABLE()

};


#endif  //__FILEVIEW_H_
