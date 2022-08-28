project ("Engine")


FOREACH(subdir ${SUBDIRS})
  ADD_SUBDIRECTORY(${subdir})
  
ENDFOREACH()


file(GLOB_RECURSE HEADER_FILES "*.h")
file(GLOB_RECURSE SOURCE_FILES "*.cpp")
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${HEADER_FILES} ${SOURCE_FILES})




add_executable (Engine "Engine.h" "Engine.cpp" ${HEADER_FILES} ${SOURCE_FILES}  "Source/Runtime/Core/Meta/json.h")


