## libXFCglade xfc/glade directory

SUBDIRS = inline private

AM_CXXFLAGS = @CXXFLAGS@ @XFC_CORE_CFLAGS@ @XFC_GLADE_CFLAGS@

INCLUDES = \
 -I$(top_builddir)/libXFCcore \
 -I$(top_builddir)/libXFCglade \
 -I$(top_builddir)/libXFCui

hh_sources = \
 glade.hh \
 xml.hh
 
cc_sources = \
 xml.cc
 
library_includedir=$(includedir)/$(XFCEDIR)/$(XFC_LIBRARY_NAME)/glade
library_include_HEADERS = $(hh_sources)

noinst_LTLIBRARIES= libglade.la
libglade_la_SOURCES= $(hh_sources) $(cc_sources)
