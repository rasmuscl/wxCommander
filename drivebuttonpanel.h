/*---------------------------------------------------------------------------*
 | 
 | File           : $Id: $
 | Written by     :                        Date: 
 | Reviewed by    :                        Date: rcl
 | Description    : Header file for DriveButtonPanel
 |                : 
 |                :
 *---------------------------------------------------------------------------*/

#ifndef __DRIVEBUTTONPANEL_H_
#define __DRIVEBUTTONPANEL_H_

/* For g++ compilation */
#ifdef __GNUG__
#pragma interface "drivebuttonpanel.h"
#endif

#include <configit_base.h>
#include <configit_gui.h>

#include <wx/toolbar.h>

/*****************************************************************************/
/* Definitions                                                               */
/*****************************************************************************/
#define ID_DRIVE_BUTTON_BAR   5000
#define ID_MOUNT_BAR          6001


/*****************************************************************************/
/* Class definition                                                          */
/*****************************************************************************/
class DriveButtonPanel: public wxPanel
{
public:
  /* Con-/destructor methods */
  DriveButtonPanel(wxWindow *parent, wxWindowID id);
  ~DriveButtonPanel();
   
private:
  /* Initializing methods: */
  void              Initialize();
  void              AddTool(wxBitmap bmp, wxString str, int id);

  /* Event handlers */

    
  /* Attributes */
  wxToolBar        *m_buttons_bar;  
  DECLARE_EVENT_TABLE()    
};


#endif /* __DRIVEBUTTONPANEL_H_ */
