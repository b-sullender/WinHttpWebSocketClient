# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#

cmake_minimum_required (VERSION 3.8)
project ("WinHttpWebSocketClient")

ADD_DEFINITIONS(-DUNICODE)
ADD_DEFINITIONS(-D_UNICODE)

add_executable(WebSocketClient WIN32 "example.cpp" "websocket.cpp" "websocket.h")

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT WebSocketClient)
set_target_properties(WebSocketClient PROPERTIES LINK_FLAGS "/SUBSYSTEM:CONSOLE")
