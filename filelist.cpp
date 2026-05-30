/*---------------------------------------------------------------------------*
 | Copyright (C) 2001 Crüger Software
 | 
 | File           : filelist.cpp
 | Written by     : rcl                    Date: april 2001
 | Description    : Contains implementation for the list control where the
 |                : the files are displayed.   
 |                :
 *---------------------------------------------------------------------------*/

/* for g++ compilation */
#ifdef __GNUG__
#pragma  implementation "filelist.h"
#endif

/* For compilers that support precompilation, includes "wx/wx.h". */
#include <wx/wxprec.h>

#ifdef __BORLANDC__
#pragma hdrstop
#endif

/* Include your minimal set of headers here, or wx.h */
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

/* Include resources (used under Linux) */
#if USE_XPM_BITMAPS
#include "bitmaps/fv_folder_icon.xpm"
#include "bitmaps/fv_hidden_folder_icon.xpm"
#include "bitmaps/fv_archive_icon.xpm"
#include "bitmaps/fv_exe_icon.xpm"
#include "bitmaps/fv_hidden_file_icon.xpm"
#include "bitmaps/fv_unknown_icon.xpm"
#include "bitmaps/fv_up_icon.xpm"
#include "bitmaps/fv_link_file_icon.xpm"
#include "bitmaps/fv_link_folder_icon.xpm"

#endif /* USE_XPM_BITMAPS */

#include <wx/log.h>
#include <wx/config.h>
#include <wx/image.h>
#include <wx/dir.h>
#include "wx/colordlg.h"    
#include <wx/mimetype.h>
#include <wx/datetime.h>

#include "filelist.h"
#include "functions.h"


/*****************************************************************************/
/* Internal functions                                                        */
/*****************************************************************************/

/* Function for sorting by name */
/*
CREATED    {* 2001-04-15 rcl *}
MODIFIED   {* *}
REVIEWED   {* *}
TESTED     {* *}
*/
static int wxCALLBACK SortByName(long item1, long item2, long asc)
{
  FileStruct *fs1, *fs2;
  
  fs1 = (FileStruct*)item1;
  fs2 = (FileStruct*)item2;

  /* We always want the "[..]" to be on the top */
  if(fs1->m_name == "[..]")
    return -1;

  if(fs2->m_name == "[..]")
    return 1;

  /* If both files are dirs, compare them */
  if(IS_DIR(fs1->m_kind) && IS_DIR(fs2->m_kind)) {
    if(asc)
      return fs1->m_name.CompareTo(fs2->m_name);
    else
      return fs2->m_name.CompareTo(fs1->m_name);
  }

  /* If item1 is dir and item2 is not, item1 is smallest */
  if(IS_DIR(fs1->m_kind) && !IS_DIR(fs2->m_kind))
    return -1;

  /* If item2 is dir and item1 is not, item1 is largest */
  if(!IS_DIR(fs1->m_kind) && IS_DIR(fs2->m_kind))
    return 1;

  /* Else it must be two files, and they are comparred normally */
  if(asc)
    return fs1->m_name.CompareTo(fs2->m_name);
  else
    return fs2->m_name.CompareTo(fs1->m_name);
}


/* Function for sorting by extension */
/*
CREATED    {* 2001-04-15 rcl *}
MODIFIED   {* *}
REVIEWED   {* *}
TESTED     {* *}
*/
static int wxCALLBACK SortByExt(long item1, long item2, long asc)
{
  FileStruct *fs1, *fs2;
  
  fs1 = (FileStruct*)item1;
  fs2 = (FileStruct*)item2;

  if(fs1->m_name == "[..]")
    return -1;

  if(IS_DIR(fs1->m_kind) && !IS_DIR(fs2->m_kind))
    return -1;

  if(!IS_DIR(fs1->m_kind) && IS_DIR(fs2->m_kind))
    return 1;

  if(asc)
    return fs1->m_ext.CompareTo(fs2->m_ext);
  else
    return fs2->m_ext.CompareTo(fs1->m_ext);

}


