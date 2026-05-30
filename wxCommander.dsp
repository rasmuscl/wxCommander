# Microsoft Developer Studio Project File - Name="wxCommander" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=wxCommander - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "wxCommander.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "wxCommander.mak" CFG="wxCommander - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "wxCommander - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "wxCommander - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "wxCommander - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "wxCommander - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "wxCommander___Win32_Debug"
# PROP BASE Intermediate_Dir "wxCommander___Win32_Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /I "c:\usr\local\configit\include\\" /I "c:\usr\local\wx2\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "__WINDOWS__" /D "__WXMSW__" /D DEBUG=1 /D "__WIN95__" /D "__WIN32__" /D WINVER=0x0400 /D "STRICT" /D WXUSINGDLL=1 /Yu"wx/wxprec.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 configit_based.lib wx22_6d.lib configit_guid.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /out:"c:\usr\local\bin\wxCommander.exe" /pdbtype:sept /libpath:"c:\usr\local\configit\lib" /libpath:"c:\usr\local\wx2\lib"

!ENDIF 

# Begin Target

# Name "wxCommander - Win32 Release"
# Name "wxCommander - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\appmanager.cpp
# End Source File
# Begin Source File

SOURCE=.\drivebuttonpanel.cpp
# End Source File
# Begin Source File

SOURCE=.\filelist.cpp
# End Source File
# Begin Source File

SOURCE=.\fileview.cpp
# End Source File
# Begin Source File

SOURCE=.\lowerpanel.cpp
# End Source File
# Begin Source File

SOURCE=.\main.cpp
# End Source File
# Begin Source File

SOURCE=.\mainframe.cpp
# End Source File
# Begin Source File

SOURCE=.\misc.cpp
# End Source File
# Begin Source File

SOURCE=.\wxCommander.rc
# End Source File
# Begin Source File

SOURCE=.\wxprec.cpp

!IF  "$(CFG)" == "wxCommander - Win32 Release"

!ELSEIF  "$(CFG)" == "wxCommander - Win32 Debug"

# ADD CPP /Yc"wx/wxprec.h"

!ENDIF 

# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\appmanager.h
# End Source File
# Begin Source File

SOURCE=.\drivebuttonpanel.h
# End Source File
# Begin Source File

SOURCE=.\filelist.h
# End Source File
# Begin Source File

SOURCE=.\fileview.h
# End Source File
# Begin Source File

SOURCE=.\global.h
# End Source File
# Begin Source File

SOURCE=.\lowerpanel.h
# End Source File
# Begin Source File

SOURCE=.\main.h
# End Source File
# Begin Source File

SOURCE=.\mainframe.h
# End Source File
# Begin Source File

SOURCE=.\misc.h
# End Source File
# Begin Source File

SOURCE=.\resource.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\bitmaps\app_icon.ico
# End Source File
# Begin Source File

SOURCE=.\bitmaps\app_icon_large.ico
# End Source File
# Begin Source File

SOURCE=.\bitmaps\fv_archive_icon.ico
# End Source File
# Begin Source File

SOURCE=.\bitmaps\fv_exe_icon.ico
# End Source File
# Begin Source File

SOURCE=.\bitmaps\fv_folder_icon.ico
# End Source File
# Begin Source File

SOURCE=.\bitmaps\fv_hidden_icon.ico
# End Source File
# Begin Source File

SOURCE=.\bitmaps\fv_unknown_icon.ico
# End Source File
# Begin Source File

SOURCE=.\bitmaps\fv_up_icon.ico
# End Source File
# Begin Source File

SOURCE=.\bitmaps\tb_back_icon.ico
# End Source File
# Begin Source File

SOURCE=.\bitmaps\tb_brief_icon.ico
# End Source File
# Begin Source File

SOURCE=.\bitmaps\tb_cd_tree_icon.ico
# End Source File
# Begin Source File

SOURCE=.\bitmaps\tb_cdrom_icon.ico
# End Source File
# Begin Source File

SOURCE=.\bitmaps\tb_drive_icon.ico
# End Source File
# Begin Source File

SOURCE=.\bitmaps\tb_floppy_icon.ico
# End Source File
# Begin Source File

SOURCE=.\bitmaps\tb_forward_icon.ico
# End Source File
# Begin Source File

SOURCE=.\bitmaps\tb_ftp_connect_icon.ico
# End Source File
# Begin Source File

SOURCE=.\bitmaps\tb_ftp_new_connection_icon.ico
# End Source File
# Begin Source File

SOURCE=.\bitmaps\tb_full_icon.ico
# End Source File
# Begin Source File

SOURCE=.\bitmaps\tb_invert_icon.ico
# End Source File
# Begin Source File

SOURCE=.\bitmaps\tb_network_icon.ico
# End Source File
# Begin Source File

SOURCE=.\bitmaps\tb_reread_icon.ico
# End Source File
# Begin Source File

SOURCE=.\bitmaps\tb_tree_icon.ico
# End Source File
# End Group
# End Target
# End Project
