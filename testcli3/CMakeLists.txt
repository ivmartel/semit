# -----------
# Test CLI #3
# -----------
# Check image loading with ITK (via memory).
# (No need for 'project()' for CLI)

# All clis depend on the SlicerExecutionModel
find_package(SlicerExecutionModel NO_MODULE REQUIRED)
include(${SlicerExecutionModel_USE_FILE})
# Depends on itk
find_package(ITK NO_MODULE REQUIRED)
include(${ITK_USE_FILE})
# Create the cli
set(MODULE_NAME testcli3)
SEMMacroBuildCLI(NAME ${MODULE_NAME})
target_link_libraries(${MODULE_NAME}Lib ITKIO)