/* Function for sorting by size */
/*
CREATED    {* 2001-04-15 rcl *}
MODIFIED   {* *}
REVIEWED   {* *}
TESTED     {* *}
*/
static int wxCALLBACK SortBySize(long item1, long item2, long sortData)
{
#if 0
  FileStruct *fs1, *fs2;
  
  fs1 = (FileStruct*)item1;
  fs2 = (FileStruct*)item2;

  if(fs1->m_name == "[..]" || fs2->m_name == "[..]")
    return -1;
    
  if(fs1->m_is_dir && fs2->m_is_dir)
    return -1;
  
  if(fs1->m_is_dir && !fs2->m_is_dir) 
    return -1;  

  if(fs2->m_is_dir && !fs1->m_is_dir) 
    return -1;

  if(sortData) {
    if(fs1->m_size < fs2->m_size)
      return -1;
    
    else if(fs1->m_size > fs2->m_size)
      return 1;

    else
      return 0;
  }
  else {
    if(fs1->m_size > fs2->m_size)
      return -1;
    
    else if(fs1->m_size < fs2->m_size)
      return 1;

    else
      return 0;
  }  
#endif
  return 0;
}


/* Function for sorting by date */
/*
CREATED    {* 2001-04-15 rcl *}
MODIFIED   {* *}
REVIEWED   {* *}
TESTED     {* *}
*/
static int wxCALLBACK SortByDate(long item1, long item2, long sortData)
{
#if 0
  FileStruct *fs1, *fs2;
  wxDateTime date1, date2;
  
  fs1 = (FileStruct*)item1;
  fs2 = (FileStruct*)item2;

  date1 = wxDateTime(::wxFileModificationTime(fs1->m_full_path)); 
  date2 = wxDateTime(::wxFileModificationTime(fs2->m_full_path)); 

  if(fs1->m_name == "[..]" || fs2->m_name == "[..]")
    return -1;

  if(fs1->m_is_dir && fs2->m_is_dir) {
    if(sortData)
      return date1 <= date2 ;
    else
      return date1 >= date2 ;      
  }
    

  if(fs1->m_is_dir && !fs2->m_is_dir) 
    return -1;  

  if(fs2->m_is_dir && !fs1->m_is_dir) 
    return -1;

  /* two files */
  if(sortData)
    return date1 <= date2 ;
  else
    return date1 >= date2 ; 
#endif

  return 0;
}


#ifdef WIN32

/* Windows version of GetFileIcon */
/*
CREATED    {* 2001-04-18 rcl *}
MODIFIED   {* *}
REVIEWED   {* *}
TESTED     {* *}
*/
static wxBitmap GetFileIcon(wxString file)
{
  wxIcon icon;
  wxString str;
  wxString icon_key;
  wxString file_type;
  wxString path_index;
  BOOL knownExtension = FALSE;
  wxString index;

  HICON icons_large[1];
  HICON icons_small[1];

  
  if(IsHidden(filename))
    return csSMALL_ICON(FV_HIDDEN_ICON);

  if(IsArchive(filename))
    return csSMALL_ICON(FV_ARCHIVE_ICON);
  
  if(ext == "ico") {
    /* Get the icons */
    ExtractIconEx(filename, 0, icons_large, icons_small, 1);
    icon.SetHICON((WXHICON)icons_small[0]);
    return icon;
  }

  if(ext == "exe") {
    /* Get the icons */
    UINT i = ExtractIconEx(filename, 0, icons_large, icons_small, 1);
    if(i) {
      icon.SetHICON((WXHICON)icons_small[0]);
      return icon;
    }
    return csSMALL_ICON(FV_EXE_ICON);
  }

  /* Add a leading dot */
  str = "." +  ext;
    
  wxRegKey key_ext(wxRegKey::HKCR, str);  
  if (key_ext.Open() ) {
    /* it's the default value of the key */
    if (!key_ext.QueryValue(wxT(""), file_type)) {
      key_ext.Close();
      return csSMALL_ICON(FV_UNKNOWN_ICON);      
    }
  }
  key_ext.Close();  
  
  icon_key << file_type << wxT("\\DefaultIcon");

  wxRegKey key(wxRegKey::HKCR, icon_key);

  if ( key.Open() ) {
   
    // it's the default value of the key
    if ( key.QueryValue(wxT(""), path_index) ) {
        
      // the format is the following: <full path to file>, <icon index>
      // NB: icon index may be negative as well as positive and the full
      //     path may contain the environment variables inside '%'
      path = path_index.BeforeLast(wxT(',')),
      index = path_index.AfterLast(wxT(','));

      // index may be omitted, in which case BeforeLast(',') is empty and
      // AfterLast(',') is the whole string
      if (path.IsEmpty() ) {
          path = index;
          index = wxT("0");
      }

      wxString strExpPath = wxExpandEnvVars(path);
      int nIndex = wxAtoi(index);        

      /* Get the icons */
      ExtractIconEx(strExpPath, nIndex, icons_large, icons_small, 1);

      switch ((int)icons_small[0]) {
      case 0: // means no icons were found
      case 1: // means no such file or it wasn't a DLL/EXE/OCX/ICO/...
        wxLogDebug(wxT("incorrect registry entry '%s': no such icon."),
                   key.GetName().c_str());
        break;

       default:
        icon.SetHICON((WXHICON)icons_small[0]);        
        return icon;
      }
    }
  }
  return csSMALL_ICON(FV_UNKNOWN_ICON);

}

