SUBDIRS = inline

AM_CXXFLAGS = @CXXFLAGS@ @XFC_CORE_CFLAGS@ @XFC_DE_CONF_CFLAGS@ @XFC_DE_UTIL_CFLAGS@

hh_sources =\
 config.hh

cc_sources =\
 config.cc

library_includedir=$(includedir)/$(XFCEDIR)/$(XFC_LIBRARY_NAME)/utils
library_include_HEADERS = $(hh_sources)

INCLUDES = -I$(top_builddir)/libXFCde -I$(top_builddir)/libXFCcore 

noinst_LTLIBRARIES= libutils.la
libutils_la_SOURCES= $(hh_sources) $(cc_sources)

