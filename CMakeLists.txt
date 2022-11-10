# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.7)

project ("ui_server_client_test")

# Include sub-projects.
add_subdirectory ("ui_server")
add_subdirectory ("ui_client")