#else

/* Linux version of GetFileIcon */
/*
CREATED    {* 2001-04-18 rcl *}
MODIFIED   {* *}
REVIEWED   {* *}
TESTED     {* *}
*/
static wxBitmap GetFileIcon(wxString file)
{
  wxIcon icon;
  wxString name, ext, path;
  
  /* Split the path */
  wxSplitPath(file, &path, &name, &ext);

  /* First check if it is a link */
  if(IsLink(file)) {        
    if(IsLinkDir(file))
      return csSMALL_ICON(FV_LINK_FOLDER_ICON);    
    else
      return csSMALL_ICON(FV_LINK_FILE_ICON);
  }
  
  /* Check if it is an executable */
  if(IsExecutable(file))
    return csSMALL_ICON(FV_EXE_ICON);
  
  return csSMALL_ICON(FV_UNKNOWN_ICON);  
}

#endif


/*****************************************************************************/
/*                > Implementation of class FileList <                       */
/*****************************************************************************/

/*---------------------------------------------------------------------------*/
/* Event Handler Table                                                       */
/*---------------------------------------------------------------------------*/
BEGIN_EVENT_TABLE(FileList, wxListCtrl)

EVT_LIST_ITEM_SELECTED(      ID_FILE_LIST, FileList::OnSelected)
EVT_LIST_ITEM_DESELECTED(    ID_FILE_LIST, FileList::OnDeselected)
EVT_LIST_KEY_DOWN(           ID_FILE_LIST, FileList::OnListKeyDown)
EVT_LIST_ITEM_ACTIVATED(     ID_FILE_LIST, FileList::OnActivated) 
EVT_LIST_COL_CLICK(          ID_FILE_LIST, FileList::OnListColClick)

EVT_RIGHT_DOWN(                            FileList::OnRightDown)

END_EVENT_TABLE()


/*---------------------------------------------------------------------------*/
/* Constructor/destructor                                                    */
/*---------------------------------------------------------------------------*/

/* Constructor for FileList */
/*
CREATED    {* 2001-04-15 rcl *}
MODIFIED   {* *}
REVIEWED   {* *}
TESTED     {* *}
*/
FileList::FileList(wxWindow *parent, long id)
   : wxListCtrl(parent, id, wxDefaultPosition, wxDefaultSize, 
          wxLC_REPORT | wxLC_EDIT_LABELS | wxSUNKEN_BORDER),
     m_imagelist(16, 16, TRUE)
{
  m_file_cnt = 0;
  m_directory_path = "";

  Initialize();
}


/* Destructor for FileList */
/*
CREATED    {* 2001-04-15 rcl *}
MODIFIED   {* *}
REVIEWED   {* *}
TESTED     {* *}
*/
FileList::~FileList()
{
  m_imagelist.RemoveAll();    
}


/*****************************************************************************/
/* Public methods                                                            */
/*****************************************************************************/

