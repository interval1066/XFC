## libXFCui xfc/atk directory

SUBDIRS = inline private

AM_CXXFLAGS = @CXXFLAGS@ @XFC_CORE_CFLAGS@ @XFC_ATK_CFLAGS@

INCLUDES = 
 -I$(top_builddir)/libXFCcore 
 -I$(top_builddir)/libXFCui

hh_sources = 
 action.hh 
 atk.hh 
 component.hh 
 document.hh 
 editabletext.hh 
 gobjectaccessible.hh 
 hyperlink.hh 
 hyperlinksignals.hh 
 hypertext.hh 
 hypertextsignals.hh 
 image.hh 
 implementor.hh 
 object.hh 
 objectsignals.hh 
 objectfactory.hh 
 registry.hh 
 relation.hh 
 selection.hh 
 selectionsignals.hh 
 stateset.hh 
 streamablecontent.hh 
 table.hh 
 tablesignals.hh 
 text.hh 
 textsignals.hh 
 util.hh 
 value.hh

cc_sources = 
 action.cc 
 component.cc 
 document.cc 
 editabletext.cc 
 gobjectaccessible.cc 
 hyperlink.cc 
 hyperlinksignals.cc 
 hypertext.cc 
 hypertextsignals.cc 
 image.cc 
 implementor.cc 
 marshal.cc 
 object.cc 
 objectsignals.cc 
 objectfactory.cc 
 registry.cc 
 relation.cc 
 selection.cc 
 selectionsignals.cc 
 stateset.cc 
 streamablecontent.cc 
 table.cc 
 tablesignals.cc 
 text.cc 
 textsignals.cc 
 util.cc 
 value.cc

library_includedir=$(includedir)/$(XFCEDIR)/$(XFC_LIBRARY_NAME)/atk
library_include_HEADERS = $(hh_sources)

noinst_LTLIBRARIES= libatk.la
libatk_la_SOURCES= $(hh_sources) $(cc_sources)
