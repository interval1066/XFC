PROJECT( XFC_GLADE )

ADD_SUBDIRECTORY( xfc )

CONFIGURE_FILE( xfcglade.pc.in xfcglade-${XFC_VERSION}.pc @ONLY )

INSTALL( FILES xfcglade-${XFC_VERSION}.pc 
	DESTINATION lib/pkgconfig )

