ADD_SUBDIRECTORY( inline )

SET( src
 action.cc
 component.cc
 document.cc
 editabletext.cc
 gobjectaccessible.cc 
 hyperlink.cc
 hyperlinksignals.cc
 hypertext.cc
 hypertextsignals.cc
 image.cc 
 implementor.cc
 marshal.cc
 object.cc
 objectsignals.cc
 objectfactory.cc 
 registry.cc
 relation.cc
 selection.cc
 selectionsignals.cc
 stateset.cc 
 streamablecontent.cc
 table.cc
 tablesignals.cc
 text.cc
 textsignals.cc 
 util.cc
 value.cc)

SET(atk_src "" )
FOREACH(f ${src})
    SET(atk_src ${atk_src} "atk/${f}" )
ENDFOREACH(f)
SET( atk_src ${atk_src} PARENT_SCOPE )

INSTALL( FILES
 action.hh 
 atk.hh 
 component.hh 
 document.hh 
 editabletext.hh 
 gobjectaccessible.hh 
 hyperlink.hh 
 hyperlinksignals.hh 
 hypertext.hh 
 hypertextsignals.hh 
 image.hh 
 implementor.hh 
 object.hh 
 objectsignals.hh 
 objectfactory.hh 
 registry.hh 
 relation.hh 
 selection.hh 
 selectionsignals.hh 
 stateset.hh 
 streamablecontent.hh 
 table.hh 
 tablesignals.hh 
 text.hh 
 textsignals.hh 
 util.hh 
 value.hh
 DESTINATION include/xfce4/xfc/atk)
