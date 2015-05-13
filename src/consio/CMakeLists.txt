# -*- coding:utf-8-unix; -*-

cmake_minimum_required(VERSION 3.0)

# project information
project(ConsIO
  LANGUAGES C
  VERSION 0.1.0
  )

set(PROJECT_CANONICAL_NAME consio)
set(PROJECT_COPYRIGHT_YEAR 2015)
set(PROJECT_COPYRIGHT_AUTHOR "Rafael Ibraim")

# generate version info, etc.
configure_file (
  "${CMAKE_CURRENT_SOURCE_DIR}/include/consio.h.in"
  "${CMAKE_CURRENT_SOURCE_DIR}/include/consio.h"
  )

# sources, headers, etc
set(CONSIO_SOURCES
  include/consio.h
  include/consio_input.h
  include/consio_output.h
  src/consio_input.c
  src/consio_output.c
  )

set(CONSIO_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)

# main target config
add_library(consio SHARED ${CONSIO_SOURCES})
target_include_directories(consio PUBLIC ${CONSIO_INCLUDE_DIR})
set_property(TARGET consio PROPERTY C_STANDARD 11)
set_property(TARGET consio PROPERTY C_STANDARD_REQUIRED ON)

# platform-specific flags
IF(WIN32)
  set_property(TARGET consio PROPERTY COMPILE_DEFINITIONS WINDOWS)
ELSEIF(UNIX)
  set_property(TARGET consio PROPERTY COMPILE_DEFINITIONS UNIX)
ENDIF()

# compiler-specific flags
IF(CMAKE_C_COMPILER_ID MATCHES "GNU")
  set_property(TARGET consio PROPERTY COMPILE_OPTIONS -Wall -Wextra -pedantic)
ENDIF()
