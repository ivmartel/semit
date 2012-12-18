# -----------
# Test CLI #0
# -----------
# Check input parameters.
# (No need for 'project()' for CLI)

# All clis depend on the SlicerExecutionModel
find_package(SlicerExecutionModel NO_MODULE REQUIRED)
include(${SlicerExecutionModel_USE_FILE})
# Create the cli
set(MODULE_NAME testcli0)
SEMMacroBuildCLI(NAME ${MODULE_NAME})
