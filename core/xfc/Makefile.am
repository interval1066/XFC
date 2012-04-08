## libXFCcore source directory

SUBDIRS = glib

AM_CXXFLAGS = @CXXFLAGS@ @XFC_CORE_CFLAGS@

EXTRA_DIST = version.hh.in

INCLUDES = -I$(top_builddir)/libXFCcore

hh_sources = \
 convert.hh \
 i18n.hh \
 integerobject.hh \
 object.hh \
 pointer.hh \
 stackobject.hh \
 trackable.hh \
 utfstring.hh \
 version.hh \
 xfccore.hh

cc_sources = \
 convert.cc \
 i18n.cc \
 object.cc \
 stackobject.cc \
 trackable.cc \
 utfstring.cc \
 version.cc
 
library_includedir=$(includedir)/$(XFCEDIR)/$(XFC_LIBRARY_NAME)
library_include_HEADERS = $(hh_sources)

lib_LTLIBRARIES = libXFCcore-4.3.la
libXFCcore_4_3_la_SOURCES= $(hh_sources) $(cc_sources)
libXFCcore_4_3_la_LIBADD= glib/libglib.la $(XFC_CORE_LIBS)
libXFCcore_4_3_la_LDFLAGS= -version-info $(XFC_LIBRARY_VERSION)

