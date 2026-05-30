/*---------------------------------------------------------------------------*
 | 
 | File           : $Id: $
 | Written by     :                        Date: 
 | Reviewed by    :                        Date: rcl
 | Description    : Source file for AppManager
 |                : 
 |                :
 *---------------------------------------------------------------------------*/

/* For g++ compilation */
#ifdef __GNUG__
#pragma  implementation "appmanager.h"
#endif

/* For compilers that support precompilation, includes "wx.h". */
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
#include "bitmaps/app_icon_large.xpm"
#endif /* USE_XPM_BITMAPS */

/* Other includes goes here */
#include "appmanager.h"
#include "main.h"
#include "functions.h"

/* This line enables the function wxGetApp(), which return a handle to the 
   one and only instance of class Main */
DECLARE_APP(Main); 


/*****************************************************************************/
/* Event Handler Table                                                       */
/*****************************************************************************/
BEGIN_EVENT_TABLE(SplitWindow, wxSplitterWindow)

EVT_SIZE(SplitWindow::OnSize)

END_EVENT_TABLE()


/*****************************************************************************/
/* Constructor / destructor                                                  */
/*****************************************************************************/
SplitWindow::SplitWindow(wxFrame *parent, long id)
 : wxSplitterWindow(parent, 
                    id, 
                    wxDefaultPosition, wxDefaultSize, 
                    wxSP_3DSASH | wxSP_FULLSASH)
{

}

/*****************************************************************************/
/* Event methods                                                             */
/*****************************************************************************/
void SplitWindow::OnSize(wxSizeEvent& event)
{
  
}


/*---------------------------------------------------------------------------*/
/* Constructor/destructor                                                    */
/*---------------------------------------------------------------------------*/

AppManager::AppManager(wxWindow *parent) : wxObject()
{
  m_mainframe         = NULL;
  m_left_drive_panel  = NULL;
  m_right_drive_panel = NULL;  
  m_split_window      = NULL;
  m_left_view         = NULL;
  m_right_view         = NULL;
  m_active_view       = NULL;  
  m_lowerpanel        = NULL;


  /* Initialize it */
  Initialize();
}

AppManager::~AppManager()
{ 
  /* Save the settings */
  ::settings_save(m_settings_table, SETTINGS_USER);

  csDESTROY(m_mainframe);
  csDESTROY(m_left_drive_panel);
  csDESTROY(m_right_drive_panel);  
  csDESTROY(m_split_window);
  csDESTROY(m_left_view);
  csDESTROY(m_right_view);
  csDESTROY(m_active_view);  
  csDESTROY(m_lowerpanel);
}


/*****************************************************************************/
/* Public methods                                                            */
/*****************************************************************************/

void AppManager::SetDirname(wxString dirname)
{
  ASSERT(m_active_view);
  ASSERT(m_lowerpanel);

  m_active_view->SetDirname(dirname);
  m_lowerpanel->SetDirname(dirname);
}

void AppManager::ShowMainFrame()
{ 
  ASSERT(m_left_view);
  ASSERT(m_right_view);  
  ASSERT(m_lowerpanel);  
  ASSERT(m_mainframe);  

  m_left_view->LoadDirectory(::wxGetCwd());
  m_right_view->LoadDirectory(::wxGetCwd());
  m_left_view->SetDirname(::wxGetCwd()); 
  m_right_view->SetDirname(::wxGetCwd());     
  m_lowerpanel->SetDirname(::wxGetCwd());
  m_mainframe->Center();
  m_mainframe->Show();
}



void AppManager::About()
{
  ASSERT(m_mainframe);
  ASSERT(m_settings_table);
  csAboutDlg dlg(m_mainframe, csLARGE_ICON(APP_ICON_LARGE), APP_NAME, 
                 m_settings_table); 
}




void AppManager::SizeChanged(wxSize size)
{
  ASSERT(m_split_window);
  m_split_window->SetSashPosition(size.GetWidth()/2);
}


void AppManager::LoadDirectory(wxString dir_path)
{
  ASSERT(m_active_view);
  m_active_view->LoadDirectory(dir_path);
}

void AppManager::SetActiveFileView(FileView* file_view)
{
  if(file_view == m_active_view)
    return;

  m_active_view->SetFocus(FALSE);
  m_active_view = file_view;  
  m_active_view->SetFocus(TRUE);
}


void AppManager::KeyTab()
{
  if(m_active_view == m_left_view) {
    m_active_view = m_right_view;
    m_right_view->SetFocus(TRUE);
    m_left_view->SetFocus(FALSE);    
    m_lowerpanel->SetDirname(m_active_view->GetFileList()->GetDirectoryPath());
    return;
 }  

  if(m_active_view == m_right_view){
    m_active_view = m_left_view;
    m_right_view->SetFocus(FALSE);
    m_left_view->SetFocus(TRUE);    
    m_lowerpanel->SetDirname(m_active_view->GetFileList()->GetDirectoryPath());
    return;
  }
}

void AppManager::KeySpace()
{
  
}

void AppManager::KeyEnter()
{
    
}

void AppManager::KeyRight()
{
  ASSERT(m_lowerpanel);  
  wxWindow *wnd = NULL;

  /* Locate the window */
  if(!(wnd = m_lowerpanel->FindWindow(ID_COMMANDS)))
    THROW_CRITICAL((_("Window with id: '%d' could not be found"), 
                    ID_COMMANDS));

  /* Give the command combo box the focus */
  wnd->SetFocus();
}



