/*---------------------------------------------------------------------------*
 |  
 | File           : mainframe.h
 | Written by     : rcl 21/02/2001
 | Description    : Implementation file for class MainFrame
 |                :
 *---------------------------------------------------------------------------*/

/* For g++ compilation */
#ifdef __GNUG__
#pragma  implementation "mainframe.h"
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
#include "bitmaps/app_icon.xpm"
#include "bitmaps/app_icon_large.xpm"
#include "bitmaps/tb_back_icon.xpm"
#include "bitmaps/tb_ftp_connect_icon.xpm"
#include "bitmaps/tb_brief_icon.xpm"               
#include "bitmaps/tb_ftp_new_connection_icon.xpm"
#include "bitmaps/tb_cd_tree_icon.xpm"             
#include "bitmaps/tb_full_icon.xpm"
#include "bitmaps/tb_cdrom_icon.xpm"               
#include "bitmaps/tb_invert_icon.xpm"
#include "bitmaps/tb_drive_icon.xpm"               
#include "bitmaps/tb_network_icon.xpm"
#include "bitmaps/tb_floppy_icon.xpm"              
#include "bitmaps/tb_reread_icon.xpm"
#include "bitmaps/tb_forward_icon.xpm"             
#include "bitmaps/tb_tree_icon.xpm"

#endif /* USE_XPM_BITMAPS */


/* Other includes goes here */
#include "mainframe.h"
#include "main.h"
#include "filelist.h"

/* This line enables the function wxGetApp(), which return a handle to the 
   one and only instance of class Main */
DECLARE_APP(Main); 

#define ID_LEFT  10000
#define ID_RIGHT 10001


/*---------------------------------------------------------------------------*/
/* Event Handler Table                                                       */
/*---------------------------------------------------------------------------*/
BEGIN_EVENT_TABLE(MainFrame, wxFrame)

EVT_MENU(FILES_MENU_EXIT,                           MainFrame::OnExit)
EVT_MENU(HELP_MENU_ABOUT,                           MainFrame::OnAbout)	
EVT_MENU_RANGE(SC_TAB, NO_SHORTCUTS-1,              MainFrame::OnShortcut)

END_EVENT_TABLE()   
  
  
/*---------------------------------------------------------------------------*/
/* Constructor/destructor                                                    */
/*---------------------------------------------------------------------------*/
MainFrame::MainFrame(const wxString& title, 
		                 const wxPoint& pos, 
		                 const wxSize& size)
  : wxFrame((wxFrame *)NULL, MAINFRAME_ID, title, pos, size)
{
  m_toolbar     = NULL;
  m_menubar     = NULL;

  /* Initialize the mainframe */
  Initialize();
}

MainFrame::~MainFrame()
{ 
  /* m_toolbar & m_menubar are implicitly destroyed when mainframe object 
     is destroyed and need not be explicitly destroyed here. See wxWindows
     manual for details. */  
}


/*****************************************************************************/
/* Public functions                                                          */
/*****************************************************************************/


/*****************************************************************************/
/* Private functions                                                         */
/*****************************************************************************/

void MainFrame::Initialize()
{   
  // Show the cursor as an hourglas
  wxBusyCursor wait;
  SetAutoLayout(TRUE);
  SetIcon(wxICON(APP_ICON)); 		

#if ADD_MENUBAR   
  /* Create the menubar */
  CreateMenu();
#endif

#if ADD_TOOLBAR  
  /* Create the toolbar */
  CreateToolbar();
#endif
  
  /* Set all the shortcuts */
  wxAcceleratorEntry entries[NO_SHORTCUTS];
  entries[0].Set  (wxACCEL_NORMAL, WXK_TAB,    SC_TAB);
  entries[1].Set  (wxACCEL_NORMAL, WXK_ESCAPE, SC_ESC);
  
  /* Make the accelerator table and add it to the frame*/
  wxAcceleratorTable accel(NO_SHORTCUTS, entries);
  SetAcceleratorTable(accel);

  // CreateStatusBar(2);
}
                     

