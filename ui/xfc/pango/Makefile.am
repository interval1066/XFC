## libXFCui xfc/pango directory

SUBDIRS = inline private

AM_CXXFLAGS = @CXXFLAGS@ @XFC_CORE_CFLAGS@ @XFC_GTK_CFLAGS@ @XFC_PANGO_CFLAGS@

INCLUDES = \
 -I$(top_builddir)/libXFCcore \
 -I$(top_builddir)/libXFCui

hh_sources = \
 attributes.hh \
 break.hh \
 context.hh \
 coverage.hh \
 font.hh \
 fontmap.hh \
 fontset.hh \
 glyph.hh \
 item.hh \
 layout.hh \
 pango.hh \
 renderer.hh \
 script.hh \
 tabs.hh \
 types.hh

cc_sources = \
 attributes.cc \
 break.cc \
 context.cc \
 coverage.cc \
 font.cc \
 fontmap.cc \
 fontset.cc \
 glyph.cc \
 item.cc \
 layout.cc \
 renderer.cc \
 script.cc \
 tabs.cc \
 types.cc

library_includedir=$(includedir)/$(XFCEDIR)/$(XFC_LIBRARY_NAME)/pango
library_include_HEADERS = $(hh_sources)

noinst_LTLIBRARIES= libpango.la
libpango_la_SOURCES= $(hh_sources) $(cc_sources)
