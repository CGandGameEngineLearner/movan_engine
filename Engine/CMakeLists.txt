SUBDIRLIST(SUBDIRS ${CMAKE_CURRENT_SOURCE_DIR})

message(STATUS "${SUBDIRS} ")

FOREACH(subdir ${SUBDIRS})
  ADD_SUBDIRECTORY(${subdir})
  
ENDFOREACH()



add_executable ("Engine.h" "Engine.cpp" )



