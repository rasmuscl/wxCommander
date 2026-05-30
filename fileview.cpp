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

/* for g++ compilation */
#ifdef __GNUG__
#pragma  implementation "fileview.h"
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

#include <wx/log.h>
#include <wx/config.h>
#include <wx/image.h>
#include "fileview.h"
#include "filelist.h"
#include "main.h"

/* This line enables the function wxGetApp(), which return a handle to the 
   one and only instance of class Main */
DECLARE_APP(Main); 



BEGIN_EVENT_TABLE(FileView, wxPanel)

EVT_FILELIST_DIR_CHANGED(ID_FILE_LIST, FileView::OnDirChanged)

END_EVENT_TABLE()

/*---------------------------------------------------------------------------*/
/* Constructor/destructor                                                    */
/*---------------------------------------------------------------------------*/
FileView::FileView(wxWindow *parent, long id, BOOL left)
 : wxPanel(parent, id, wxDefaultPosition, wxDefaultSize)
{
  m_filelist = NULL;     
  m_mountpoints = NULL;
  m_dirname = NULL;
  m_mountstatus = NULL;
  m_mountname = NULL;
  m_currentdirectory = "";
  m_left = left;

  Initialize();
}


FileView::~FileView()
{
  csDESTROY(m_filelist);
  csDESTROY(m_mountpoints);
  csDESTROY(m_mountname);
  csDESTROY(m_mountstatus);
  csDESTROY(m_dirname);
}


/*****************************************************************************/
/* Public methods                                                            */
/*****************************************************************************/

void FileView::SetFocus(BOOL focus)
{
  ASSERT(m_dirname);
  ASSERT(m_filelist);
  
  if(focus) {
    m_dirname_bar->SetBackgroundColour(cDARK_BLUE);      
    m_dirname->SetBackgroundColour(cDARK_BLUE);
    m_dirname->SetForegroundColour(*wxWHITE);
    m_filelist->SetFocus();
  }  
  else {
    m_dirname->SetBackgroundColour(cDARK_GRAY);
    m_dirname_bar->SetBackgroundColour(cDARK_GRAY);
    m_dirname->SetForegroundColour(*wxLIGHT_GREY);
  }
  
  m_dirname->Refresh();
  m_dirname_bar->Refresh();
}


void FileView::LoadDirectory(wxString dir_path)
{
  ASSERT(m_filelist);
 m_filelist->LoadDirectory(dir_path);
  SetDirname(dir_path);
}


void FileView::SetDirname(wxString dirname)
{
  ASSERT(m_dirname);  
  m_dirname->SetLabel(dirname);
}


FileList* FileView::GetFileList()
{
  ASSERT(m_filelist);
  return m_filelist;
}

/*****************************************************************************/
/* Private methods                                                           */
/*****************************************************************************/

void FileView::Initialize()
{
  CreateWidgets();

  m_mountpoints->SetFont(cCOMMANDER_FONT);
  m_mountpoints->Append("[-floppy-]");
  m_mountpoints->Append("[-/-]");
  m_mountpoints->Append("[-data-]");
  m_mountpoints->Append("[-documents-]");
  m_mountpoints->SetSelection(1);
  m_filesselected->SetLabel(_("0 of 14,3 k in 0 of 100 files selected"));
  m_mountname->SetFont(cCOMMANDER_FONT);
  m_mountstatus->SetFont(cCOMMANDER_FONT);  
  m_dirname->SetFont(cCOMMANDER_FONT);
  m_filesselected->SetFont(cCOMMANDER_FONT);
}
 

void FileView::CreateWidgets()
{
  SetAutoLayout(TRUE);
  wxLayoutConstraints *c;

  m_mountpoints = new wxComboBox(this, ID_MOUNTPOINTS);
  m_mountname = new wxStaticText(this, -1, "[documents]");
  m_mountstatus = new wxStaticText(this, -1, "500,000 of 700,000 k");  
  m_dirname_bar = new wxPanel(this, -1);
  m_dirname = new wxStaticText(m_dirname_bar, -1, "c:\\*.*");    
  m_filelist = new FileList(this, ID_FILE_LIST);
  m_filesselected = new wxStaticText(this, -1, "");

  c = new wxLayoutConstraints;
  c->top.SameAs(this, wxTop, 2);
  c->left.SameAs(this, wxLeft);
  c->height.AsIs();
  c->width.Absolute(100);  
  m_mountpoints->SetConstraints(c);
  
  c = new wxLayoutConstraints;
  c->centreY.SameAs(m_mountpoints, wxCentreY);
  c->left.SameAs(m_mountpoints, wxRight, 5);
  c->height.AsIs();  
  c->width.Absolute(100);    
  m_mountname->SetConstraints(c);
  
  c = new wxLayoutConstraints;
  c->centreY.SameAs(m_mountpoints, wxCentreY);
  c->left.SameAs(m_mountname, wxRight, 5);
  c->height.AsIs();  
  c->right.SameAs(this, wxRight, 18);
  m_mountstatus->SetConstraints(c);
  
  c = new wxLayoutConstraints;
  c->top.SameAs(m_mountpoints, wxBottom);
  c->left.SameAs(this, wxLeft);
  c->right.SameAs(this, wxRight);  
  c->height.Absolute(16); 
  m_dirname_bar->SetConstraints(c);

  c = new wxLayoutConstraints;
  c->top.SameAs(m_dirname_bar, wxTop);
  c->left.SameAs(m_dirname_bar, wxLeft);
  c->right.SameAs(m_dirname_bar, wxRight);  
  c->bottom.SameAs(m_dirname_bar, wxBottom);    
  m_dirname->SetConstraints(c);
  
  c = new wxLayoutConstraints;
  c->top.SameAs(m_dirname_bar, wxBottom, -3);  

  if(m_left)
    c->left.SameAs(this, wxLeft);
  else
    c->left.SameAs(this, wxLeft, -3);
  
  c->right.SameAs(this, wxRight, -2);  
  c->bottom.SameAs(this, wxBottom, 15);
  m_filelist->SetConstraints(c);
  
  c = new wxLayoutConstraints;  
  c->top.SameAs(m_filelist, wxBottom);
  c->left.SameAs(this, wxLeft, 2);
  c->right.SameAs(this, wxRight);  
  c->bottom.SameAs(this, wxBottom);  
  m_filesselected->SetConstraints(c);

  Layout();
}


/*****************************************************************************/
/* Event handlers                                                            */
/*****************************************************************************/

void FileView::OnDirChanged(FileListEvent& event)
{  
  SetDirname(event.GetDirectory());
  GetParent()->GetEventHandler()->ProcessEvent(event);
  event.Skip();
}
