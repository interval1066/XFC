## libXFCglade source directory

SUBDIRS = glade

AM_CXXFLAGS = @CXXFLAGS@ @XFC_CORE_CFLAGS@ @XFC_GLADE_CFLAGS@

INCLUDES = \
 -I$(top_builddir)/libXFCcore \
 -I$(top_builddir)/libXFCglade \
 -I$(top_builddir)/libXFCui

hh_sources = \
 xfcglade.hh

library_includedir=$(includedir)/$(XFCEDIR)/$(XFC_LIBRARY_NAME)
library_include_HEADERS = $(hh_sources)

lib_LTLIBRARIES = libXFCglade-4.3.la
libXFCglade_4_3_la_SOURCES= $(hh_sources)
libXFCglade_4_3_la_LIBADD= glade/libglade.la $(XFC_GLADE_LIBS)
libXFCglade_4_3_la_LDFLAGS= -version-info $(XFC_LIBRARY_VERSION)
