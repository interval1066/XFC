## gtk-sourceview directory

SUBDIRS = private

AM_CXXFLAGS = @CXXFLAGS@ @XFC_CORE_CFLAGS@ @XFC_UI_CFLAGS@ @XFC_SOURCEVIEW_CFLAGS@

hh_sources =\
 sourcebuffer.hh \
 sourcebuffersignals.hh \
 sourceiter.hh \
 sourcelanguage.hh \
 sourcelanguagesignals.hh \
 sourceprintjob.hh \
 sourceprintjobsignals.hh \
 sourcestylescheme.hh \
 sourcestyleschemesignals.hh \
 sourcetag.hh \
 sourcetagsignals.hh \
 sourcetagstyle.hh \
 sourceview.hh

cc_sources =\
 sourcebuffer.cc \
 sourcebuffersignals.cc \
 sourceiter.cc \
 sourcelanguage.cc \
 sourcelanguagesignals.cc \
 sourceprintjob.cc \
 sourceprintjobsignals.cc \
 sourcestylescheme.cc \
 sourcestyleschemesignals.cc \
 sourcetag.cc \
 sourcetagsignals.cc \
 sourcetagstyle.cc \
 sourceview.cc

library_includedir=$(includedir)/$(XFCEDIR)/$(XFC_LIBRARY_NAME)/sourceview
library_include_HEADERS = $(hh_sources)

INCLUDES = -I$(top_builddir)/libXFCsourceview \
     -I$(top_builddir)/libXFCcore \
     -I$(top_builddir)/libXFCui

noinst_LTLIBRARIES= libsourceview.la
libsourceview_la_SOURCES= $(hh_sources) $(cc_sources)
