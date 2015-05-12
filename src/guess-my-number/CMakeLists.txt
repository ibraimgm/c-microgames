# -*- coding:utf-8-unix; -*-

cmake_minimum_required(VERSION 3.0)

# project information
project(GuessMyNumber_Microgame
  LANGUAGES C
  VERSION 0.1.0
  )

set(PROJECT_CANONICAL_NAME guess-my-number)
set(PROJECT_COPYRIGHT_YEAR 2015)
set(PROJECT_COPYRIGHT_AUTHOR "Rafael Ibraim")

# if no one defined a package, we build in standalone mode
if (NOT IN_PACKAGE)
  SET(IN_PACKAGE 0)
endif()

# special flags
IF(WIN32)
  add_definitions(-DWINDOWS)
ELSEIF(UNIX)
  add_definitions(-DUNIX)
ENDIF()

# generate it's own config.h
configure_file (
  "${CMAKE_CURRENT_SOURCE_DIR}/src/config.h.in"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/config.h"
  )

add_executable(guess-my-number
  src/main.c
  src/config.h
  )

target_link_libraries(guess-my-number
  consio
  )
