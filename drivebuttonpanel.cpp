/*---------------------------------------------------------------------------*
 | 
 | File           : $Id: $
 | Written by     :                        Date: 
 | Reviewed by    :                        Date: rcl
 | Description    : Source file for DriveButtonPanel
 |                : 
 |                :
 *---------------------------------------------------------------------------*/

/* For g++ compilation */
#ifdef __GNUG__
#pragma  implementation "drivebuttonpanel.h"
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
#include "bitmaps/tb_cdrom_icon.xpm"
#include "bitmaps/tb_floppy_icon.xpm"
#include "bitmaps/tb_network_icon.xpm"
#include "bitmaps/tb_drive_icon.xpm"
#endif /* USE_XPM_BITMAPS */


#include <wx/statline.h>

/* Other includes goes here */
#include "drivebuttonpanel.h"
#include "main.h"

/* This line enables the function wxGetApp(), which return a handle to the 
   one and only instance of class Main */
DECLARE_APP(Main); 

/*---------------------------------------------------------------------------*/
/* Event Handler Table                                                       */
/*---------------------------------------------------------------------------*/
BEGIN_EVENT_TABLE(DriveButtonPanel, wxPanel)

END_EVENT_TABLE()   


/*---------------------------------------------------------------------------*/
/* Constructor/destructor                                                    */
/*---------------------------------------------------------------------------*/

DriveButtonPanel::DriveButtonPanel(wxWindow *parent, wxWindowID id) : 
                                              wxPanel(parent, id)
{
  m_buttons_bar  = NULL;  
  Initialize();
}

DriveButtonPanel::~DriveButtonPanel()
{ 
  
}


/*****************************************************************************/
/* Public methods                                                            */
/*****************************************************************************/

/*****************************************************************************/
/* Private methods                                                           */
/*****************************************************************************/

void DriveButtonPanel::Initialize()
{ 
  wxLayoutConstraints *c = NULL;
  SetAutoLayout(TRUE);
  wxStaticLine *line = NULL;
  wxStaticText *label = NULL;
  
  long style = wxNO_BORDER | wxTB_FLAT | wxTB_HORIZONTAL;

  m_buttons_bar = new wxToolBar(this, ID_DRIVE_BUTTON_BAR, wxDefaultPosition,
                                wxDefaultSize, style);

  m_buttons_bar->SetToolBitmapSize(wxSize(16, 16));  
  
  /* Make the layout for the controls */
  c = new wxLayoutConstraints;
  c->top.SameAs(this, wxTop);  
  c->height.Absolute(28);
  c->left.SameAs(this, wxLeft);
  c->right.SameAs(this, wxRight);
  m_buttons_bar->SetConstraints(c); 
  
  AddTool(csSMALL_ICON(TB_FLOPPY_ICON), _("Floppy"), 5000); 
  AddTool(csSMALL_ICON(TB_CDROM_ICON), _("Cd ROM"), 5001); 
  
  AddTool(csSMALL_ICON(TB_DRIVE_ICON), _("Drive"), 5002); 
  AddTool(csSMALL_ICON(TB_DRIVE_ICON), _("Drive"), 5003); 
  AddTool(csSMALL_ICON(TB_DRIVE_ICON), _("Drive"), 5004); 
  AddTool(csSMALL_ICON(TB_DRIVE_ICON), _("Drive"), 5005); 
  AddTool(csSMALL_ICON(TB_NETWORK_ICON), _("Network"), 5006);
  m_buttons_bar->Realize();

  /* Line above buttons */
  line = new wxStaticLine(this, -1);
  c = new wxLayoutConstraints;
  c->top.SameAs(this, wxTop);  
  c->height.Absolute(2);  
  c->left.SameAs(this, wxLeft);
  c->right.SameAs(this, wxRight, -1);  
  line->SetConstraints(c); 

  /* Line below buttons */
  line = new wxStaticLine(this, -1);
  c = new wxLayoutConstraints;
  c->top.SameAs(this, wxTop, 28);  
  c->height.Absolute(2);  
  c->left.SameAs(this, wxLeft);
  c->right.SameAs(this, wxRight, -1);  
  line->SetConstraints(c); 

  Layout();
}


void DriveButtonPanel::AddTool(wxBitmap bmp, wxString s, int id) 
{
  ASSERT(m_buttons_bar);
  m_buttons_bar->AddTool(id, bmp, wxNullBitmap, FALSE, -1, -1, 
                         (wxObject*)NULL, s);
}


/*****************************************************************************/
/* Event handlers                                                            */
/*****************************************************************************/

