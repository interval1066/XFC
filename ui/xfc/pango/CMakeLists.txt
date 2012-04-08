ADD_SUBDIRECTORY( inline )

SET( src
 attributes.cc 
 break.cc
 context.cc 
 coverage.cc 
 font.cc 
 fontmap.cc 
 fontset.cc 
 glyph.cc 
 item.cc 
 layout.cc 
 renderer.cc 
 script.cc 
 tabs.cc 
 types.cc)

SET( pango_src "" )
FOREACH(f ${src})
    SET(pango_src ${pango_src} "pango/${f}" )
ENDFOREACH(f)
SET( pango_src ${pango_src} PARENT_SCOPE )

INSTALL( FILES
 attributes.hh 
 break.hh 
 context.hh 
 coverage.hh 
 font.hh 
 fontmap.hh 
 fontset.hh 
 glyph.hh 
 item.hh 
 layout.hh 
 pango.hh 
 renderer.hh 
 script.hh 
 tabs.hh 
 types.hh
 DESTINATION include/xfce4/xfc/pango)
