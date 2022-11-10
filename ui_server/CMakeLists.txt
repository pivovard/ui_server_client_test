# CMakeList.txt : CMake project for ui_server, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Add source to this project's executable.
find_package(Boost 1.62.0 COMPONENTS log)
if(Boost_FOUND)
  message("Include headers: " ${Boost_INCLUDE_DIRS})
  include_directories(${Boost_INCLUDE_DIRS})
  add_executable (ui_server "ui_server.cpp"  "helpers/stats.h" "helpers/stats.cpp" "helpers/logger.h" "tcp/tcp_server.h" "tcp/tcp_server.cpp" "tcp/tcp_connection.h"  "tcp/tcp_connection.cpp")

  if (CMAKE_VERSION VERSION_GREATER 3.12)
    set_property(TARGET ui_server PROPERTY CXX_STANDARD 20)
  endif()

  message("Link libararies: " ${Boost_LIBRARIES})
  target_link_libraries(ui_server ${Boost_LIBRARIES})

else()
  message(SEND_ERROR  "Boost not found!")
endif()

