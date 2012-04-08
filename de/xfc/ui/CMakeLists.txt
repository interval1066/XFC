ADD_SUBDIRECTORY( inline )

INCLUDE_DIRECTORIES(${xfce_core_SOURCE_DIRS} ${XFCE_UI_INCLUDE_DIRS})

SET( ui_src ui/dialogs.cc PARENT_SCOPE)

INSTALL( FILES 
   dialogs.hh
   DESTINATION include/xfce4/xfc/ui)
