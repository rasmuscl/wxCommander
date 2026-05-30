/*---------------------------------------------------------------------------*
 | 
 | File           : $Id: $
 | Written by     :                        Date: 
 | Reviewed by    :                        Date: rcl
 | Description    : Header file for AppManager
 |                : 
 |                :
 *---------------------------------------------------------------------------*/

#ifndef __APPMANAGER_H_
#define __APPMANAGER_H_

/* For g++ compilation */
#ifdef __GNUG__
#pragma interface "appmanager.h"
#endif

#include <configit_base.h>
#include <configit_gui.h>
#include <wx/splitter.h>
#include <wx/resource.h>
#include <wx/statline.h>
#include <wx/listctrl.h>
#include "mainframe.h"
#include "drivebuttonpanel.h"
#include "fileview.h"
#include "lowerpanel.h"


/*****************************************************************************/
/* Definitions                                                               */
/*****************************************************************************/
#define ID_LEFT_DRIVE_PANEL   9000
#define ID_RIGHT_DRIVE_PANEL  9001
#define ID_SPLIT_WINDOW       9002
#define ID_LOWER_PANEL        9003
#define ID_LOWER_BUTTON_PANEL 9004
#define ID_LEFT_VIEW          9050
#define ID_RIGHT_VIEW         9051



/*****************************************************************************/
/* Class definition                                                          */
/*****************************************************************************/
class SplitWindow: public wxSplitterWindow
{
public:
  // Constructor / destructor
  SplitWindow(wxFrame *parent, long id);
  ~SplitWindow(){};

private:
  
  // Event methods
  void              OnSize(wxSizeEvent& event);  


  DECLARE_EVENT_TABLE()
};



/*****************************************************************************/
/* Class definition                                                          */
/*****************************************************************************/

class AppManager: public wxObject
{
public:
  /* Con-/destructor methods */
  AppManager(wxWindow *parent = NULL);
  ~AppManager();
    
  /* Normal methods */
  void              ShowMainFrame();
  void              About();
  void              SizeChanged(wxSize size);
  void              LoadDirectory(wxString dir_path);
  void              SetActiveFileView(FileView* file_view);
  void              SetDirname(wxString dirname);
  
  void              KeyTab();
  void              KeySpace();
  void              KeyEnter();
  void              KeyRight();
  void              KeyLeft();
  void              KeyUp();
  void              KeyDown();
  void              KeyEsc();

  void              View();
  void              Edit();
  void              Copy();
  void              Move();
  void              MkDir();
  void              Delete();
  void              Exit();
  
  
  BOOL              GetSmallIcon(wxIcon& icon, wxString ext);
    
  /* Get/set methods */
  MainFrame*        GetMainFrame(){return m_mainframe;}  
    
private:
  /* Initializing methods: */
  void              Initialize();
  void              CreateControls();
    
private:
  /* Attributes */
  MainFrame        *m_mainframe;

  /* Used for the drive buttons / mount buttons */
  DriveButtonPanel *m_left_drive_panel;
  DriveButtonPanel *m_right_drive_panel;
  
  /* Splitting the window in two halfs */
  wxSplitterWindow *m_split_window;
  
  /* The two halfs + a pointer to the active one */
  FileView         *m_left_view;
  FileView         *m_right_view;
  FileView         *m_active_view;  
  
  /* The lower panel with the commandcombobox */
  LowerPanel       *m_lowerpanel;
  LowerButtonPanel *m_lowerbuttonpanel;

  /* ConfigIt settings */
  SettingsTable     m_settings_table;
};


#endif /* __AppManager_H_ */
