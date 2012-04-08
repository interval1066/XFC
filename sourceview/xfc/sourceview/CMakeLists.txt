## gtk-sourceview directory

INSTALL( FILES 
 sourcebuffer.hh 
 sourcebuffersignals.hh 
 sourceiter.hh 
 sourcelanguage.hh 
 sourcelanguagesignals.hh 
 sourceprintjob.hh 
 sourceprintjobsignals.hh 
 sourcestylescheme.hh 
 sourcestyleschemesignals.hh 
 sourcetag.hh 
 sourcetagsignals.hh 
 sourcetagstyle.hh 
 sourceview.hh
 DESTINATION include/xfce4/xfc/sourceview)

SET( src
 sourcebuffer.cc 
 sourcebuffersignals.cc 
 sourceiter.cc 
 sourcelanguage.cc 
 sourcelanguagesignals.cc 
 sourceprintjob.cc 
 sourceprintjobsignals.cc 
 sourcestylescheme.cc 
 sourcestyleschemesignals.cc 
 sourcetag.cc 
 sourcetagsignals.cc 
 sourcetagstyle.cc 
 sourceview.cc)

SET(sourceview_src "" )
FOREACH(f ${src})
    SET(sourceview_src ${sourceview_src} "sourceview/${f}" )
ENDFOREACH(f)
SET( sourceview_src ${sourceview_src} PARENT_SCOPE )

