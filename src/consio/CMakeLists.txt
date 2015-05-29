# -*- coding:utf-8-unix; -*-

cmake_minimum_required(VERSION 2.8)
include(CheckIncludeFile)
include(CheckSymbolExists)

# set version manually
if(POLICY CMP0048)
  cmake_policy(SET CMP0048 OLD)
endif()

# project information
project(ConsIO
  LANGUAGES C
  )

set(PROJECT_VERSION_MAJOR 0)
set(PROJECT_VERSION_MINOR 1)
set(PROJECT_VERSION_PATCH 0)
set(PROJECT_VERSION ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH})

set(PROJECT_CANONICAL_NAME consio)
set(PROJECT_COPYRIGHT_YEAR 2015)
set(PROJECT_COPYRIGHT_AUTHOR "Rafael Ibraim")

# generate version info, etc.
check_include_file(getopt.h HAVE_GETOPT_H)
check_include_file(conio.h HAVE_CONIO_H)
check_symbol_exists(getch conio.h HAVE_GETCH)
check_include_file(termios.h HAVE_TERMIOS_H)
check_symbol_exists(GetStdHandle windows.h USE_WINDOWS_CONSOLE_API)

configure_file (
  "${CMAKE_CURRENT_SOURCE_DIR}/include/consio_config.h.in"
  "${CMAKE_CURRENT_SOURCE_DIR}/include/consio_config.h"
  )

# it's a huge pain to make a shared DLL using MSVC
IF(MSVC)
  set(BUILD_TYPE STATIC)
ELSE()
  set(BUILD_TYPE SHARED)
ENDIF()

# sources, headers, etc
IF(NOT HAVE_GETOPT_H)
  set(CONSIO_GETOPT_SOURCES
    include/getopt.h
    src/getopt_long.c
    )
ENDIF()

set(CONSIO_SOURCES
  include/consio_config.h
  include/consio.h
  include/consio_input.h
  include/consio_output.h
  src/consio_input.c
  src/consio_output.c
  ${CONSIO_GETOPT_SOURCES}
  )

set(CONSIO_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(CONSIO_LIBS containers)

# main target config
add_library(consio ${BUILD_TYPE} ${CONSIO_SOURCES})
target_include_directories(consio PUBLIC ${CONSIO_INCLUDE_DIR})
target_link_libraries(consio ${CONSIO_LIBS})
set_property(TARGET consio PROPERTY C_STANDARD 11)
set_property(TARGET consio PROPERTY C_STANDARD_REQUIRED ON)

# compiler-specific flags
IF(CMAKE_C_COMPILER_ID MATCHES "GNU")
  set_property(TARGET consio PROPERTY COMPILE_OPTIONS -Wall -Wextra -pedantic)
ENDIF()

IF(MSVC)
  set_property(TARGET consio PROPERTY COMPILE_OPTIONS /D_CRT_SECURE_NO_WARNINGS)
ENDIF()