/* Loads a given directory */
/*
CREATED    {* 2001-04-15 rcl *}
MODIFIED   {* 2001-04-18 rcl *}
REVIEWED   {* *}
TESTED     {* *}
*/
void FileList::LoadDirectory(wxString dir_path)
{
  long index = -1;
  wxDir dir;
  wxString filename, ext, path, name, full_path;
  BOOL cont;
  long dirs;
  long files;
  wxLogNull nolog;
  
  /* Check if it is a directory */
  if(!::wxDirExists(dir_path))
    THROW_CRITICAL((_("'%s' is not a directory"), csWX2CHAR(dir_path)));    


  /* Open the directory */
  dir.Open(dir_path);
  if (!dir.IsOpened()) {
    wxMessageBox(_("Permission denied"), _("Permission denied"), wxICON_STOP);
    return;
  }
  
  /* Reset the lists of images */
  m_imagelist.RemoveAll();
  
  /* Delete all the items */ 
  DeleteAllItems();

  /* Get a list of files from the given path */  
  m_file_cnt = 0;

  /* First get the directories */
  dirs = wxDIR_DOTDOT | wxDIR_HIDDEN | wxDIR_DIRS | wxDIR_FILES;
  for(cont = dir.GetFirst(&filename, wxEmptyString, dirs); cont; 
      cont = dir.GetNext(&filename)){    
    
    if((filename == "..") || (filename == "." && dir_path == "/"))
      continue;
    
    /* Get the full path to the file/dir */
    full_path = FileCat(dir_path, filename); 
    
    /* Gather the file information */
    GetFileInfo(dir_path, filename, &m_files[m_file_cnt]);
    
    /* Insert the item in the list */
    m_imagelist.Add(m_files[m_file_cnt].m_icon);  
    index = InsertItem(m_file_cnt, m_files[m_file_cnt].m_name);  
    SetItem(m_file_cnt, EXT_COLOM,  m_files[m_file_cnt].m_ext);
    SetItem(m_file_cnt, SIZE_COLOM, m_files[m_file_cnt].m_fsize);
    SetItem(m_file_cnt, DATE_COLOM, m_files[m_file_cnt].m_datetime);
    SetItem(m_file_cnt, ATT_COLOM,  m_files[m_file_cnt].m_att);    
    SetItemImage(m_file_cnt, m_file_cnt, -1);
    SetItemData(index, (long)&m_files[m_file_cnt]);
    m_files[m_file_cnt].m_index = index;
    
    m_file_cnt++;
  }  

  m_directory_path = dir_path;

  SortItems(m_sort_functions[m_sort_by], m_sort_asc[m_sort_by]);
  UpdateIndices();

  for(int i = 0; i < NO_COLOMS; i++)  
    SetColumnWidth(i, wxLIST_AUTOSIZE);

  FileListEvent fle(EVT_DIR_CHANGED, GetId());
  fle.SetEventObject(this);
  fle.SetDirectory(dir_path);
  
  GetEventHandler()->ProcessEvent(fle);  
}


/* Reloads the currently loaded directory */
/*
CREATED    {* 2001-04-15 rcl *}
MODIFIED   {* *}
REVIEWED   {* *}
TESTED     {* *}
*/
void FileList::ReloadDirectory()
{
  LoadDirectory(m_directory_path);
}


/* View the currently (if any) selected file */
/*
CREATED    {* 2001-04-15 rcl *}
MODIFIED   {* 2001-04-18 rcl *}
REVIEWED   {* *}
TESTED     {* *}
*/
void FileList::View(wxString file)
{
  ::wxExecute(csGui::Format("emacs %s", csWX2CHAR(file)));
}


/* Edit the currently (if any) selected file */
/*
CREATED    {* 2001-04-15 rcl *}
MODIFIED   {* *}
REVIEWED   {* *}
TESTED     {* *}
*/
void FileList::Edit(wxString file)
{
  ::wxExecute(csGui::Format("emacs %s", csWX2CHAR(file)));
}


