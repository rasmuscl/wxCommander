/*---------------------------------------------------------------------------*
 | Copyright (C) 2000 Rasmus Crüger Lund
 | 
 | 
 | File           : $Id: $
 | Written by     : rcl                    Date: apr 2001
 | Reviewed by    :                        Date: apr 2001
 | Description    : 
 |                : 
 |                :
 *---------------------------------------------------------------------------*/

#ifndef __MAIN_H_
#define __MAIN_H_

/* For g++ compilation */
#ifdef __GNUG__
#pragma interface "main.h"
#endif

#include <configit_base.h>
#include "appmanager.h"

/*****************************************************************************/
/* Definitions                                                               */
/*****************************************************************************/
class FileListEvent;

/*****************************************************************************/
/* Main class representing ConfigIt Stuido application                       */
/*****************************************************************************/
class Main : public wxApp
{
public:
  Main();
  ~Main();
  
  /* this one is called on application startup and is a good place for the 
     app initialization (doing it here and not in the ctor allows to have 
     an error return: if OnInit() returns false, the application terminates)
  */
  virtual bool      OnInit();  
  virtual int       OnExit();  
  AppManager*       GetAppManager(){return m_app_manager;}

private:
  /* Event handlers */
  void              OnKeyDown(wxKeyEvent& event);

  
  AppManager       *m_app_manager;  
  static void       AppErrorHandler(ErrorBuffer* errbuf);
  
  DECLARE_EVENT_TABLE()  
};



#endif /* __MAIN_H_ */

