cmake_minimum_required(VERSION 3.15 FATAL_ERROR)

project(libOG LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

set(OG_SRC
  src/og/net/Internal.cc
  src/og/net/Ipv4.cc
  src/og/net/SocketAddr.cc
  src/og/net/Socket.cc
  src/og/net/TcpListener.cc
  src/og/net/TcpStream.cc
  src/og/net/TcpStream.cc)

# specific targets
if(${CMAKE_SYSTEM_NAME} STREQUAL Linux)
  set(OG_SRC ${OG_SRC}
    src/og/net/epoll/Event.cc
    src/og/net/epoll/Poll.cc)
endif()

# using object library to compile once every source file
add_library(OG_obj OBJECT ${OG_SRC})
set_target_properties(OG_obj PROPERTIES POSITION_INDEPENDENT_CODE TRUE)
target_include_directories(OG_obj PUBLIC include)

# the real deal
add_library(OG STATIC $<TARGET_OBJECTS:OG_obj>)
add_library(OG-shared SHARED $<TARGET_OBJECTS:OG_obj>)
