# -*- coding:utf-8-unix; -*-
cmake_minimum_required(VERSION 3.0)

# project information
project(testRunner
  LANGUAGES C
  VERSION 0.1.0
  )

set(PROJECT_CANONICAL_NAME testrunner)
set(PROJECT_SHORT_DESCRIPTION "Test runner for C Microgames")
set(PROJECT_COPYRIGHT_YEAR 2015)
set(PROJECT_COPYRIGHT_AUTHOR "Rafael Ibraim")

# determine sources and libraries
set(TESTRUNNER_SOURCES
  src/minunit.h
  src/test_clist.h
  src/test_clist.c
  src/main.c
  )

set(TESTRUNNER_LIBS containers)

# main target config
add_executable(testrunner ${TESTRUNNER_SOURCES})
target_link_libraries(testrunner ${TESTRUNNER_LIBS})
set_property(TARGET testrunner PROPERTY C_STANDARD 11)
set_property(TARGET testrunner PROPERTY C_STANDARD_REQUIRED ON)
set_property(TARGET testrunner PROPERTY EXCLUDE_FROM_ALL 1)
set_property(TARGET testrunner PROPERTY EXCLUDE_FROM_DEFAULT_BUILD 1)

# compiler-specific flags
IF(CMAKE_C_COMPILER_ID MATCHES "GNU")
  set_property(TARGET testrunner PROPERTY COMPILE_OPTIONS -Wall -Wextra -pedantic)
ENDIF()
