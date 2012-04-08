## xfc examples/core/threads directory

ADD_EXECUTABLE( complex_thread complex-thread.cc)

TARGET_LINK_LIBRARIES( complex_thread xfc_ui )

ADD_EXECUTABLE( multiple_thread multiple-thread.cc)

TARGET_LINK_LIBRARIES( multiple_thread xfc_ui )

ADD_EXECUTABLE( simple_thread simple-thread.cc)

TARGET_LINK_LIBRARIES( simple_thread  xfc_ui )

ADD_EXECUTABLE( threadpool threadpool.cc )

TARGET_LINK_LIBRARIES( threadpool xfc_ui )
