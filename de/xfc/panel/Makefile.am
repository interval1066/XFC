SUBDIRS = inline

AM_CXXFLAGS = @CXXFLAGS@ @XFC_CORE_CFLAGS@ @XFC_DE_PANEL_CFLAGS@

hh_sources =\
 panel.hh

cc_sources =\
 panel.cc

library_includedir=$(includedir)/$(XFCEDIR)/$(XFC_LIBRARY_NAME)/panel
library_include_HEADERS = $(hh_sources)

INCLUDES = -I$(top_builddir)/libXFCde -I$(top_builddir)/libXFCcore 

noinst_LTLIBRARIES= libpanel.la
libpanel_la_SOURCES= $(hh_sources) $(cc_sources)
