## libXFCui xfc/gdk directory

SUBDIRS = inline private

AM_CXXFLAGS = @CXXFLAGS@  @XFC_CORE_CFLAGS@ @XFC_GTK_CFLAGS@

INCLUDES = 
 -I$(top_builddir)/libXFCcore 
 -I$(top_builddir)/libXFCui

hh_sources = 
 bitmap.hh 
 color.hh 
 cursor.hh 
 display.hh 
 displaysignals.hh 
 displaymanager.hh 
 displaymanagersignals.hh 
 dnd.hh 
 drawable.hh 
 events.hh 
 gc.hh 
 gdk.hh 
 image.hh 
 input.hh 
 keymap.hh 
 keymapsignals.hh 
 keyval.hh 
 pangorenderer.hh 
 pixmap.hh 
 region.hh 
 screen.hh 
 screensignals.hh 
 spawn.hh 
 types.hh 
 visual.hh 
 window.hh

cc_sources = 
 bitmap.cc 
 color.cc 
 cursor.cc 
 display.cc 
 displaysignals.cc 
 displaymanager.cc 
 displaymanagersignals.cc 
 dnd.cc 
 drawable.cc 
 events.cc 
 gc.cc 
 image.cc 
 input.cc 
 keymap.cc 
 keymapsignals.cc 
 keyval.cc 
 marshal.cc 
 pangorenderer.cc 
 pixmap.cc 
 region.cc 
 screen.cc 
 screensignals.cc 
 spawn.cc 
 types.cc 
 visual.cc 
 window.cc

library_includedir=$(includedir)/$(XFCEDIR)/$(XFC_LIBRARY_NAME)/gdk
library_include_HEADERS = $(hh_sources)

noinst_LTLIBRARIES= libgdk.la
libgdk_la_SOURCES= $(hh_sources) $(cc_sources)
