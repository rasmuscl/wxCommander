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

/* For g++ compilation */
#ifdef __GNUG__
#pragma  implementation "main.h"
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

/* Other includes goes here */
#include "main.h"
#include "filelist.h"

#define CASE(id) case id: return #id; break;


// Create a new application object: this macro will allow wxWindows to create
// the application object during program execution (it's better than using a
// static object for many reasons) and also declares the accessor function
// wxGetApp() which will return the reference of the right type (i.e. MyApp and
// not wxApp)
IMPLEMENT_APP(Main)


/*---------------------------------------------------------------------------*/
/* Event Handler Table                                                       */
/*---------------------------------------------------------------------------*/
BEGIN_EVENT_TABLE(Main, wxApp)

EVT_KEY_DOWN(Main::OnKeyDown)

END_EVENT_TABLE()   



/*---------------------------------------------------------------------------*/
/* Constructor/destructor                                                    */
/*---------------------------------------------------------------------------*/

Main::Main()
{
  m_app_manager = NULL;    
}

Main::~Main()
{
  // DEL(m_app_manager);
}


/*****************************************************************************/
/* Public methods                                                            */
/*****************************************************************************/

/*---------------------------------------------------------------------------*/
/* Initialization function called on application start                       */
/*---------------------------------------------------------------------------*/
bool Main::OnInit()
{
#ifdef __CONFIGIT_GUI_H_
  csGui::InitializeApp();
#endif  

  /* Register the application specific errorhandler */
#ifdef __CONFIGIT_BASE_H_
  ::msg_register_error_handler(&Main::AppErrorHandler);	
#endif

  /* Create an instance of the AppController */
  m_app_manager = new AppManager;

  /* Make the mainframe appear on the screen */
  m_app_manager->ShowMainFrame();
  
  /* And make sure it is the top most window */
  SetTopWindow((wxWindow*)m_app_manager->GetMainFrame());

  /*
  MainFrame *mainframe = new MainFrame(APP_NAME, wxDefaultPosition, 
                                       wxSize(600, 600));
  FileList *list = new FileList(mainframe, ID_FILE_LIST);    
  mainframe->SetAutoLayout(TRUE);
  wxLayoutConstraints *c = new wxLayoutConstraints;
  c->top.SameAs(mainframe, wxTop);
  c->left.SameAs(mainframe, wxLeft);
  c->right.SameAs(mainframe, wxRight);
  c->bottom.SameAs(mainframe, wxBottom);
  list->SetConstraints(c);
  mainframe->Layout();
  mainframe->Center();
  mainframe->Show();  
  SetTopWindow(mainframe);*/

  return TRUE;
}


int Main::OnExit()
{
  return EXIT_SUCCESS;
}

/*****************************************************************************/
/* Private methods                                                           */
/*****************************************************************************/
#ifdef __CONFIGIT_BASE_H_
/* Error handler */
void Main::AppErrorHandler(ErrorBuffer* error_buffer)
{
  wxString errortype    = "";  
  wxString location     = "";
  wxString errorstring  = "";
  int      msgstyle     = wxICON_STOP;

  switch(error_buffer->errtype){
  case ERR_CRITICAL: 
    errortype = "Critical error";
    break;
  case ERR_USER :
    errortype = "Error";
    msgstyle  = wxICON_EXCLAMATION;
    break;
  case ERR_WARNING :
    errortype = "Warning";
    msgstyle  = wxICON_EXCLAMATION;
    break;
  default :
    errortype = "Unknown error type";
  }

  errorstring = error_buffer->errormsg;

#ifdef DEBUG
  location.Printf("\n\n(Error located in %s: %d)", error_buffer->filename, 
		  error_buffer->linenumber);
  errorstring += location;
#endif
      
  wxMessageBox(errorstring, errortype, msgstyle); 
}
#endif


void Main::OnKeyDown(wxKeyEvent& event)
{
  switch(event.GetKeyCode()){      
    case WXK_RIGHT: APP_MNG()->KeyRight(); break;    
    default: break;
  }

  /* Make sure the event is handled */
  event.Skip();
}





