# -*- coding:utf-8-unix; -*-

cmake_minimum_required(VERSION 3.0)

# project information
project(GuessMyNumber_Microgame
  LANGUAGES C
  VERSION 0.1.0
  )

set(PROJECT_CANONICAL_NAME guess-my-number)
set(PROJECT_SHORT_DESCRIPTION "A simple guessing game with the computer")
set(PROJECT_COPYRIGHT_YEAR 2015)
set(PROJECT_COPYRIGHT_AUTHOR "Rafael Ibraim")

# if no one defined a package, we build in standalone mode
if (NOT IN_PACKAGE)
  SET(IN_PACKAGE 0)
endif()

# generate it's own config.h
configure_file (
  "${CMAKE_CURRENT_SOURCE_DIR}/src/config.h.in"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/config.h"
  )

# determine sources and libraries
set(GUESS_SOURCES
  src/main.c
  src/config.h)

set(GUESS_LIBS consio)

# main target config
add_executable(guess-my-number ${GUESS_SOURCES})
target_link_libraries(guess-my-number ${GUESS_LIBS})
set_property(TARGET guess-my-number PROPERTY C_STANDARD 11)
set_property(TARGET guess-my-number PROPERTY C_STANDARD_REQUIRED ON)

# platform-specific flags
IF(WIN32)
  set_property(TARGET guess-my-number PROPERTY COMPILE_DEFINITIONS WINDOWS)
ELSEIF(UNIX)
  set_property(TARGET guess-my-number PROPERTY COMPILE_DEFINITIONS UNIX)
ENDIF()

# compiler-specific flags
IF(CMAKE_C_COMPILER_ID MATCHES "GNU")
  set_property(TARGET guess-my-number PROPERTY COMPILE_OPTIONS -Wall -Wextra -pedantic)
ENDIF()
