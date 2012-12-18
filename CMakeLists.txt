# -------------------------------------------------
# SEMIT: Slicer Execution Model Integration Testing
# -------------------------------------------------
project(SEMIT)

# CMake min
cmake_minimum_required(VERSION 2.8.2)

# All cli (and dependencies) should install to this folder
set(${PROJECT_NAME}_RUNTIME_OUTPUT_DIRECTORY "${${PROJECT_NAME}_BINARY_DIR}/bin")
set(${PROJECT_NAME}_LIBRARY_OUTPUT_DIRECTORY "${${PROJECT_NAME}_BINARY_DIR}/lib")
set(SlicerExecutionModel_CLI_RUNTIME_OUTPUT_DIRECTORY
  "${${PROJECT_NAME}_RUNTIME_OUTPUT_DIRECTORY}" CACHE PATH "" FORCE)
set(SlicerExecutionModel_CLI_LIBRARY_OUTPUT_DIRECTORY
  "${${PROJECT_NAME}_LIBRARY_OUTPUT_DIRECTORY}" CACHE PATH "" FORCE)
set(SlicerExecutionModel_CLI_ARCHIVE_OUTPUT_DIRECTORY
  "${${PROJECT_NAME}_LIBRARY_OUTPUT_DIRECTORY}" CACHE PATH "" FORCE)

# Dependency for reading images
add_subdirectory(nifti)

# CLI modules list
set(cli_modules testcli0 testcli1 testcli2 testcli3)
# Add the modules
foreach(module ${cli_modules})
  set(${module}_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/${module})
  add_subdirectory(${module})
endforeach(module)

