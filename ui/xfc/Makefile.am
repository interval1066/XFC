## libXFCui source directory

SUBDIRS = atk gdk gdk-pixbuf gtk pango cairo

AM_CXXFLAGS = @CXXFLAGS@ @XFC_CORE_CFLAGS@ @XFC_UI_CFLAGS@

EXTRA_DIST = config.h.in

INCLUDES = \
 -I$(top_builddir)/libXFCcore \
 -I$(top_builddir)/libXFCui

hh_sources = \
 main.hh \
 ui.hh \
 xfcui.hh \
 config.h

cc_sources = \
 main.cc 

library_includedir=$(includedir)/$(XFCEDIR)/$(XFC_LIBRARY_NAME)
library_include_HEADERS = $(hh_sources)

lib_LTLIBRARIES= libXFCui-4.3.la
libXFCui_4_3_la_SOURCES= $(hh_sources) $(cc_sources)
libXFCui_4_3_la_LIBADD= atk/libatk.la gdk/libgdk.la gdk-pixbuf/libgdk_pixbuf.la gtk/libgtk.la pango/libpango.la cairo/libcairo.la $(XFC_UI_LIBS) $(XFC_SIGC_LIBS)
libXFCui_4_3_la_LDFLAGS= -version-info $(XFC_LIBRARY_VERSION)
