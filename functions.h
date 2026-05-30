/*---------------------------------------------------------------------------*
 | Copyright (C) 2001 Crüger Software
 | 
 | File           : misc.cpp
 | Written by     : rcl                    Date: april 2001
 | Description    : Some common functions 
 |                : 
 |                :
 *---------------------------------------------------------------------------*/

#ifndef __FUNCTIONS_H_
#define __FUNCTIONS_H_

/* For g++ compilation */
#ifdef __GNUG__
#pragma interface "functions.h"
#endif

#include <configit_base.h>
#include <configit_gui.h>


/*****************************************************************************/
/* File functions                                                            */
/*****************************************************************************/

wxString          GetFileAttributes(wxString file);
long              GetFileSize(wxString file);
wxString          GetParentDir(wxString path);

wxString          FileCat(wxString file1, wxString file2);

BOOL              IsHidden(wxString file);
BOOL              IsArchive(wxString file);
BOOL              IsExecutable(wxString file);
BOOL              IsLink(wxString file);
BOOL              IsLinkDir(wxString file);
BOOL              IsDir(wxString file);
BOOL              IsRegular(wxString file);



/*****************************************************************************/
/* Format functions                                                          */
/*****************************************************************************/

wxString          FormatDate(wxString file);
wxString          FormatSize(long byte_size);



#endif /* __FUNCTIONS_H_ */
