INCLUDE( FindDoxygen )

CONFIGURE_FILE( Doxyfile.in Doxyfile )
CONFIGURE_FILE( xfc_footer.html.in xfc_footer.html )

ADD_CUSTOM_TARGET(api-docs ALL ${DOXYGEN_EXECUTABLE} Doxyfile) 

INSTALL( DIRECTORY html DESTINATION ${docs_dest}/reference/html
         PATTERN ".svn" EXCLUDE )

INSTALL( FILES 
    doxygen.css 
    xfc_footer.html
    xfc_header.html
    DESTINATION ${docs_dest}/reference/html)
