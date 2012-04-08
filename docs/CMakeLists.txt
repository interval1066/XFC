## xfc docs directory

ADD_SUBDIRECTORY( faq )
ADD_SUBDIRECTORY( howto ) 
ADD_SUBDIRECTORY( images )
ADD_SUBDIRECTORY( tutorial )
ADD_SUBDIRECTORY( reference )

SET( docs_dest share/doc/xfc-${XFC_VERSION}/docs)

CONFIGURE_FILE( index.html.in index.html @ONLY)

INSTALL( FILES
   index.html README 
   DESTINATION ${docs_dest})
