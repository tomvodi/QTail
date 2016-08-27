cmake_minimum_required(VERSION 3.5.2)
cmake_policy(SET CMP0048 NEW)
cmake_policy(SET CMP0026 OLD)

project( QTail LANGUAGES CXX VERSION 0.4.0)

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

if (UNIX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1y")
endif()

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_LIST_DIR}/cmake)

if(MSVC)
  # Force to always compile with W4
  if(CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
    string(REGEX REPLACE "/W[0-4]" "/W3" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
  else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W3")
  endif()
elseif(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
  # Update if necessary
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wno-long-long -pedantic")
endif()


option(WITH_TESTS "Build unit tests" OFF)
if (WITH_TESTS)
    enable_testing()
    add_subdirectory( tests )
endif()
add_subdirectory( src )