/* Copy the currently (if any) selected file to a specified location */
/*
CREATED    {* 2001-04-15 rcl *}
MODIFIED   {* *}
REVIEWED   {* *}
TESTED     {* *}
*/
void FileList::Copy(wxString file)
{
  /* Get the dst file */
}


/* Rename/move the currently (if any) selected file */
/*
CREATED    {* 2001-04-15 rcl *}
MODIFIED   {* *}
REVIEWED   {* *}
TESTED     {* *}
*/
void FileList::RenMov(wxString file)
{
  /* Get the dst file */  
}


/* Create a new directory under the currently loaded directory */
/*
CREATED    {* 2001-04-15 rcl *}
MODIFIED   {* *}
REVIEWED   {* *}
TESTED     {* *}
*/
void FileList::MkDir()
{
  
}


/* Delete the currently (if any) selected file */
/*
CREATED    {* 2001-04-15 rcl *}
MODIFIED   {* *}
REVIEWED   {* *}
TESTED     {* *}
*/
void FileList::Delete()
{
  wxNode     *node = NULL;
  FileStruct *fs   = NULL;

  /* Get selected files */
  wxList *files = GetSelectedFiles(); 

  /* Get selected dirs */
  wxList *dirs = GetSelectedDirs(); 

  /* If none is seletected - return */
  if(files->Number() + dirs->Number() == 0)
    return;
  
  if(wxMessageBox(_("Do you really want to delete the selected file(s)?"),
                  _("Confirm delete"), wxICON_QUESTION | wxYES_NO) != wxYES)
    return;
  
  /* Delete the selected files */
  for(node = files->GetFirst(); node; node = node->GetNext()) {
    /* Get the filestruct */
    fs = (FileStruct*)node->GetData();

    /* Delete the item from the list */
    DeleteItem(fs->m_index);    
    ::wxRemoveFile(fs->m_full_path);
    fs->m_is_used = FALSE;
  }
  
  /* Delete the selected directories */
  for(node = dirs->GetFirst(); node; node = node->GetNext()) {
    /* Get the filestruct */
    fs = (FileStruct*)node->GetData();
    
    /* Delete the item from the list */
    DeleteItem(fs->m_index);    
    ::wxRmdir(fs->m_full_path);
    fs->m_is_used = FALSE;
  }
  
  /* free the lists */  
  delete dirs;
  delete files;

  /* Get the indices updated */
  UpdateIndices();
  Refresh();
}


/*****************************************************************************/
/* Private methods                                                           */
/*****************************************************************************/

/* When a file is deleted or the list has been sorted, the indices are
   modified. This updates the list items data field index */
/*
CREATED    {* 2001-04-15 rcl *}
MODIFIED   {* *}
REVIEWED   {* *}
TESTED     {* *}
*/
void FileList::UpdateIndices()
{
  FileStruct *fs;
  
  /* Go through the list and update the indices */    
  for(int i = 0; i < GetItemCount(); i++) {
    fs = (FileStruct*)GetItemData(i);
    fs->m_index = i;    
  }
}


/* Builds a list of the currently selected files, used in Delete() */
/*
CREATED    {* 2001-04-15 rcl *}
MODIFIED   {* *}
REVIEWED   {* *}
TESTED     {* *}
*/
wxList* FileList::GetSelectedFiles()
{
  wxList *files = new wxList(wxKEY_NONE);
  for(int i = m_file_cnt-1; i >= 0; i--) {
    if(m_files[i].m_is_used && !IS_DIR(m_files[i].m_kind)
       && m_files[i].m_selected)
      files->Append((wxObject*)&m_files[i]);
  }
  return files;
}


/* Builds a list of the currently selected directories, used in Delete() */
/*
CREATED    {* 2001-04-15 rcl *}
MODIFIED   {* *}
REVIEWED   {* *}
TESTED     {* *}
*/
wxList* FileList::GetSelectedDirs()
{
  wxList *dirs = new wxList(wxKEY_NONE);
  for(int i = 0; i < m_file_cnt; i++) {
    if(m_files[i].m_is_used && IS_DIR(m_files[i].m_kind)
       && m_files[i].m_selected)
      dirs->Append((wxObject*)&m_files[i]);
  }
  return dirs;
}


