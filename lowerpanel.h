/*---------------------------------------------------------------------------*
 | Copyright (C) 2000 Crüger Software
 |
 | 
 | 
 | 
 | 
 | File           : main.cpp
 | Written by     : rcl                    Date: august 2000
 | Reviewed by    :                        Date: 
 | Description    : 
 |                : 
 |                :
 *---------------------------------------------------------------------------*/

#ifndef __LOWERPANEL_H_
#define __LOWERPANEL_H_

/* For g++ compilation */
#ifdef __GNUG__
#pragma interface "lowerpanel.h"
#endif

#include <configit_base.h>
#include <configit_gui.h>
#include <wx/statline.h>

#include "filelist.h"

/*****************************************************************************/
/* Defines                                                                   */
/*****************************************************************************/
#define ID_COMMANDS   8001
#define ID_PANEL      8002

enum
{
  ID_BT_VIEW,
  ID_BT_EDIT,
  ID_BT_COPY,
  ID_BT_RENMOV,
  ID_BT_MKDIR,
  ID_BT_DELETE,
  ID_BT_EXIT,
  NO_BUTTONS
};

/*****************************************************************************/
/* Class definition                                                          */
/*****************************************************************************/
class LowerPanel: public wxPanel
{

public:
  /* Constructor / destructor */
  LowerPanel(wxFrame *frame, long id);
  ~LowerPanel();

  void              SetDirname(wxString dirname);
  
private:  
  void              Initialize();
  void              CreateWidgets();

  /* Eventhandlers: */
  void              OnSize(wxSizeEvent &event);  
  void              OnDirChanged(FileListEvent& event);
  
  wxComboBox       *m_commands;
  wxStaticText     *m_commandpath;
  wxStaticText     *m_selectedleft;
  wxStaticText     *m_selectedright;
  wxButton        **m_buttons;
  wxButton         *m_edit;
  wxStaticLine     *m_line1;
  wxStaticLine     *m_line2;

  DECLARE_EVENT_TABLE()
};


/*****************************************************************************/
/* Class definition                                                          */
/*****************************************************************************/
class LowerButtonPanel: public wxPanel
{

public:
  /* Constructor / destructor */
  LowerButtonPanel(wxFrame *frame, long id);
  ~LowerButtonPanel();

private:  
  void              Initialize();
  void              CreateWidgets();

  void              OnView(wxCommandEvent &event);
  void              OnEdit(wxCommandEvent &event);  
  void              OnCopy(wxCommandEvent &event);
  void              OnMove(wxCommandEvent &event);
  void              OnMkDir(wxCommandEvent &event);
  void              OnDelete(wxCommandEvent &event);
  void              OnExit(wxCommandEvent &event);  
  void              OnOnEdit(wxCommandEvent& event);

  wxButton        **m_buttons;
  DECLARE_EVENT_TABLE()
};

#endif  //__LOWERPANEL_H_
