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

# special flags
IF(WIN32)
  add_definitions(-DWINDOWS)
ELSEIF(UNIX)
  add_definitions(-DUNIX)
ENDIF()

# generate version info, etc.
configure_file (
  "${CMAKE_CURRENT_SOURCE_DIR}/include/consio.h.in"
  "${CMAKE_CURRENT_SOURCE_DIR}/include/consio.h"
  )

# library target
add_library(consio SHARED
  include/consio.h
  include/consio_input.h
  src/consio_input.c
  )

target_include_directories(consio PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
