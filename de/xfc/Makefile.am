## libXFCde source directory

SUBDIRS = utils ui

library_includedir=$(includedir)/$(XFCEDIR)/$(XFC_LIBRARY_NAME)

lib_LTLIBRARIES = libXFCde-4.3.la

libXFCde_4_3_la_SOURCES= 
libXFCde_4_3_la_LIBADD= utils/libutils.la ui/libui.la $(XFC_DE_UTIL_LIBS) $(XFC_DE_CONF_LIBS) $(XFC_DE_UI_LIBS)
libXFCde_4_3_la_LDFLAGS= -version-info $(XFC_LIBRARY_VERSION)

# Panel will not work until Xfce 4.8
#if USE_PANEL
#   SUBDIRS += panel
#   libXFCde_4_3_la_LIBADD += panel/libpanel.la $(XFC_DE_PANEL_LIBS) 
#endif

