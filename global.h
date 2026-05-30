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

#ifndef __GLOBAL_H_
#define __GLOBAL_H_

/* For g++ compilation */
#ifdef __GNUG__
#pragma interface "global.h"
#endif

/* Name of the application */
#define APP_NAME                "wxCommander"
#define ADD_TOOL_BAR            0
#define ADD_MENU_BAR            1

/* Default values about the user */
#define DEFAULT_USER_NAME       (char*)"NA" 
#define DEFAULT_COMPANY_NAME    (char*)"NA" 
#define DEFAULT_LICENSE_KEY     (char*)"NA"

/* Macro for getting a pointer to the manager */
#define APP_MNG()               wxGetApp().GetAppManager()

#ifndef WIN32
#define BOOL  int
#define TRUE  1
#define FALSE 0
#endif

#define pbTB_ICON(name) wxIcon(#name, wxBITMAP_TYPE_ICO_RESOURCE, 16, 16)


#ifdef WIN32
#define cCOMMANDER_FONT wxFont(9, wxDEFAULT, wxNORMAL, wxBOLD)
#else
#define cCOMMANDER_FONT wxFont(12, wxDEFAULT, wxNORMAL, wxBOLD)
#endif

#define cDARK_BLUE wxColour(0, 0, 128)
#define cDARK_GRAY wxColour(128, 128, 128)

#endif // __GLOBAL_H_

