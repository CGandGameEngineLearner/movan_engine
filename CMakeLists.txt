cmake_minimum_required(VERSION 3.25.1 FATAL_ERROR)

project(MovanEngine VERSION 0.1.0)

set(MOVAN_MAIN_CXX_STANDARD 20)

set(CMAKE_CXX_STANDARD ${MOVAN_MAIN_CXX_STANDARD})
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(BUILD_SHARED_LIBS OFF)

include(CMakeDependentOption)

# ---- Include guards ----
if(PROJECT_SOURCE_DIR STREQUAL PROJECT_BINARY_DIR)
  message(
    FATAL_ERROR
      "In-source builds not allowed. Please make a new directory (called a build directory) and run CMake from there."
  )
endif()

set(MOVAN_ENGINE_ROOT_DIR "${CMAKE_CURRENT_SOURCE_DIR}")
set(CMAKE_INSTALL_PREFIX "${MOVAN_ENGINE_ROOT_DIR}/bin")
set(BINARY_ROOT_DIR "${CMAKE_INSTALL_PREFIX}/")


add_subdirectory(engine)