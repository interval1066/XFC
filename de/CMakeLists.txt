PROJECT( XFC_DE )

ADD_SUBDIRECTORY( xfc )

CONFIGURE_FILE( xfcde.pc.in xfcde-${XFC_VERSION}.pc @ONLY )

INSTALL( FILES xfcde-${XFC_VERSION}.pc 
	DESTINATION lib/pkgconfig )
