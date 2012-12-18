# ------------------------------------------
# Nifty: IO and manipulation of nifti images
# ------------------------------------------
project(Nifti)

# CMake min
cmake_minimum_required(VERSION 2.8.2)

# Include dirs
set(${PROJECT_NAME}_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}")
include_directories("${${PROJECT_NAME}_INCLUDE_DIRS}")

# Build library
set(${PROJECT_NAME}_SRCS nifti1_io.c znzlib.c)
# static
set(${PROJECT_NAME}_STATIC ${PROJECT_NAME}Static)
add_library(${${PROJECT_NAME}_STATIC} STATIC ${${PROJECT_NAME}_SRCS})
# shared
set(${PROJECT_NAME}_SHARED ${PROJECT_NAME}Shared)
add_library(${${PROJECT_NAME}_SHARED} SHARED ${${PROJECT_NAME}_SRCS})
# create in the main outputs dirs
set_target_properties(${${PROJECT_NAME}_SHARED} PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY "${SEMIT_RUNTIME_OUTPUT_DIRECTORY}"
  LIBRARY_OUTPUT_DIRECTORY "${SEMIT_LIBRARY_OUTPUT_DIRECTORY}"
  ARCHIVE_OUTPUT_DIRECTORY "${SEMIT_LIBRARY_OUTPUT_DIRECTORY}")

# Configure support files
set(${PROJECT_NAME}_LIBRARY_DIRS "${CMAKE_CURRENT_BINARY_DIR}")
set(${PROJECT_NAME}_LIBRARIES ${${PROJECT_NAME}_STATIC} ${${PROJECT_NAME}_SHARED})
set(${PROJECT_NAME}_USE_FILE
  "${CMAKE_CURRENT_SOURCE_DIR}/Use${PROJECT_NAME}.cmake.in")
# config file
configure_file(
  "${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}Config.cmake.in"
  "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake")
# use file
configure_file(
  ${${PROJECT_NAME}_USE_FILE}
  "${CMAKE_CURRENT_BINARY_DIR}/Use${PROJECT_NAME}.cmake" COPYONLY)
