PROJECT( XFC_SOURCEVIEW )

ADD_SUBDIRECTORY( xfc )

CONFIGURE_FILE( xfcsourceview.pc.in xfcsourceview-${XFC_VERSION}.pc @ONLY )

INSTALL( FILES xfcsourceview-${XFC_VERSION}.pc 
	DESTINATION lib/pkgconfig )

