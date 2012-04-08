INCLUDE_DIRECTORIES( ${XFC_UI_SOURCE_DIR} ${XFC_CORE_SOURCE_DIR}
    ${GLIB_INCLUDE_DIRS} ${SIGC_INCLUDE_DIRS} ${GDK_INCLUDE_DIRS}
    ${GTK_INCLUDE_DIRS} ${XFC_SOURCE_DIR})

ADD_DEFINITIONS( -DDEMOCODEDIR="${XFC_DEMOS_SOURCE_DIR}/xfc-demo" )

SET( demos 
 appwindow.cc 
 button_box.cc 
 changedisplay.cc 
 clipboard.cc 
 colorsel.cc 
 dialog.cc 
 drawingarea.cc 
 entry_completion.cc 
 expander.cc 
 hypertext.cc 
 iconview.cc 
 images.cc 
 menus.cc 
 panes.cc 
 pixbufs.cc 
 rotated_text.cc 
 sizegroup.cc 
 stock_browser.cc 
 textview.cc 
 editable_cells.cc 
 list_store.cc 
 tree_store.cc 
 ui_manager.cc)

ADD_EXECUTABLE( xfc-demo main.cc demowindow.cc ${demos} )

TARGET_LINK_LIBRARIES( xfc-demo xfc_ui )

SET( images alphatest.png apple-red.png background.jpg floppybuddy.gif gnome-applets.png
 gnome-calendar.png gnome-fs-directory.png gnome-foot.png gnome-gimp.png gnome-gmush.png gnome-gsame.png
 gnome-fs-regular.png gnu-keys.png gtk-logo-rgb.gif)

INSTALL( FILES ${demos} ${images}
    DESTINATION share/xfce4/xfc/demos)

INSTALL( TARGETS xfc-demo 
    RUNTIME DESTINATION bin 
    LIBRARY DESTINATION lib)
