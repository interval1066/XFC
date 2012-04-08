democodedir = $(datadir)/$(XFCEDIR)/xfc/demos

AM_CXXFLAGS = @CXXFLAGS@ @XFC_UI_CFLAGS@

demos = \
 appwindow.cc \
 button_box.cc \
 changedisplay.cc \
 clipboard.cc \
 colorsel.cc \
 dialog.cc \
 drawingarea.cc \
 entry_completion.cc \
 expander.cc \
 hypertext.cc \
 iconview.cc \
 images.cc \
 menus.cc \
 panes.cc \
 pixbufs.cc \
 rotated_text.cc \
 sizegroup.cc \
 stock_browser.cc \
 textview.cc \
 editable_cells.cc \
 list_store.cc \
 tree_store.cc \
 ui_manager.cc

bin_PROGRAMS = xfc-demo

xfc_demo_SOURCES = \
 $(demos) \
 demos.hh \
 demowindow.hh \
 demowindow.cc \
 main.cc

INCLUDES = \
 -DDEMOCODEDIR="\"$(democodedir)\"" \
 -I$(top_builddir)/libXFCcore \
 -I$(top_builddir)/libXFCui 

LIBS = \
 $(top_builddir)/libXFCcore/xfc/libXFCcore-$(XFC_API_VERSION).la \
 $(top_builddir)/libXFCui/xfc/libXFCui-$(XFC_API_VERSION).la \
 $(XFC_SIGC_LIBS)

IMAGEFILES = \
 alphatest.png \
 apple-red.png \
 background.jpg \
 floppybuddy.gif \
 gnome-applets.png \
 gnome-calendar.png \
 gnome-fs-directory.png \
 gnome-foot.png \
 gnome-gimp.png \
 gnome-gmush.png \
 gnome-gsame.png \
 gnome-fs-regular.png \
 gnu-keys.png \
 gtk-logo-rgb.gif

democode_DATA = $(demos) $(IMAGEFILES)

EXTRA_DIST = $(democode_DATA)
