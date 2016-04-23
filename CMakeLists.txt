cmake_minimum_required(VERSION 2.8.12)

project( QTail CXX )

set(QTail_VERSION_MAJOR 0)
set(QTail_VERSION_MINOR 1)
set(QTail_VERSION_PATCH 0)

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1y")

option(WITH_TESTS "Build unit tests" OFF)
if (WITH_TESTS)
    enable_testing()
    add_subdirectory( tests )
endif()
add_subdirectory( src )
