/*---------------------------------------------------------------------------*
 | Copyright (C) 2000 Crüger Software
 | 
 | File           : lowerpanel.cpp
 | Written by     : rcl                    Date: august 2000
 | Reviewed by    :                        Date: 
 | Description    : 
 |                : 
 |                :
 *---------------------------------------------------------------------------*/

/* for g++ compilation */
#ifdef __GNUG__
#pragma  implementation "lowerpanel.h"
#endif

// For compilers that support precompilation, includes "wx/wx.h".
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
#include "lowerpanel.h"
#include "main.h"

/* This line enables the function wxGetApp(), which return a handle to the 
   one and only instance of class Main */
DECLARE_APP(Main); 

/*---------------------------------------------------------------------------*/
/* Event Handler Table                                                       */
/*---------------------------------------------------------------------------*/
BEGIN_EVENT_TABLE(LowerPanel, wxPanel)

EVT_SIZE(                              LowerPanel::OnSize)
EVT_FILELIST_DIR_CHANGED(ID_FILE_LIST, LowerPanel::OnDirChanged)

END_EVENT_TABLE()


/*---------------------------------------------------------------------------*/
/* Constructor/destructor                                                    */
/*---------------------------------------------------------------------------*/
LowerPanel::LowerPanel(wxFrame *parent, long id)
 : wxPanel(parent, 
           id, 
           wxDefaultPosition, 
           wxDefaultSize)
{

  m_commands    = NULL;
  m_commandpath = NULL;
  m_edit        = NULL;
  m_line1        = NULL;

  Initialize();     
}


LowerPanel::~LowerPanel()
{
  DEL(m_line1);  
}

/*****************************************************************************/
/* Public methods                                                            */
/*****************************************************************************/

void LowerPanel::SetDirname(wxString dirname)
{
  m_commandpath->SetLabel(dirname + ">");  
  Layout();
}


/*****************************************************************************/
/* Private methods                                                           */
/*****************************************************************************/

void LowerPanel::Initialize()
{
  CreateWidgets();

  m_commands->SetFont(cCOMMANDER_FONT);
  m_commandpath->SetFont(cCOMMANDER_FONT);
}
 

void LowerPanel::CreateWidgets()
{
  SetAutoLayout(TRUE);
  wxLayoutConstraints *c = NULL;
  
  /* Combobox for commands */
  m_commands = new wxComboBox(this, ID_COMMANDS);
  
  /* Text for showing actual path */
  m_commandpath =  new wxStaticText(this, -1, "c:\\>", wxDefaultPosition,
                                    wxDefaultSize, wxALIGN_RIGHT);
  

  m_line1 = new wxStaticLine(this, -1, wxPoint(0, 30), 
                            wxSize(GetSize().GetWidth(), 2));

  m_line2 = new wxStaticLine(this, -1, wxPoint(0, 0), 
                            wxSize(GetSize().GetWidth(), 2));

  c = new wxLayoutConstraints;
  c->top.SameAs(this, wxTop);
  c->right.SameAs(this, wxRight, 0);
  c->left.PercentOf(this, wxWidth, 33);
  c->bottom.SameAs(this, wxBottom, 4);  
  m_commands->SetConstraints(c);
  
  c = new wxLayoutConstraints;  
  c->centreY.SameAs(m_commands, wxCentreY);  
  c->left.SameAs(this, wxLeft, 5);
  c->right.SameAs(m_commands, wxLeft, 5);  
  c->height.Absolute(18);
  m_commandpath->SetConstraints(c);
}


/*****************************************************************************/
/* Event handlers                                                            */
/*****************************************************************************/

void LowerPanel::OnSize(wxSizeEvent &event)
{
  Layout();  
  if(m_line1){
    int w = this->GetSize().GetWidth();
    m_line1->SetSize(w,2);
  }

  if(m_line2){
    int w = this->GetSize().GetWidth();
    m_line2->SetSize(w,2);
  }
  return;
}

void LowerPanel::OnDirChanged(FileListEvent& event)
{  
  SetDirname(event.GetDirectory());
  event.Skip();
}



