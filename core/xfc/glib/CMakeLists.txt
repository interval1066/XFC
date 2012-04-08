## libXFCcore xfc/glib directory

ADD_SUBDIRECTORY( inline )

SET( src
 asyncqueue.cc 
 boxed.cc 
 completion.cc 
 connection.cc 
 date.cc 
 error.cc 
 fileutils.cc 
 iochannel.cc 
 keyfile.cc 
 main.cc 
 markup.cc 
 marshal.cc 
 module.cc 
 mutex.cc 
 object.cc 
 objectsignals.cc 
 option.cc 
 pattern.cc 
 property.cc 
 quark.cc 
 rand.cc 
 scanner.cc 
 shell.cc 
 signals.cc 
 spawn.cc 
 thread.cc 
 threadpool.cc 
 timer.cc 
 timeval.cc 
 type.cc 
 unicode.cc 
 utils.cc 
 value.cc)

SET(glib_src "" )
FOREACH(f ${src})
    SET(glib_src ${glib_src} "glib/${f}" )
ENDFOREACH(f)
SET( glib_src ${glib_src} PARENT_SCOPE )

INSTALL( FILES
 asyncqueue.hh 
 boxed.hh 
 completion.hh 
 date.hh 
 error.hh 
 fileutils.hh 
 g.hh 
 iochannel.hh 
 keyfile.hh 
 main.hh 
 markup.hh 
 module.hh 
 mutex.hh 
 object.hh 
 objectsignals.hh 
 option.hh 
 pattern.hh 
 property.hh 
 quark.hh 
 rand.hh 
 scanner.hh 
 shell.hh 
 signals.hh 
 slist.hh 
 spawn.hh 
 thread.hh 
 threadpool.hh 
 timer.hh 
 timeval.hh 
 type.hh 
 unicode.hh 
 utils.hh 
 value.hh
 DESTINATION include/xfce4/xfc/glib)