/* Initializes the control: Columns, etc. */
/*
CREATED    {* 2001-04-15 rcl *}
MODIFIED   {* 2001-04-18 rcl *}
REVIEWED   {* *}
TESTED     {* *}
*/
void FileList::Initialize()
{
  /* Set colour and font */
  SetBackgroundColour(*wxWHITE);
  SetFont(cCOMMANDER_FONT);
 
  /* So far, let the coloms be: */
  InsertColumn(NAME_COLOM,_("Name")); 
  InsertColumn(EXT_COLOM, _("Ext"));
  InsertColumn(SIZE_COLOM,_("Size"));
  InsertColumn(DATE_COLOM,_("Date"));
  InsertColumn(ATT_COLOM, _("Att"));  

  /* Sort default ascending */
  m_sort_asc[NAME_COLOM] = TRUE;
  m_sort_asc[EXT_COLOM]  = TRUE;
  m_sort_asc[SIZE_COLOM] = TRUE;
  m_sort_asc[DATE_COLOM] = TRUE;

  /* Save pointers to the sorting functions */
  m_sort_functions[NAME_COLOM] = SortByName;
  m_sort_functions[EXT_COLOM]  = SortByExt;
  m_sort_functions[SIZE_COLOM] = SortBySize;
  m_sort_functions[DATE_COLOM] = SortByDate;

  /* Sort default by name */
  m_sort_by = NAME_COLOM;

  SetImageList(&m_imagelist, wxIMAGE_LIST_SMALL);
  
  /* By default load the current working directory */
  LoadDirectory(::wxGetCwd());
}


/* Scrolls down to a given file - does NOT work */
/*
CREATED    {* 2001-04-15 rcl *}
MODIFIED   {* *}
REVIEWED   {* *}
TESTED     {* *}
*/
void FileList::ScrollToFile(wxString file)
{
  FileStruct *fs;
  int i;
  
  /* Go through the list until file is found */    
  for(i = 0; i < GetItemCount(); i++) {
    fs = (FileStruct*)GetItemData(i);
   
    if(fs->m_full_path == file)
      break;
  }
  /* Scroll does not work */
}


/* Get the file info */
/*
CREATED    {* 2001-04-18 rcl *}
MODIFIED   {* *}
REVIEWED   {* *}
TESTED     {* *}
*/
void FileList::GetFileInfo(wxString dir_path, wxString file, FileStruct *fs)
{
  ASSERT(fs);  
  wxString name, ext, path, full_path;

  /* Get the full path to the file/dir */
  full_path = FileCat(dir_path, file); 

  /* Split the path */
  wxSplitPath(full_path, &path, &name, &ext);

  /* First set the common fields */
  fs->m_icon      = GetFileIcon(full_path);
  fs->m_full_path = full_path;  
  fs->m_datetime  = FormatDate(full_path);
  fs->m_att       = GetFileAttributes(full_path); 
  fs->m_selected  = FALSE;
  fs->m_is_used   = TRUE;

  /* Directory */
  if(IsDir(full_path)) {
    fs->m_name      = "[" + name + "]";  
    fs->m_ext       = "";
    fs->m_kind      = FT_DIR;
    fs->m_fsize     = "<DIR>";
    fs->m_size      = -1;
    
        
    /* Possible overwrite the name and icon */
    if(name == ".") {
      fs->m_icon = csSMALL_ICON(FV_UP_ICON); 
      fs->m_full_path = GetParentDir(dir_path);
      fs->m_name      = "[..]";
    }
  }

  /* Regular file */
  if(IsRegular(full_path)) {
    fs->m_name      = name;
    fs->m_ext       = ext;   
    fs->m_size      = GetFileSize(full_path);  
    fs->m_fsize     = FormatSize(fs->m_size);    
    fs->m_kind      = FT_FILE;
  }  
  
  /* Link */
  if(IsLink(full_path)) {
    fs->m_name      = name;
    fs->m_ext       = ext;
    fs->m_kind   |= FT_LNK;
    fs->m_size    = 11;
    fs->m_fsize   = "<LNK>";

    /* Is it a link to a directory */
    if(IsLinkDir(full_path))
      fs->m_kind   |= FT_DIR;      
  }

  /* Extra: Executable */
  if(IsExecutable(full_path) && (fs->m_kind & FT_FILE))
    fs->m_kind |= FT_EXECUTABLE;

  /* Extra: Archive */
   if(IsArchive(full_path))
    fs->m_kind |= FT_ARCHIVE;
}


