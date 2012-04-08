## xfc examples/howto/drawingarea directory

ADD_EXECUTABLE( scribble scribble.cc )

TARGET_LINK_LIBRARIES( scribble xfc_ui )
 
ADD_EXECUTABLE( simple simple.cc )

TARGET_LINK_LIBRARIES( simple xfc_ui )
