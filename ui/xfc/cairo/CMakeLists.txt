SET( src
 context.cc matrix.cc ps_surface.cc xlib_surface.cc fontoptions.cc 
 pattern.cc surface.cc image_surface.cc pdf_surface.cc svg_surface.cc)

SET(cairo_src "" )
FOREACH(f ${src})
    SET(cairo_src ${cairo_src} "cairo/${f}" )
ENDFOREACH(f)
SET( cairo_src ${cairo_src} PARENT_SCOPE )

INSTALL( FILES
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
 DESTINATION include/xfce4/xfc/cairo)
