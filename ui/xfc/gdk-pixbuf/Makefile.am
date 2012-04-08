## libXFCui xfc/gdk-pixbuf directory

SUBDIRS = inline private

AM_CXXFLAGS = @CXXFLAGS@  @XFC_CORE_CFLAGS@ @XFC_GTK_CFLAGS@

INCLUDES = \
 -I$(top_builddir)/libXFCcore \
 -I$(top_builddir)/libXFCui

hh_sources = \
 gdk-pixbuf.hh \
 pixbuf.hh \
 pixbuf-io.hh \
 pixbuf-animation.hh \
 pixbuf-loader.hh \
 pixbuf-loadersignals.hh

cc_sources = \
 pixbuf.cc \
 pixbuf-io.cc \
 pixbuf-animation.cc \
 pixbuf-loader.cc \
 pixbuf-loadersignals.cc

library_includedir=$(includedir)/$(XFCEDIR)/$(XFC_LIBRARY_NAME)/gdk-pixbuf
library_include_HEADERS = $(hh_sources)

noinst_LTLIBRARIES= libgdk_pixbuf.la
libgdk_pixbuf_la_SOURCES= $(hh_sources) $(cc_sources) 
