# -*- coding: utf-8-unix; -*-

cmake_minimum_required(VERSION 3.0)

# project information
project(Containers
  LANGUAGES C
  VERSION 0.1.0
  )

set(PROJECT_CANONICAL_NAME containers)
set(PROJECT_COPYRIGHT_YEAR 2015)
set(PROJECT_COPYRIGHT_AUTHOR "Rafael Ibraim")

# generate version info, etc.
configure_file (
  "${CMAKE_CURRENT_SOURCE_DIR}/include/containers_config.h.in"
  "${CMAKE_CURRENT_SOURCE_DIR}/include/containers_config.h"
  )

# it's a huge pain to make a shared DLL using MSVC
IF(MSVC)
  set(BUILD_TYPE STATIC)
ELSE()
  set(BUILD_TYPE SHARED)
ENDIF()

# sources, headers, etc
set(CONTAINERS_SOURCES
  include/containers_config.h
  include/containers.h
  include/containers_clist.h
  include/containers_variant.h
  include/containers_primptr.h
  src/containers_clist.c
  src/containers_variant.c
  src/containers_primptr.c
  )

set(CONTAINERS_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)

# main target config
add_library(containers ${BUILD_TYPE} ${CONTAINERS_SOURCES})
target_include_directories(containers PUBLIC ${CONTAINERS_INCLUDE_DIR})
set_property(TARGET containers PROPERTY C_STANDARD 11)
set_property(TARGET containers PROPERTY C_STANDARD_REQUIRED ON)

# compiler-specific flags
IF(CMAKE_C_COMPILER_ID MATCHES "GNU")
  set_property(TARGET containers PROPERTY COMPILE_OPTIONS -Wall -Wextra -pedantic)
ENDIF()
