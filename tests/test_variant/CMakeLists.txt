# -*- coding:utf-8-unix; -*-
cmake_minimum_required(VERSION 3.0)

# project information
project(test_variant
  LANGUAGES C
  VERSION 0.1.0
  )

set(PROJECT_CANONICAL_NAME test_variant)

# determine sources and libraries
set(TEST_VARIANT_SOURCES
  ../include/minunit.h
  src/test_variant.c
  )

set(TEST_VARIANT_LIBS containers)

# main target config
add_executable(test_variant ${TEST_VARIANT_SOURCES})
target_link_libraries(test_variant ${TEST_VARIANT_LIBS})
target_include_directories(test_variant PRIVATE "../include")
set_property(TARGET test_variant PROPERTY C_STANDARD 11)
set_property(TARGET test_variant PROPERTY C_STANDARD_REQUIRED ON)
set_property(TARGET test_variant PROPERTY EXCLUDE_FROM_ALL 1)
set_property(TARGET test_variant PROPERTY EXCLUDE_FROM_DEFAULT_BUILD 1)

# compiler-specific flags
IF(CMAKE_C_COMPILER_ID MATCHES "GNU")
  set_property(TARGET test_variant PROPERTY COMPILE_OPTIONS -Wall -Wextra -pedantic)
ENDIF()
