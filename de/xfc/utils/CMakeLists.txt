
SET( utils_src utils/config.cc PARENT_SCOPE )

INSTALL( FILES config.hh 
     DESTINATION include/xfce4/xfc/utils )
INSTALL( FILES inline/config.inl 
     DESTINATION include/xfce4/xfc/utils/inline )