/* Return a 16 x 16 icon that corresponds to the file */
/*
CREATED    {* 2001-04-15 rcl *}
MODIFIED   {* 2001-04-19 rcl *}
REVIEWED   {* *}
TESTED     {* *}
*/
wxBitmap FileList::GetFileIcon(wxString file)
{
  wxString name, ext, path;
    
  /* Split the path */
  wxSplitPath(file, &path, &name, &ext);
  
  /* Suppress all wxWindows errors */
  wxLogNull nolog;

  /* Is it a hidden file/directory */
  if(IsHidden(name)) {
    if(IsDir(file) || (IsLink(file) && IsLinkDir(file)))
      return csSMALL_ICON(FV_HIDDEN_FOLDER_ICON);
    else
      return csSMALL_ICON(FV_HIDDEN_FILE_ICON);
  }
  
  /* Is it a directory */
  if(IsDir(file))
    return csSMALL_ICON(FV_FOLDER_ICON);
  
  /* Is it an archive (tar, zip, tgz, ...)*/
  if(IsArchive(file))
    return csSMALL_ICON(FV_ARCHIVE_ICON);

  /* The rest is put in two differetn functions */
  return ::GetFileIcon(file);
}



/*****************************************************************************/
/* Event handlers                                                            */
/*****************************************************************************/

/* Called when user has pressed a key, i.e. enter, space, etc */
/*
CREATED    {* 2001-04-15 rcl *}
MODIFIED   {* *}
REVIEWED   {* *}
TESTED     {* *}
*/
void FileList::OnListKeyDown(wxListEvent& event)
{
  wxListItem list_item;
  long item = -1; 
  wxRect item_rect;
  FileStruct *fs;
  wxString old_file;
  int key;

  /* Get the selected item */
  if((item = event.GetIndex()) == -1)
    return;
  
  /* Get the data for the list item */
  fs = (FileStruct*)GetItemData(item);

  /* Make the list item ready by setting the id */
  list_item.SetId(item);
  
  /* Get the key code to switch on */
  key = event.GetCode();

  switch(key) {
    
  case WXK_SPACE:      
    
    if(fs->m_selected)
      list_item.SetTextColour(*wxBLACK);
    else
      list_item.SetTextColour(*wxRED);
    
    fs->m_selected = !fs->m_selected;
    SetItem(list_item);
    
    break;
    
  case WXK_RETURN:
    break;
    
  case WXK_BACK:
    LoadDirectory(GetParentDir(m_directory_path));
    break;

  case WXK_F3:
    View(fs->m_full_path);
    break;

  case WXK_F4:
    Edit(fs->m_full_path);
    break;

  case WXK_F5:
    Copy(fs->m_full_path);
    break;

  case WXK_F6:
    RenMov(fs->m_full_path);
    break;

  case WXK_F7:
    MkDir();
    break;

  case WXK_F8:
  case WXK_DELETE:
    /* Select the one the marker is over */
   
    if(!fs->m_selected) {
      list_item.SetTextColour(*wxRED);    
      fs->m_selected = TRUE;
      SetItem(list_item);
    }
    
    Delete();
    break;
    
  case (WXK_SHIFT & WXK_F6) :
    wxMessageBox("Shift+F6");
    break;
  default: 
    event.Skip(); 
    break;
  }
  
  event.Skip(); 
}


/* Called when user has selected an item. This function deselects that 
   selection, since we dont use the built in selection mechanism. */
/*
CREATED    {* 2001-04-15 rcl *}
MODIFIED   {* *}
REVIEWED   {* *}
TESTED     {* *}
*/
void FileList::OnSelected(wxListEvent& event)
{
  /* Set this fileview as the active */
  // APP_MNG()->SetActiveFileView((FileView*)GetParent());

  /* Unselect the choice - i.e. do not use the built in 
     selections. */
  SetItemState(event.GetIndex(), 0, wxLIST_STATE_SELECTED);  
  event.Skip();
}


