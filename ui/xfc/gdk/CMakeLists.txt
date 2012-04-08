ADD_SUBDIRECTORY( inline )

SET( src 
 bitmap.cc color.cc cursor.cc display.cc displaysignals.cc displaymanager.cc 
 displaymanagersignals.cc dnd.cc drawable.cc events.cc gc.cc image.cc input.cc 
 keymap.cc keymapsignals.cc keyval.cc marshal.cc pangorenderer.cc pixmap.cc 
 region.cc screen.cc screensignals.cc spawn.cc types.cc visual.cc window.cc )

SET(gdk_src "" )
FOREACH(f ${src})
    SET(gdk_src ${gdk_src} "gdk/${f}" )
ENDFOREACH(f)
SET( gdk_src ${gdk_src} PARENT_SCOPE )

INSTALL( FILES
 bitmap.hh 
 color.hh 
 cursor.hh 
 display.hh 
 displaysignals.hh 
 displaymanager.hh 
 displaymanagersignals.hh 
 dnd.hh 
 drawable.hh 
 events.hh 
 gc.hh 
 gdk.hh 
 image.hh 
 input.hh 
 keymap.hh 
 keymapsignals.hh 
 keyval.hh 
 pangorenderer.hh 
 pixmap.hh 
 region.hh 
 screen.hh 
 screensignals.hh 
 spawn.hh 
 types.hh 
 visual.hh 
 window.hh
 DESTINATION include/xfce4/xfc/gdk)
