CMAKE_MINIMUM_REQUIRED( VERSION 2.8.5 )

SET(CMAKE_SYSTEM_NAME "Linux")

# Project Declaration

project(cys-engine)

# enable c++11
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_definitions(-m64 -Wall -Wno-unused-function)

# Get source files

file(
  GLOB_RECURSE source_files 
  # ngengine
  ../../src/*
)

include_directories(
  ../../include/
)

add_library(cysengine ${source_files})

add_custom_command(TARGET cysengine POST_BUILD 
  COMMAND ${CMAKE_COMMAND} -E copy libcysengine.a ../../bin/libcysengine.a
)

#add_custom_command(TARGET cysengine POST_BUILD 
#  COMMAND ${CMAKE_COMMAND} -E copy ../../resources/sql/01-story.sql ../../bin/sql/01-story.sql
#)
file(MAKE_DIRECTORY ../../bin)
file(MAKE_DIRECTORY ../../bin/sql)
file(COPY ../../resources/sql DESTINATION ../../bin/)

# TESTS AND TEST RUNNER

MACRO( TEST _target _target_folder )
  file(
    GLOB_RECURSE _sources
    ../../tests/tests/${_target_folder}/*.cpp
  )
  add_executable(${_target} ${_sources})
  include_directories(../../tests/tests/)
  
  target_link_libraries(${_target} cysengine)
  target_link_libraries(${_target} sqlite3)

  add_custom_command(TARGET ${_target} POST_BUILD 
    COMMAND ${CMAKE_COMMAND} -E copy ${_target} ../../bin/tests/${_target_folder}/test
  )

ENDMACRO( TEST )

TEST( utils_data_datatype utils/data/datatype )
TEST( utils_database_sqlite3 utils/database/sqlite3 )
TEST( storyexample_1 story-example/1 )

# test runner

file(
    GLOB_RECURSE _sources_runner
    ../../tests/runner/*.cpp
  )
add_executable( test_runner ${_sources_runner})

add_custom_command(TARGET test_runner POST_BUILD 
  COMMAND ${CMAKE_COMMAND} -E copy test_runner ../../bin/test-runner
)

