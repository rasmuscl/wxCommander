/*---------------------------------------------------------------------------*
 | Copyright (C) 2001 Crüger Software
 | 
 | File           : filelist.h
 | Written by     : rcl                    Date: april 2001
 | Description    : Contains class definition for the list control where the
 |                : the files are displayed.   
 |                :
 *---------------------------------------------------------------------------*/

#ifndef __FILELIST_H_
#define __FILELIST_H_

/* For g++ compilation */
#ifdef __GNUG__
#pragma interface "filelist.h"
#endif

#include <configit_base.h>
#include <configit_gui.h>
#include <wx/imaglist.h>
#include <wx/listctrl.h>
#include "global.h"


/*****************************************************************************/
/* Forward declaratuions                                                     */
/*****************************************************************************/

class FileListEvent;


/*****************************************************************************/
/* Defines                                                                   */
/*****************************************************************************/

#define IS_DIR(kind) (kind & FT_DIR)

#define EVT_DIR_CHANGED wxEVT_USER_FIRST + 1
#define EVT_GOT_FOCUS   wxEVT_USER_FIRST + 2
#define EVT_COPY_FILE   wxEVT_USER_FIRST + 3
#define EVT_MOVE_FILE   wxEVT_USER_FIRST + 4

typedef void (wxEvtHandler::*FileListEventFunction)(FileListEvent&);

#define EVT_FILELIST_DIR_CHANGED(id, fn) { EVT_DIR_CHANGED, id, -1, (wxObjectEventFunction) (wxEventFunction) (FileListEventFunction) &fn, (wxObject*) NULL },

#define EVT_FILELIST_GOT_FOCUS(id, fn) { EVT_GOT_FOCUS, id, -1, wxObjectEventFunction) (wxEventFunction) (FileListEventFunction) & fn, wxObject *) NULL },

#define EVT_FILELIST_COPY_FILE(id, fn) { EVT_COPY_FILE, id, -1, wxObjectEventFunction) (wxEventFunction) (FileListEventFunction) & fn, wxObject *) NULL },

#define EVT_FILELIST_MOVE_FILE(id, fn) { EVT_MOVE_FILE, id, -1, wxObjectEventFunction) (wxEventFunction) (FileListEventFunction) & fn, wxObject *) NULL },


/* Enums for the columns in list */
enum 
{
  NAME_COLOM = 0,
  EXT_COLOM,
  SIZE_COLOM,
  DATE_COLOM,
  ATT_COLOM,
  NO_COLOMS
};

#define ID_FILE_LIST   7040
#define MAX_FILES      1000

/* Enum for the different filetypes */

#define FT_FILE       1
#define FT_DIR        2
#define FT_LNK        4
#define FT_EXECUTABLE 8
#define FT_ARCHIVE    16


/*****************************************************************************/
/* Class definition                                                          */
/*****************************************************************************/

/* FileListEvent class  */
/*
CREATED    {* 2001-04-20 rcl *}
MODIFIED   {* 2001-04-21 rcl *}
REVIEWED   {* *}
TESTED     {* *}
*/
class FileListEvent : public wxNotifyEvent
{
public:
    FileListEvent(wxEventType commandType = wxEVT_NULL, int id = 0);

    void            SetDirectory(wxString dir) {m_dir = dir;}
    wxString        GetDirectory(){return m_dir; }    

private:
    wxString        m_dir;
    DECLARE_DYNAMIC_CLASS(FileListEvent)
};


/*****************************************************************************/
/* Class definition                                                          */
/*****************************************************************************/

/* Files in fileview */
/*
CREATED    {* 2001-04-15 rcl  *}
MODIFIED   {* *}
REVIEWED   {* *}
TESTED     {* *}
*/
class FileStruct : public wxObject
{
public:
  /* Index in list control */
  long     m_index;

  /* Icon to show */
  wxBitmap m_icon;

  /* Filename without extension */
  wxString m_name;

  /* Full path to file or directory */
  wxString m_full_path;

  /* File extension for dirs: <DIR> for links <LNK> */
  wxString m_ext;

  /* String formatation of the size */
  wxString m_fsize;  

  /* Actual file size in bytes */
  long     m_size;  

  /* A date formatted as a string */
  wxString m_datetime;    

  /* Attributes formatted as a string */
  wxString m_att;

  /* Flag telling whether the entry in array is used - see class FileList */
  BOOL     m_is_used;

  /* Is the file or directory selected by the user */
  BOOL     m_selected;

  /* What kind of file is it? */
  long     m_kind;
};


/*****************************************************************************/
/* Class definition                                                          */
/*****************************************************************************/

/* Class for filelist control */
/*
CREATED    {* 2001-04-15 rcl *}
MODIFIED   {* 2001-04-18 rcl *}
REVIEWED   {* *}
TESTED     {* *}
*/
class FileList: public wxListCtrl
{
public:
  /* Constructor / destructor */
  FileList(wxWindow *parent, long id);
  ~FileList();

  /* Public methods */  
  void              LoadDirectory(wxString dir_path);  
  wxString          GetDirectoryPath(){return m_directory_path;}
  void              ReloadDirectory();

  /* Standard operations */
  void              View(wxString file);
  void              Edit(wxString file);
  void              Copy(wxString file);
  void              RenMov(wxString file);
  void              MkDir();
  void              Delete();
  
private:
  void              Initialize();
  wxList*           GetSelectedFiles();  
  wxList*           GetSelectedDirs();  
  void              UpdateIndices();
  void              ScrollToFile(wxString file);
  void              GetFileInfo(wxString dir, wxString file, FileStruct* fs);  
  wxBitmap          GetFileIcon(wxString filename);


  /* Event handlers: */
  void              OnListKeyDown(wxListEvent& event);
  void              OnSelected(wxListEvent& event);
  void              OnActivated(wxListEvent& event);
  void              OnDeselected(wxListEvent& event);
  void              OnListColClick(wxListEvent& event);
  void              OnRightDown(wxMouseEvent& event);
  
  /* List containing the images */
  wxImageList       m_imagelist;  

  /* Array of data pointed to by the file items */
  FileStruct        m_files[MAX_FILES];

  /* Number of files on list */
  long              m_file_cnt;

  /* Currently loaded directory */
  wxString          m_directory_path;

  /* Flags telling wheteher to sort a column asc. or desc. */
  BOOL              m_sort_asc[4];

  /* List of corresponding compare functions */
  wxListCtrlCompare m_sort_functions[4];

  /* Sort by name, ext, size, etc*/
  int               m_sort_by;

  int               m_width;
  
  DECLARE_EVENT_TABLE()
};


#endif  /* __FILELIST_H_ */

