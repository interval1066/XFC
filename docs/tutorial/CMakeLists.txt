## xfc docs/tutorial directory

ADD_SUBDIRECTORY( html )

FOREACH(f ${html})
    SET(files ${files} "html/${f}" )
ENDFOREACH(f)

INSTALL( FILES 
    ${files}
    DESTINATION ${docs_dest}/tutorial/html)
