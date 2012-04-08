## libXFCsourceview source directory

SUBDIRS = sourceview

library_includedir=$(includedir)/$(XFCEDIR)/$(XFC_LIBRARY_NAME)

lib_LTLIBRARIES = libXFCsourceview-4.3.la
libXFCsourceview_4_3_la_SOURCES= 
libXFCsourceview_4_3_la_LIBADD= sourceview/libsourceview.la $(XFC_SOURCEVIEW_LIBS)
libXFCsourceview_4_3_la_LDFLAGS= -version-info $(XFC_LIBRARY_VERSION)
