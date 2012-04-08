SUBDIRS = inline

AM_CXXFLAGS = @CXXFLAGS@ @XFC_CORE_CFLAGS@ @XFC_DE_UI_CFLAGS@

hh_sources =\
 dialogs.hh

cc_sources =\
 dialogs.cc

library_includedir=$(includedir)/$(XFCEDIR)/$(XFC_LIBRARY_NAME)/ui
library_include_HEADERS = $(hh_sources)

INCLUDES = -I$(top_builddir)/libXFCde -I$(top_builddir)/libXFCcore -I$(top_builddir)/libXFCui

noinst_LTLIBRARIES= libui.la
libui_la_SOURCES= $(hh_sources) $(cc_sources)
