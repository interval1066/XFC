## xfc docs/howto directory

ADD_SUBDIRECTORY( html )

FOREACH(f ${html_files})
    SET(files ${files} "html/${f}" )
ENDFOREACH(f)

INSTALL( FILES ${files}
   DESTINATION ${docs_dest}/docs/howto/html)
