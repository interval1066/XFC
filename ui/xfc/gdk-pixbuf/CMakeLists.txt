ADD_SUBDIRECTORY( inline )

SET( src
 pixbuf.cc pixbuf-io.cc 
 pixbuf-animation.cc 
 pixbuf-loader.cc 
 pixbuf-loadersignals.cc )

SET(gdk_pixbuf_src "" )
FOREACH(f ${src})
    SET(gdk_pixbuf_src ${gdk_pixbuf_src} "gdk-pixbuf/${f}" )
ENDFOREACH(f)
SET( gdk_pixbuf_src ${gdk_pixbuf_src} PARENT_SCOPE )

INSTALL( FILES
 gdk-pixbuf.hh 
 pixbuf.hh 
 pixbuf-io.hh 
 pixbuf-animation.hh 
 pixbuf-loader.hh 
 pixbuf-loadersignals.hh
 DESTINATION include/xfce4/xfc/gdk-pixbuf )
