# CMakeList.txt : CMake project for ui_server, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Add source to this project's executable.
find_package(Boost 1.62.0 COMPONENTS log)
if(Boost_FOUND)
  include_directories(${Boost_INCLUDE_DIRS})
  add_executable (ui_client "ui_client.cpp" "ui_client.h")

  if (CMAKE_VERSION VERSION_GREATER 3.12)
    set_property(TARGET ui_server PROPERTY CXX_STANDARD 20)
  endif()

  target_link_libraries(ui_client ${Boost_LIBRARIES})
else()
  message(SEND_ERROR  "Boost not found!")
endif()