void MainFrame::CreateMenu()
{
  wxMenu **menus       = NULL;
  int      i           = 0;
  wxString menunames[] = {_("&Files"), _("&Mark"), _("&Commands"), 
                          _("&Show"), _("&Configuration"), _("&Start"), 
                          _("&Help")};	
  
  m_menubar = new wxMenuBar;
  menus = new wxMenu*[NO_MENUS];
    	 
#ifdef WIN32
  // In windows, the menu bar must be attached ! 
  m_menubar->Attach(this);
#endif
	
  for(i=0; i < NO_MENUS; i++)	 {
    menus[i] = new wxMenu;        
    m_menubar->Append(menus[i], menunames[i]);
  }  

  /* Files menu */
  menus[FILES_MENU]->Append(FILES_MENU_EXIT,   _("&Exit\tAlt+Q"));

  /* Mark menu */
  
  /* Commands menu */

  /* Show menu */

  /* Configuration menu */

  /* Start menu */

  /* Help menu */ 
  
  SetMenuBar(m_menubar);
}


void MainFrame::AddTool(wxBitmap bmp, wxString s, int id) 
{
  ASSERT(m_toolbar);
  m_toolbar->AddTool(id, bmp, wxNullBitmap, FALSE, -1, -1, (wxObject*)NULL, s);
}


void MainFrame::CreateToolbar(BOOL horizontal)
{
  /* Delete and recreate the toolbar */
  m_toolbar = GetToolBar();	
  SetToolBar(NULL);
  m_toolbar = NULL;
 
  long style;
  /* Set style for tool bar */
  if(horizontal)
    style = wxNO_BORDER | wxTB_FLAT | wxTB_HORIZONTAL;
  else
    style = wxNO_BORDER | wxTB_FLAT | wxTB_VERTICAL;

  
  /* Create new toolbar */
  if(!(m_toolbar = CreateToolBar(style)))
    THROW_CRITICAL((_("Toolbar could not be created")));
  
  m_toolbar->SetToolBitmapSize(wxSize(16, 16));  

  AddTool(csSMALL_ICON(TB_REREAD_ICON), _("Reread"), COMMANDS_MENU_REREAD); 
  AddTool(csSMALL_ICON(TB_CD_TREE_ICON), _("Cd tree"), COMMANDS_MENU_CD_TREE); 

  m_toolbar->AddSeparator();

  AddTool(csSMALL_ICON(TB_BRIEF_ICON), _("Brief"), SHOW_MENU_BRIEF); 
  AddTool(csSMALL_ICON(TB_FULL_ICON), _("Full"), SHOW_MENU_FULL); 
  AddTool(csSMALL_ICON(TB_TREE_ICON), _("Tree"), SHOW_MENU_TREE); 

  m_toolbar->AddSeparator();

  AddTool(csSMALL_ICON(TB_INVERT_ICON), _("Invert"), MARK_MENU_INVERT); 
  AddTool(csSMALL_ICON(TB_BACK_ICON), _("<-"), COMMANDS_MENU_GO_BACK); 
  AddTool(csSMALL_ICON(TB_FORWARD_ICON), _("->"), COMMANDS_MENU_GO_FORWARD); 

  m_toolbar->AddSeparator();

  AddTool(csSMALL_ICON(TB_FTP_CONNECT_ICON), _("Ftp connect"), 
                    COMMANDS_MENU_FTP_CONNECT);   
  AddTool(csSMALL_ICON(TB_FTP_NEW_CONNECTION_ICON), _("Ftp new connection"), 
                    COMMANDS_MENU_FTP_NEW_CONNECTION);

      
  /* Reflect changes */
  m_toolbar->Realize();
}



/*****************************************************************************/
/* Event handlers                                                            */
/*****************************************************************************/


void MainFrame::OnExit(wxCommandEvent& event)
{
  APP_MNG()->Exit();
}

void MainFrame::OnAbout(wxCommandEvent& event)
{
  APP_MNG()->About();
}

void MainFrame::OnShortcut(wxCommandEvent& event)
{
  switch(event.GetId()){       
    case SC_TAB:    APP_MNG()->KeyTab(); return;     
    case SC_ESC:    APP_MNG()->KeyEsc(); return;     
    default: break; 
  }
  
  /* Make sure the event is handled */
  event.Skip();
}