/* Called when user has pressed a key, i.e. enter, space, etc */
/*
CREATED    {* 2001-04-15 rcl *}
MODIFIED   {* *}
REVIEWED   {* *}
TESTED     {* *}
*/
void FileList::OnActivated(wxListEvent& event)
{
  int item;
  FileStruct *fs;
  
  /* If the use has clicked outside a list item */
  if((item = event.GetIndex()) == -1)
    return;

  /* Get the data for the list item */
  fs = (FileStruct*)GetItemData(item);

  /* If the node is a directory just load it */
  if(IS_DIR(fs->m_kind))
    LoadDirectory(fs->m_full_path);

  event.Skip();

}


/* Called when an item has been deselected - not used so far */
/*
CREATED    {* 2001-04-15 rcl *}
MODIFIED   {* *}
REVIEWED   {* *}
TESTED     {* *}
*/
void FileList::OnDeselected(wxListEvent& event)
{
  int item = event.GetItem();
}



/* Called when user presses coloum header */
/*
CREATED    {* 2001-04-15 rcl *}
MODIFIED   {* *}
REVIEWED   {* *}
TESTED     {* *}
*/
void FileList::OnListColClick(wxListEvent& event)
{
  int col = event.GetColumn();

  if(col != NAME_COLOM && col != EXT_COLOM &&
     col != SIZE_COLOM && col != DATE_COLOM)
    return;

  m_sort_by = col;
  
  SortItems(m_sort_functions[m_sort_by], m_sort_asc[m_sort_by]);
  m_sort_asc[m_sort_by] = !m_sort_asc[m_sort_by];
  UpdateIndices();
}


void FileList::OnRightDown(wxMouseEvent& event)
{
  FileStruct *fs;    
  wxPoint pos = event.GetPosition();
  wxString info = "";

  
  int flag = wxLIST_HITTEST_ONITEM;
  
  /* Did we hit anything? */
  long item = HitTest(pos, flag);

  if(item == -1)
    return;

  long kind;

  SetItemState(item, wxLIST_STATE_SELECTED, wxLIST_STATE_SELECTED);  
  
  /* Get the data for the list item */
  fs = (FileStruct*)GetItemData(item);

  info += csGui::Format("index: %d\n", fs->m_index);
  info += csGui::Format("name: %s\n", csWX2CHAR(fs->m_name));
  info += csGui::Format("ext: %s\n", csWX2CHAR(fs->m_ext));
  info += csGui::Format("full path: %s\n", csWX2CHAR(fs->m_full_path));
  info += csGui::Format("size: %s\n", csWX2CHAR(fs->m_fsize));
  info += csGui::Format("index: %d\n", fs->m_index);
  info += csGui::Format("date: %s\n", csWX2CHAR(fs->m_datetime));
  info += csGui::Format("att: %s\n", csWX2CHAR(fs->m_att));
  info += csGui::Format("selected: %d\n", fs->m_selected);

  info += csGui::Format("kind: %d\n", fs->m_kind);
  info += csGui::Format("FT_FILE: %d\n", (fs->m_kind & FT_FILE));
  info += csGui::Format("FT_DIR: %d\n", (fs->m_kind & FT_DIR));
  info += csGui::Format("FT_LNK: %d\n", (fs->m_kind & FT_LNK));
  info += csGui::Format("FT_EXECUTABLE: %d\n", (fs->m_kind & FT_EXECUTABLE));
  info += csGui::Format("FT_ARCHIVE: %d\n", (fs->m_kind & FT_ARCHIVE));

  wxMessageBox(info);
  
}


/*****************************************************************************/
/*                > Implementation of class FileListEvent <                  */
/*****************************************************************************/

IMPLEMENT_DYNAMIC_CLASS(FileListEvent, wxNotifyEvent)

FileListEvent::FileListEvent( wxEventType commandType, int id ):
  wxNotifyEvent( commandType, id )
{
  m_dir = "";
}
