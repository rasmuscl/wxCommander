/*---------------------------------------------------------------------------*
 | Copyright (C) 2001 Crüger Software
 | 
 | File           : misc.cpp
 | Written by     : rcl                    Date: april 2001
 | Description    : Some common functions 
 |                : 
 |                :
 *---------------------------------------------------------------------------*/

/* For g++ compilation */
#ifdef __GNUG__
#pragma  implementation "functions.h"
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
#endif /* USE_XPM_BITMAPS */

#include <wx/log.h>
#include <wx/config.h>
#include <wx/image.h>
#include <wx/dir.h>
#include <wx/datetime.h>
#include "wx/colordlg.h"    
#include <wx/ffile.h>

#ifndef WIN32
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <pwd.h>
#include <grp.h>
#include <fnmatch.h>
#endif

#include "functions.h"


/*****************************************************************************/
/* Internal functions                                                        */
/*****************************************************************************/


/*****************************************************************************/
/* File functions                                                            */
/*****************************************************************************/

/* Windows version of GetFileAttributes */
/*
CREATED    {* 2001-04-15 rcl *}
MODIFIED   {* *}
REVIEWED   {* *}
TESTED     {* *}
*/
#ifdef WIN32
wxString GetFileAttributes(wxString file)
{
  wxString att = "";

  DWORD a;
  a = ::GetFileAttributes(csWX2CHAR(file));
  att += (a & FILE_ATTRIBUTE_READONLY) ? "r" : "-";
  att += (a & FILE_ATTRIBUTE_ARCHIVE)  ? "a" : "-";
  att += (a & FILE_ATTRIBUTE_HIDDEN)   ? "h" : "-";
  att += (a & FILE_ATTRIBUTE_SYSTEM)   ? "s" : "-";

  return att;
}
#endif

/* Linux version of GetFileAttributes */
/*
CREATED    {* 2001-04-15 rcl *}
MODIFIED   {* *}
REVIEWED   {* *}
TESTED     {* *}
*/
#ifndef WIN32
wxString GetFileAttributes(wxString file)
{
  struct stat file_stat;  
  int u;
	int g;
	int o;
	char buf[11];
  mode_t mode;
	char *perm_sets[] = { "---", "--x", "-w-", "-wx", "r--", 
                        "r-x", "rw-", "rwx" };
    
  lstat(csWX2CHAR(file), &file_stat);
  mode  = file_stat.st_mode;

	u = (mode & S_IRWXU) >> 6;
 	g = (mode & S_IRWXG) >> 3;
  o = (mode & S_IRWXO);
  
	sprintf (buf, "-%s%s%s", perm_sets[u], perm_sets[g], perm_sets[o]);
	
	if (mode & S_ISVTX)
    buf[9] = (buf[9] == '-') ? 'T' : 't';
  if (mode & S_ISGID)
    buf[6] = (buf[6] == '-') ? 'S' : 's';
  if (mode & S_ISUID)
    buf[3] = (buf[3] == '-') ? 'S' : 's';
  
  if (S_ISLNK (mode))
    buf[0] = 'l';
  else if (S_ISDIR (mode))
    buf[0] = 'd';
  else if (S_ISBLK (mode))
    buf[0] = 'b';
  else if (S_ISCHR (mode))
    buf[0] = 'c';
  else if (S_ISFIFO (mode))
    buf[0] = 'f';
  else if (S_ISSOCK (mode))
    buf[0] = 's';
	
  return wxString(buf);
}
#endif


/* Windows version of GetFileSize */
/*
CREATED    {* 2001-04-15 rcl *}
MODIFIED   {* *}
REVIEWED   {* *}
TESTED     {* *}
*/
#ifdef WIN32
long GetFileSize(wxString file)
{
  long bytesize;
  DWORD hiw, low;
  HANDLE hfile = ::CreateFile(csWX2CHAR(file), STANDARD_RIGHTS_READ, 
                              FILE_SHARE_READ, NULL, OPEN_EXISTING, 
                              FILE_ATTRIBUTE_NORMAL, NULL);
  low = ::GetFileSize(hfile, &hiw);
  bytesize = (hiw << 32) | low;  
  CloseHandle(hfile);  

  return bytesize;
}
#endif


/* Linux version of GetFileSize */
/*
CREATED    {* 2001-04-15 rcl *}
MODIFIED   {* *}
REVIEWED   {* *}
TESTED     {* *}
*/
#ifndef WIN32
long GetFileSize(wxString file)
{
  long bytesize;
  wxFFile ff;

  if(!ff.Open(file))
    return 0;
  bytesize = ff.Length();
  ff.Close();  
  
  return bytesize;
}
#endif


/* For a given directory, return the parent directory */
/*
CREATED    {* 2001-04-15 rcl *}
MODIFIED   {* *}
REVIEWED   {* *}
TESTED     {* *}
*/
wxString GetParentDir(wxString dirpath)
{
  wxString path;
#ifdef WIN32
  path = dirpath.BeforeLast('\\');
#else
  path = dirpath.BeforeLast('/');
  if(path == "")
    path = "/";
#endif
  return path;
}


/* Appends to files together */
/*
CREATED    {* 2001-04-15 rcl *}
MODIFIED   {* *}
REVIEWED   {* *}
TESTED     {* *}
*/
wxString FileCat(wxString file1, wxString file2)
{
#ifdef WIN32
  return file1 + "\\" + file2;
#else
  if(file1 == "/")
    return "/" + file2;
  else
    return file1 + "/" + file2;
#endif
}
 

