## xfc examples/howto/menu directory

ADD_EXECUTABLE( menu menu.cc )

TARGET_LINK_LIBRARIES( menu xfc_ui )

ADD_EXECUTABLE( stock stock.cc )

TARGET_LINK_LIBRARIES( stock xfc_ui )
