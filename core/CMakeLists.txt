PROJECT( XFC_CORE )

ADD_SUBDIRECTORY( xfc )

CONFIGURE_FILE( xfccore.pc.in xfccore-${XFC_VERSION}.pc @ONLY )

INSTALL( FILES xfccore-${XFC_VERSION}.pc 
        DESTINATION lib/pkgconfig )