/* Tells whether a file is hidden */
/*
CREATED    {* 2001-04-15 rcl *}
MODIFIED   {* *}
REVIEWED   {* *}
TESTED     {* *}
*/
BOOL IsHidden(wxString file)
{
#ifdef WIN32
  DWORD a;
  a = ::GetFileAttributes(csWX2CHAR(file));
  return a & FILE_ATTRIBUTE_HIDDEN;

#else

  if(file.GetChar(0) == '.' && file != ".")
    return TRUE;
  else
    return FALSE;
#endif
}


/* Tells whether a file is an archive */
/*
CREATED    {* 2001-04-15 rcl *}
MODIFIED   {* *}
REVIEWED   {* *}
TESTED     {* *}
*/
BOOL IsArchive(wxString file)
{
  wxString name, ext, path;
  wxSplitPath(file, &path, &name, &ext);

#ifdef WIN32  
  if(ext == "zip" || ext == "tgz" || ext == "tar")
    return TRUE;  
#else
  if(ext == "zip" || ext == "tgz" || ext == "tar" || ext == "gz")
    return TRUE;
#endif

  return FALSE;
}


/* Tells whether a file is executable */
/*
CREATED    {* 2001-04-18 rcl *}
MODIFIED   {* *}
REVIEWED   {* *}
TESTED     {* *}
*/
BOOL IsExecutable(wxString file)
{
  wxString name, ext, path;
  
#ifdef WIN32
  return FALSE;
#else
  struct stat file_stat;    
  mode_t mode;

  lstat(csWX2CHAR(file), &file_stat);
  mode = file_stat.st_mode;  
  if ((S_IXUSR & mode) || (S_IXGRP & mode) || (S_IXOTH & mode))
    return TRUE;  

#endif
  return FALSE;
}


/* Tells whether a file is a link */
/*
CREATED    {* 2001-04-18 rcl *}
MODIFIED   {* *}
REVIEWED   {* *}
TESTED     {* *}
*/
BOOL IsLink(wxString file)
{
  wxString name, ext, path;
  
#ifdef WIN32
  return FALSE;
#else
  struct stat file_stat;    
  mode_t mode;

  lstat(csWX2CHAR(file), &file_stat);
  mode = file_stat.st_mode;  
  
  if((mode & S_IFMT) == S_IFLNK)
    return TRUE;  

#endif
  return FALSE;
}

/* Tells whether a file is a link */
/*
CREATED    {* 2001-04-21 rcl *}
MODIFIED   {* *}
REVIEWED   {* *}
TESTED     {* *}
*/
BOOL IsLinkDir(wxString file)
{
  wxString name, ext, path;
  char buffer[STRING_BUFFER_SIZE];
  int length;
  
  /* Split the path */
  wxSplitPath(file, &path, &name, &ext);
  
#ifdef WIN32
  return FALSE;
#else

  length = readlink(csWX2CHAR(file), buffer, STRING_BUFFER_SIZE);
  buffer[length] = '\0';    
  
  if (buffer[0] == '/')
    file = csGui::Format("/%s", buffer);
  else
    file = csGui::Format("%s/%s", csWX2CHAR(path), buffer);
  
  if(::wxDirExists(file))
    return TRUE;
  else 
    return FALSE;

#endif
  return FALSE;
}


/* Tells whether a file is a directory */
/*
CREATED    {* 2001-04-18 rcl *}
MODIFIED   {* *}
REVIEWED   {* *}
TESTED     {* *}
*/
BOOL IsDir(wxString file)
{
  wxString name, ext, path;
  
#ifdef WIN32
  return ::wxDirExists(file);
#else
  struct stat file_stat;    
  mode_t mode;

  lstat(csWX2CHAR(file), &file_stat);
  mode = file_stat.st_mode;  
  
  if((mode & S_IFMT) == S_IFDIR)
    return TRUE;  

#endif
  return FALSE;
}


/* Tells whether a file is a regular file */
/*
CREATED    {* 2001-04-18 rcl *}
MODIFIED   {* *}
REVIEWED   {* *}
TESTED     {* *}
*/
BOOL IsRegular(wxString file)
{
  wxString name, ext, path;
  
#ifdef WIN32
  return TRUE;
#else
  struct stat file_stat;    
  mode_t mode;

  lstat(csWX2CHAR(file), &file_stat);
  mode = file_stat.st_mode;
  
  if((mode & S_IFMT) == S_IFREG)
    return TRUE;  

#endif
  return FALSE;
}



/*****************************************************************************/
/* Format functions                                                          */
/*****************************************************************************/

/* Format a date, and returns the corresponding string */
/*
CREATED    {* 2001-04-15 rcl *}
MODIFIED   {* *}
REVIEWED   {* *}
TESTED     {* *}
*/
wxString FormatDate(wxString file)
{
  wxString fdate;
  wxDateTime date;

  if(!::wxFileExists(file) && !::wxDirExists(file)) {
    return "###";
  }  
  /* Get the date for the file */
  date = wxDateTime(::wxFileModificationTime(file));
  
  fdate = date.Format("%x") + " " + date.Format("%H:%M");
  return fdate;
}


/* Formats the size and returns the corresponding string  */
/*
CREATED    {* 2001-04-15 rcl *}
MODIFIED   {* *}
REVIEWED   {* *}
TESTED     {* *}
*/
wxString FormatSize(long bytesize)
{
  wxString size = "";  
  char  format[256];  
  char *p;
  int i, j;

  /* Format the string */
  sprintf(format, "%ld", bytesize);
  int len = strlen(format);
  char *result = new char[(len-1)/3 + len + 1];
  p = &result[(len-1)/3 + len];  
  *p = '\0';

  for(i = len-1, j = 0; i >= 0; i--, j++) {        
    if(j % 3 == 0 && j != 0)
      *(--p) = ',';    
    *(--p) = format[i];
  }  
  size = wxString(result);
  delete result;  
  return size;
}
