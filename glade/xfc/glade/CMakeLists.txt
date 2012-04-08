## libXFCglade xfc/glade directory

ADD_SUBDIRECTORY( inline )

SET( glade_src glade/xml.cc PARENT_SCOPE)

INSTALL( FILES
 glade.hh 
 xml.hh
 DESTINATION include/xfce4/xfc/glade )