void AppManager::KeyLeft()
{
  ASSERT(m_lowerpanel);  
  wxWindow *wnd = NULL;

  /* Locate the window */
  if(!(wnd = m_lowerpanel->FindWindow(ID_COMMANDS)))
    THROW_CRITICAL((_("Window with id: '%d' could not be found"), 
                    ID_COMMANDS));

  /* Give the command combo box the focus */
  wnd->SetFocus();  
}


void AppManager::KeyUp()
{
  wxWindow *wnd = NULL;

  /* Locate the window */
  if(!(wnd = m_active_view->FindWindow(ID_FILE_LIST)))
    THROW_CRITICAL((_("Window with id: '%d' could not be found"), 
                    ID_FILE_LIST));

  /* Give the command combo box the focus */
  ((wxListCtrl*)wnd)->SetFocus();  
}

void AppManager::KeyDown()
{
  wxWindow *wnd = NULL;

  /* Locate the window */
  if(!(wnd = m_active_view->FindWindow(ID_FILE_LIST)))
    THROW_CRITICAL((_("Window with id: '%d' could not be found"), 
                    ID_FILE_LIST));

  /* Give the command combo box the focus */
  ((wxListCtrl*)wnd)->SetFocus();    
}


void AppManager::KeyEsc()
{
  ASSERT(m_lowerpanel);  
  ASSERT(m_active_view);  

  wxWindow *wnd = NULL;

  /* Locate the window */
  if(!(wnd = m_lowerpanel->FindWindow(ID_COMMANDS)))
    THROW_CRITICAL((_("Window with id: '%d' could not be found"), 
                    ID_COMMANDS));

  /* Give the command combo box the focus */
  ((wxComboBox*)wnd)->SetValue("");

  m_active_view->SetFocus(TRUE);
}


void AppManager::View()
{

}

void AppManager::Edit()
{

}

void AppManager::Copy()
{

}

void AppManager::Move()
{

}

void AppManager::MkDir()
{
  ASSERT(m_active_view);
  wxString dir_path = m_active_view->GetFileList()->GetDirectoryPath();   
  
  if(::wxMkdir(FileCat(dir_path, "test"))) 
    m_active_view->GetFileList()->ReloadDirectory();
}


void AppManager::Delete()
{
  ASSERT(m_active_view);
  m_active_view->GetFileList()->Delete(); 
}


void AppManager::Exit()
{
  ASSERT(m_mainframe);
  m_mainframe->Close(TRUE);  
}


/*****************************************************************************/
/* Private methods                                                           */
/*****************************************************************************/

void AppManager::Initialize()
{ 

  wxLayoutConstraints *c = NULL;

  /* Load the application settings table */
  m_settings_table = ::settings_load(); 
  
  /* Create the mainframe */
  m_mainframe = new MainFrame(APP_NAME, wxDefaultPosition, 
                              wxSize(900, 600));  


  m_left_drive_panel = new DriveButtonPanel(m_mainframe, ID_LEFT_DRIVE_PANEL);
  m_right_drive_panel = new DriveButtonPanel(m_mainframe, 
                                             ID_RIGHT_DRIVE_PANEL);  

  /* Make the layout for the controls */
  c = new wxLayoutConstraints;  
  c->top.SameAs(m_mainframe, wxTop);
  c->left.SameAs(m_mainframe, wxLeft);
  c->height.Absolute(30);  
  c->right.PercentOf(m_mainframe, wxWidth, 50);
  m_left_drive_panel->SetConstraints(c); 

  c = new wxLayoutConstraints;  
  c->top.SameAs(m_mainframe, wxTop);
  c->left.SameAs(m_left_drive_panel, wxRight);
  c->right.SameAs(m_mainframe, wxRight);  
  c->height.Absolute(30);    
  m_right_drive_panel->SetConstraints(c); 

  m_lowerbuttonpanel = new LowerButtonPanel(m_mainframe, 
                                            ID_LOWER_BUTTON_PANEL);
  c = new wxLayoutConstraints;  
  c->left.SameAs(m_mainframe, wxLeft);
  c->right.SameAs(m_mainframe, wxRight);
  c->bottom.SameAs(m_mainframe, wxBottom);  
  c->height.Absolute(35);  
  m_lowerbuttonpanel->SetConstraints(c);

  m_lowerpanel = new LowerPanel(m_mainframe, ID_LOWER_PANEL);
  c = new wxLayoutConstraints;    
  c->left.SameAs(m_mainframe, wxLeft);
  c->right.SameAs(m_mainframe, wxRight);
  c->bottom.SameAs(m_lowerbuttonpanel, wxTop, -3);  
  c->height.Absolute(35);
  m_lowerpanel->SetConstraints(c);

  m_split_window = new wxSplitterWindow(m_mainframe, ID_SPLIT_WINDOW, 
                                        wxDefaultPosition, wxDefaultSize, 
                                        wxSP_3DSASH | wxSP_FULLSASH);

  c = new wxLayoutConstraints;
  c->top.SameAs(m_right_drive_panel, wxBottom);
  c->left.SameAs(m_mainframe, wxLeft);
  c->right.SameAs(m_mainframe, wxRight);
  c->bottom.SameAs(m_lowerpanel, wxTop);
  m_split_window->SetConstraints(c); 

  m_left_view  = new FileView(m_split_window, ID_LEFT_VIEW, TRUE);    
  m_right_view = new FileView(m_split_window, ID_RIGHT_VIEW, FALSE);

  m_split_window->SplitVertically(m_left_view, m_right_view,
                                  m_mainframe->GetSize().GetWidth()/2);
  m_active_view = m_left_view;
  m_active_view->SetFocus(TRUE);
  m_right_view->SetFocus(FALSE);

  m_mainframe->Layout();

}
