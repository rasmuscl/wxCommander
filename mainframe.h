/*---------------------------------------------------------------------------*
 |  
 | File           : mainframe.h
 | Written by     : rcl 21/02/2001
 | Description    : Header file for class MainFrame
 |                :
 *---------------------------------------------------------------------------*/

#ifndef __MAINFRAME_H_
#define __MAINFRAME_H_

/* For g++ compilation */
#ifdef __GNUG__
#pragma interface "mainframe.h"
#endif

#include "global.h"


/*****************************************************************************/
/* Definitions                                                               */
/*****************************************************************************/


#define ADD_MENUBAR     1
#define ADD_STATUSBAR   1
#define ADD_TOOLBAR     1
#define MAINFRAME_ID    6000

enum{
  FILES_MENU,
  COMMANDS_MENU,
  SHOW_MENU,
  CONFIGURATION_MENU,
  MARK_MENU,
  START_MENU,
  HELP_MENU,
  NO_MENUS
};

enum 
{
  /* Files */
  FILES_MENU_CHANGE_ATTRIBUTES = 100,
  FILES_MENU_PACK,
  FILES_MENU_UNPACK,
  FILES_MENU_TEST_ARCHIVE,
  FILES_MENU_COMPARE,
  FILES_MENU_ASSOCIATE,
  FILES_MENU_PROPERTIES,
  FILES_MENU_SPACE,
  FILES_MENU_RENAME_TOOL,
  FILES_MENU_PRINT,
  FILES_MENU_SPLIT,
  FILES_MENU_COMBINE,
  FILES_MENU_ENCODE,
  FILES_MENU_DECODE,
  FILES_MENU_EXIT,

  /* Mark */
  MARK_MENU_SELECT_GROUP,
  MARK_MENU_UNSELECT_GROUP,
  MARK_MENU_SELECT_ALL,
  MARK_MENU_UNSELECT_ALL,
  MARK_MENU_INVERT,
  MARK_MENU_RESTORE,
  MARK_MENU_COMPARE_DIRS,
  MARK_MENU_MARK_NEWER,

  /* Commands */
  COMMANDS_MENU_REREAD,
  COMMANDS_MENU_CD_TREE,  
  COMMANDS_MENU_SEARCH,
  COMMANDS_MENU_VOLUME_LABEL,
  COMMANDS_MENU_SYSTEM_INFORMATION,
  COMMANDS_MENU_SYNCHRONIZE_DIRS,
  COMMANDS_MENU_DIRECTORY_HOTLIST,
  COMMANDS_MENU_GO_BACK,
  COMMANDS_MENU_GO_FORWARD,
  COMMANDS_MENU_PROMPT,
  COMMANDS_MENU_NETWORK_CONNECTIONS,
  COMMANDS_MENU_DISCONNECT_NETWORK_DRIVES,
  COMMANDS_MENU_SHARE_DIRECTORY,
  COMMANDS_MENU_UNSHARE_DIRECTORY,
  COMMANDS_MENU_FTP_CONNECT,
  COMMANDS_MENU_FTP_NEW_CONNECTION,
  COMMANDS_MENU_FTP_DISCONNECT,
  COMMANDS_MENU_FTP_SHOW_HIDDEN,
  COMMANDS_MENU_FTP_DOWNLOAD_FROM_LIST,
  COMMANDS_MENU_PORT_CONNECTION,
  COMMANDS_MENU_SOURCE,
  COMMANDS_MENU_TARGET,

  /* Show */
  SHOW_MENU_BRIEF,
  SHOW_MENU_FULL,
  SHOW_MENU_TREE,
  SHOW_MENU_QUICK_VIEW,
  SHOW_MENU_ALL_FILES,
  SHOW_MENU_PROGRAMS,
  SHOW_MENU_STAR,
  SHOW_MENU_CUSTOM,
  SHOW_MENU_NAME,
  SHOW_MENU_EXT,
  SHOW_MENU_TIME,
  SHOW_MENU_SIZE,
  SHOW_MENU_UNSORTED,
  SHOW_MENU_REVERSED_ORDER,
  SHOW_MENU_RELOAD,

  /* Configuration */
  CONFIGURATION_MENU_OPTIONS,  
  CONFIGURATION_MENU_BUTTONS_BAR,  
  CONFIGURATION_MENU_SAVE_POS,  
  CONFIGURATION_MENU_SAVE_SETTINGS,  

  // Start
  START_MENU_CHANGE_START_MENU,
  START_MENU_CHANGE_MAIN_MENU,

  // Help
  HELP_MENU_SHOWINDEX,
  HELP_MENU_KEYBOARD,
  HELP_MENU_REGISTRATION,
  HELP_MENU_WEBINFO,
  HELP_MENU_ABOUT
};


enum
{
  SC_TAB = 7400,
  SC_ESC,
  NO_SHORTCUTS
};


/*****************************************************************************/
/* Class definition                                                          */
/*****************************************************************************/
class MainFrame: public wxFrame
{
public:
  /* Con-/destructor methods */
  MainFrame(const wxString& title, 
	          const wxPoint& pos = wxDefaultPosition, 
            const wxSize& size = wxDefaultSize);
  ~MainFrame();
  
private:
  /* Initializing methods: */
  void              Initialize();

  /* Other methods */
  void              CreateMenu();
  void              CreateToolbar(BOOL horizontal = TRUE);
  void              AddTool(wxBitmap bmp, wxString str, int id);

  /* Event handlers */
  void              OnExit(wxCommandEvent& event);
  void              OnAbout(wxCommandEvent& event);
  void              OnShortcut(wxCommandEvent& event);
  
private:	
  wxToolBarBase   *m_toolbar;
  wxMenuBar       *m_menubar;  
    
  DECLARE_EVENT_TABLE()    
};


#endif  /* __MAINFRAME_H_ */
