# CMakeList.txt: MovanStudio 的 CMake 项目，在此处包括源代码并定义
# 项目特定的逻辑。
#
cmake_minimum_required (VERSION 3.8)

project ("MovanStudio")

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

#https://oomake.com/question/2034387
MACRO(SUBDIRLIST result curdir)
  FILE(GLOB children RELATIVE ${curdir} ${curdir}/*)
  SET(dirlist "")
  FOREACH(child ${children})
    IF(IS_DIRECTORY ${curdir}/${child})
      LIST(APPEND dirlist ${child})
    ENDIF()
  ENDFOREACH()
  SET(${result} ${dirlist})
ENDMACRO()


file(GLOB_RECURSE HEADER_FILES "*.h")
file(GLOB_RECURSE SOURCE_FILES "*.cpp")
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${HEADER_FILES} ${SOURCE_FILES})


# 将源代码添加到此项目的可执行文件。
add_executable (MovanStudio "MovanStudio.cpp" "MovanStudio.h")

# TODO: 如有需要，请添加测试并安装目标。

add_subdirectory("Engine" )
set_property(TARGET "Engine" PROPERTY FOLDER MovanStudio)