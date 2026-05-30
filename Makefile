# *---------------------------------------------------------------------------*
# | Copyright (C) 2000 ConfigIt! (www.configit.dk)
# |
# | This software is the property of ConfigIt!, and may not be copied and/ or 
# | modified as a whole or in parts without explicit authorization from
# | ConfigIt!
# | 
# | File           : $Id: Makefile,v 1.2 2001/03/16 18:12:41 rcl Exp $
# | Written by     : rcl                    Date: april 2001
# | Reviewed by    :                        Date: 
# | Description    : Makefile for wxCommander
# *---------------------------------------------------------------------------*

CFG_WARNINGS	= n
-include	../../Makefile.defines

CC = g++

TARGET_SRC	= main.cpp mainframe.cpp lowerpanel.cpp fileview.cpp \
							filelist.cpp drivebuttonpanel.cpp appmanager.cpp functions.cpp
TARGET_NAME	= wxCommander

INCLUDE		= -I$(CONFIGIT_ROOT)/include -I/usr/local/lib/wx/include \
						 -I/usr/X11R6/include -I/usr/lib/glib/include
LIB_DIR		= -L$(CONFIGIT_ROOT)/lib
CFLAGS		+= -DGTK_NO_CHECK_CASTS -D__WXGTK__ `wx-config --cflags` \
             -DUSE_XPM_BITMAPS

CONFIGIT_LIBS	= -lconfigit_base -lconfigit_gui
SYSTEM_LIBS	= -lstdc++ -lodbc -ldl -lm -lz `wx-config --libs`

TARGET_BIN	= $(TARGET_NAME)
EXPORT_BIN	= n

-include	../../Makefile.targets

