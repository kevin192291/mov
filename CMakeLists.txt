cmake_minimum_required(VERSION 3.11)
SET(PROJECT_NAME MyExample)
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
        SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++17 -static -g")
    else()
        SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++17 -g")
    endif()
  endif()

  SET (CMAKE_CXX_FLAGS_DEBUG "-g -D_DEBUG_")
  SET (CMAKE_CXX_FLAGS_RELEASE "-O4 -DNDEBUG")
  SET (CMAKE_CXX_FLAGS_DEBUG "-g -DDEBUG")
  SET (PROJECT_SRC src/main.cpp)

  if(WIN32)
    add_executable(${PROJECT_NAME} WIN32 ${PROJECT_SRC})
  else()
    add_executable(${PROJECT_NAME} ${PROJECT_SRC})
  endif()

  target_link_libraries(${PROJECT_NAME} PRIVATE sfml-graphics sfml-window sfml-system tmxlite)

  install(DIRECTORY assets DESTINATION .)