/*---------------------------------------------------------------------------*/
/* Event Handler Table                                                       */
/*---------------------------------------------------------------------------*/
BEGIN_EVENT_TABLE(LowerButtonPanel, wxPanel)

EVT_BUTTON(ID_BT_VIEW,   LowerButtonPanel::OnView)
EVT_BUTTON(ID_BT_EDIT,   LowerButtonPanel::OnEdit)
EVT_BUTTON(ID_BT_COPY,   LowerButtonPanel::OnCopy)
EVT_BUTTON(ID_BT_RENMOV, LowerButtonPanel::OnMove)
EVT_BUTTON(ID_BT_MKDIR,  LowerButtonPanel::OnMkDir)
EVT_BUTTON(ID_BT_DELETE, LowerButtonPanel::OnDelete)
EVT_BUTTON(ID_BT_EXIT,   LowerButtonPanel::OnExit)

END_EVENT_TABLE()


/*---------------------------------------------------------------------------*/
/* Constructor/destructor                                                    */
/*---------------------------------------------------------------------------*/
LowerButtonPanel::LowerButtonPanel(wxFrame *parent, long id)
 : wxPanel(parent, 
           id, 
           wxDefaultPosition, 
           wxDefaultSize)
{

  m_buttons     = NULL;
  Initialize();     
}


LowerButtonPanel::~LowerButtonPanel()
{
}

/*****************************************************************************/
/* Public methods                                                            */
/*****************************************************************************/

/*****************************************************************************/
/* Private methods                                                           */
/*****************************************************************************/

void LowerButtonPanel::Initialize()
{
  CreateWidgets();
}
 

void LowerButtonPanel::CreateWidgets()
{
  SetAutoLayout(TRUE);
  wxLayoutConstraints *c = NULL;
  
  m_buttons = new wxButton*[7];
  m_buttons[ID_BT_VIEW] = new wxButton(this, ID_BT_VIEW, _("F3 View"));  
  m_buttons[ID_BT_EDIT] = new wxButton(this, ID_BT_EDIT, _("F4 Edit"));
  m_buttons[ID_BT_COPY] = new wxButton(this, ID_BT_COPY, _("F5 Copy"));
  m_buttons[ID_BT_RENMOV] = new wxButton(this, ID_BT_RENMOV, _("F6 RenMov"));
  m_buttons[ID_BT_MKDIR] = new wxButton(this, ID_BT_MKDIR, _("F7 MkDir"));
  m_buttons[ID_BT_DELETE] = new wxButton(this, ID_BT_DELETE, _("F8 Delete"));
  m_buttons[ID_BT_EXIT] = new wxButton(this, ID_BT_EXIT, _("Alt+F4 Exit"));
  
  for(int i = 0; i < NO_BUTTONS; i++){  
    c = new wxLayoutConstraints;
    c->top.SameAs(this, wxTop, 5);       
    
    if(i==0)
      c->left.PercentOf(this, wxWidth, 1);      
    else
      c->left.SameAs(m_buttons[i-1], wxRight, 0);      

    c->bottom.SameAs(this, wxBottom, 5);
    c->width.PercentOf(this, wxWidth, 14);    
    m_buttons[i]->SetFont(cCOMMANDER_FONT);
    m_buttons[i]->SetConstraints(c);
  }   
  Layout();
}


/*****************************************************************************/
/* Event handlers                                                            */
/*****************************************************************************/

void LowerButtonPanel::OnView(wxCommandEvent& event)
{
  APP_MNG()->View();
}

void LowerButtonPanel::OnEdit(wxCommandEvent& event)
{
  APP_MNG()->Edit();
}


void LowerButtonPanel::OnCopy(wxCommandEvent& event)
{
  APP_MNG()->Copy();
}


void LowerButtonPanel::OnMove(wxCommandEvent& event)
{
  APP_MNG()->Move();
}


void LowerButtonPanel::OnMkDir(wxCommandEvent& event)
{
  APP_MNG()->MkDir();
}


void LowerButtonPanel::OnDelete(wxCommandEvent& event)
{
  APP_MNG()->Delete();
}


void LowerButtonPanel::OnExit(wxCommandEvent& event)
{
  APP_MNG()->Exit();    
}
