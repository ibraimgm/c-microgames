# -*- coding:utf-8-unix; -*-
cmake_minimum_required(VERSION 3.0)

# project information
project(test_clist
  LANGUAGES C
  VERSION 0.1.0
  )

set(PROJECT_CANONICAL_NAME test_clist)

# determine sources and libraries
set(TEST_CLIST_SOURCES
  ../include/minunit.h
  src/test_clist.c
  )

set(TEST_CLIST_LIBS containers)

# main target config
add_executable(test_clist ${TEST_CLIST_SOURCES})
target_link_libraries(test_clist ${TEST_CLIST_LIBS})
target_include_directories(test_clist PRIVATE "../include")
set_property(TARGET test_clist PROPERTY C_STANDARD 11)
set_property(TARGET test_clist PROPERTY C_STANDARD_REQUIRED ON)
set_property(TARGET test_clist PROPERTY EXCLUDE_FROM_ALL 1)
set_property(TARGET test_clist PROPERTY EXCLUDE_FROM_DEFAULT_BUILD 1)

# compiler-specific flags
IF(CMAKE_C_COMPILER_ID MATCHES "GNU")
  set_property(TARGET test_clist PROPERTY COMPILE_OPTIONS -Wall -Wextra -pedantic)
ENDIF()
