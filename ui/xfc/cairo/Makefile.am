## libXFCui xfc/cairo directory

#SUBDIRS = inline private

AM_CXXFLAGS = @CXXFLAGS@ @XFC_CORE_CFLAGS@ @XFC_UI_CFLAGS@

INCLUDES = 
 -I$(top_builddir)/libXFCcore 
 -I$(top_builddir)/libXFCui

hh_sources = 
 context.hh 
 matrix.hh 
 ps_surface.hh 
 types.hh 
 fontoptions.hh  
 pattern.hh  
 surface.hh  
 xlib_surface.hh 
 image_surface.hh 
 pdf_surface.hh 
 svg_surface.hh

cc_sources = 
 context.cc 
 matrix.cc 
 ps_surface.cc 
 xlib_surface.cc 
 fontoptions.cc 
 pattern.cc 
 surface.cc 
 image_surface.cc 
 pdf_surface.cc 
 svg_surface.cc

library_includedir=$(includedir)/$(XFCEDIR)/$(XFC_LIBRARY_NAME)/cairo
library_include_HEADERS = $(hh_sources)

noinst_LTLIBRARIES= libcairo.la
libcairo_la_SOURCES= $(hh_sources) $(cc_sources)
