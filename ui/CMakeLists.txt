PROJECT( XFC_UI )

ADD_SUBDIRECTORY( xfc )

CONFIGURE_FILE( xfcui.pc.in xfcui-${XFC_VERSION}.pc @ONLY )

INSTALL( FILES xfcui-${XFC_VERSION}.pc 
	DESTINATION lib/pkgconfig )
