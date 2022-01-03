cmake_minimum_required(VERSION 3.11)

project(
  ModernCMakeExample
  VERSION 1.0
  LANGUAGES CXX)

  include(FetchContent)
  FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/fallahn/tmxlite.git
    GIT_TAG        b87724c732bf8521364c9b1d49e3e2f4e3834b5c # release-1.10.0
  )

  if(CMAKE_COMPILER_IS_GNUCXX OR APPLE)
    if(PROJECT_STATIC_RUNTIME)
        SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++14 -static -g")
    else()
        SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++14 -g")
    endif()
  endif()

  SET (CMAKE_CXX_FLAGS_DEBUG "-g -D_DEBUG_")
  SET (CMAKE_CXX_FLAGS_RELEASE "-O4 -DNDEBUG")
  set (CMAKE_CXX_FLAGS_DEBUG "-g -DDEBUG") 

  add_executable(MyExample main.cpp)

  target_link_libraries(MyExample PRIVATE sfml-graphics sfml-window sfml-system tmxlite)

  install(DIRECTORY assets DESTINATION .)