# -----------
# Test CLI #1
# -----------
# Check image loading from an external static lib.
# (No need for 'project()' for CLI)

# All clis depend on the SlicerExecutionModel
find_package(SlicerExecutionModel NO_MODULE REQUIRED)
include(${SlicerExecutionModel_USE_FILE})
# Depends on nifti
find_package(Nifti REQUIRED)
include(${Nifti_USE_FILE})
# Create the cli
set(MODULE_NAME testcli1)
# This test is only for executable since the integrated reader
# only supports nifti which cannot be passed via memory.
SEMMacroBuildCLI(NAME ${MODULE_NAME} EXECUTABLE_ONLY)
target_link_libraries(${MODULE_NAME} NiftiStatic)
