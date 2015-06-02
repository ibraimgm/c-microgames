cmake_minimum_required(VERSION 3.0)

# project information
project(test_darray
  LANGUAGES C
  VERSION 0.1.0
  )

set(PROJECT_CANONICAL_NAME test_darray)

# determine sources and libraries
set(TEST_DARRAY_SOURCES
  ../include/minunit.h
  src/test_darray.c
  )

set(TEST_DARRAY_LIBS containers)

# main target config
add_executable(test_darray ${TEST_DARRAY_SOURCES})
target_link_libraries(test_darray ${TEST_DARRAY_LIBS})
target_include_directories(test_darray PRIVATE "../include")
set_property(TARGET test_darray PROPERTY C_STANDARD 11)
set_property(TARGET test_darray PROPERTY C_STANDARD_REQUIRED ON)
set_property(TARGET test_darray PROPERTY EXCLUDE_FROM_ALL 1)
set_property(TARGET test_darray PROPERTY EXCLUDE_FROM_DEFAULT_BUILD 1)

# compiler-specific flags
IF(CMAKE_C_COMPILER_ID MATCHES "GNU")
  set_property(TARGET test_darray PROPERTY COMPILE_OPTIONS -g -Wall -Wextra -pedantic)
ENDIF()
