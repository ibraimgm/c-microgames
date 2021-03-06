# -*- coding:utf-8-unix; -*-

cmake_minimum_required(VERSION 3.0)
project(C_Microgames
  LANGUAGES C
  VERSION 0.1.0
  )

# make sure we support in-source and out-source builds
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})

# tell the subprojects that they are inside a package
set(IN_PACKAGE 1 CACHE BOOL "Build with subprojects enabled")

# make package information available
set(PACKAGE_VERSION ${PROJECT_VERSION})
set(PACKAGE_CANONICAL_NAME "C Microgames")
configure_file (
  "${PROJECT_SOURCE_DIR}/include/package_ver.h.in"
  "${PROJECT_SOURCE_DIR}/include/package_ver.h"
  )

include_directories("${PROJECT_SOURCE_DIR}/include")

# add every subproject
add_subdirectory(src/containers)
add_subdirectory(src/consio)
add_subdirectory(src/guess-my-number)

# unit tests
enable_testing()
add_subdirectory(tests/test_clist)
add_subdirectory(tests/test_variant)
add_subdirectory(tests/test_darray)
add_test(Test_CList test_clist)
add_test(Test_Variant test_variant)
add_test(Test_DArray test_darray)
add_custom_target(check
  COMMAND ${CMAKE_CTEST_COMMAND} --output-on-failure
  DEPENDS test_clist test_variant test_darray
  )
